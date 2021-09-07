#include <Arduino.h>
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <SoftwareSerial.h>
#include "ArduinoJson-v6.18.0.h"

//Sendlab netwerk ww: SENDLAB / SEnDLab@LA121

WiFiClient espClient;
PubSubClient client(espClient);

constexpr uint8_t max_id_length = 32;

char callback_id[max_id_length];
char callback_buffer[255];
uint8_t callback_buffer_length = 0;

void callback(char* topic, byte* payload, unsigned int length) {


  /*Serial.println("Got callback: ");
  while (length--) Serial.print(*payload); ++payload;
  Serial.println();
  Serial.println("Payload done");*/
  callback_buffer_length = length > 255 ? 255 : length;
  memcpy(callback_buffer, payload, callback_buffer_length);
  char * write_head = callback_id;
  char * read_head = topic + 5; // skip "node/"
  while (*read_head != '/' && *read_head != '\0') {
    *(write_head++) = *(read_head++);
  }
  write_head = '\0';
};

void setup() {
  pinMode(BUILTIN_LED, OUTPUT);

  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial1.begin(9600);

  Serial.print("attempting WIFI connection...");
  WiFi.hostname("SmartSensor-Controller");
  WiFi.begin("SENDLAB", "SEnDLab@LA121");
  while (!WiFi.isConnected())
    delay(1);
  Serial.print("connected\n");
  
  client.setBufferSize(1024);
  client.setServer("sendlab.nl", 11884);
  client.setCallback(callback);
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("attempting MQTT connection...");

    if (client.connect("SmartSensor-Controller", "node", "smartmeternode")) {
      Serial.println("connected");
    } else {
      Serial.println("failed to connect");
      delay(1000);
    }
  }
}

bool b;

long last = millis();

char message_buffer[512];

bool is_valid_message(const char* msg) {
  bool is_valid = true;
  uint8_t index = 0;

  do {
    const auto c = msg[index];

    if (c >= 'a' && c <= 'z') continue;
    if (c >= 'A' && c <= 'Z') continue;
    if (c >= '0' && c <= '9') continue;
    if (c == '{' || c == '}') continue;
    if (c == '[' || c == ']') continue;
    if (c == ' ' || c == '.') continue;
    if (c == '\n' || c == '\t') continue;
    if (c == ':' || c == '-') continue;
    if (c == '"' || c == ',') continue;
    if (c == '!') continue;

    Serial.printf("\tinvalid char := %c (0x%X) at %d\n", c, c, index);
    is_valid = false;

  } while (msg[++index] != '\0');
  return is_valid;
}

constexpr uint8_t id_to_adress_size = 32;

struct {
  char id[max_id_length];
  uint64_t xbee_adress;
} id_to_adress_table[id_to_adress_size];
uint8_t id_to_adress_index = 0;

bool register_SmartSensor(const char* id, uint64_t xbee_adress) {
  if (strlen(id) > max_id_length) {
    Serial.printf("unable to register := id is too long (%s)\n", id);
    return false;
  } else if (id_to_adress_index >= id_to_adress_size) {
    Serial.print("unable to register := no space in table\n");
    return false;
  }

  strcpy(id_to_adress_table[id_to_adress_index].id, id);
  id_to_adress_table[id_to_adress_index].xbee_adress = xbee_adress;

  Serial.printf("registered id %s at adress 0x%016llX and index %hhu\n", id, xbee_adress, id_to_adress_index);

  ++id_to_adress_index;
  
  return true;
}

uint64_t get_xbee_adress(const char* id) {
  for (uint8_t i = 0; i < id_to_adress_index; ++i) {
    if (strcmp(id, id_to_adress_table[i].id) == 0) return id_to_adress_table[i].xbee_adress;
  }
  return 0;
}

void output_xbee_frame(uint64_t destination, const char*msg) {
  //Serial1.printf("0x%016llX -> %s\n", destination, msg);
  constexpr auto header_size = 14;

  const auto msg_length = strlen(msg);
  if (msg_length > (255-header_size)) {
    Serial.printf("XBEE: message to long (%d)\n", msg_length);
    return;
  }

  const auto length = msg_length + header_size;

  uint64_t checksum = 0;
  auto send_byte = [&](uint8_t byte) { checksum += byte; Serial1.write(byte); };

  Serial1.write(0x7E);
  Serial1.write(0x00);
  Serial1.write(length & 0xFF);

  send_byte(0x10);
  send_byte(1);
  for (uint8_t i = 0; i < 8; ++i) 
    send_byte((destination >> ((7-i)*8)) & 0xFF);
  
  send_byte(0xFF);
  send_byte(0xFE);
  send_byte(0);
  send_byte(0);
  
  for (uint8_t i = 0; i < msg_length; ++i)
    send_byte(msg[i]);

  send_byte(0xFF - (checksum & 0xFF));
}

void loop() {
  //Serial.println("Hello!");
  //delay(250);
  digitalWrite(LED_BUILTIN, (b = !b));

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  if (callback_buffer_length) {
    Serial.print("callback:\n");
    Serial.write(callback_buffer, callback_buffer_length);
    Serial.print("\n\n");

    StaticJsonDocument<255> doc;

    if (auto error = deserializeJson(doc, callback_buffer, callback_buffer_length)) {
      Serial.printf("Failed to deserialize JSON: %s\n", error.c_str());
    } else{

      if (const auto adrr = get_xbee_adress(callback_id)) {

        output_xbee_frame(adrr, doc["time"]);
      } else {
        Serial.printf("unable to resolve id := %s\n", callback_id);
      }
    }

    callback_buffer_length = 0;
  }

  if (!Serial.available()) { 
    //Serial.write("No Data\n"); 
    delay(100);
    return; 
  }
  //Serial.write("Data incomming\n");

  int res = Serial.read();
  if (res >= 0) {
    uint8_t byte = res;
    if (byte == '?') {
      Serial1.write("!OK!");
    } else if (byte == 0x7E) {
      Serial.write(" 0x7E ");

      uint16_t payload_bytes_read = 0;
      auto read_byte = [&]{++payload_bytes_read; return static_cast<uint8_t>(Serial.read());};

      uint16_t length = read_byte() << 8;
      length |= read_byte();
      payload_bytes_read = 0;

      Serial.printf("length := %u\n", length);

      const auto frame_type = read_byte();
      uint64_t source_adrr64 = 0;
      for (uint_fast8_t i = 0; i < (64/8); ++i)
        source_adrr64 |= (uint64_t)read_byte() << (8*(7-i));
      uint16_t source_adrr16 = read_byte() << 8;
      source_adrr16 |= read_byte();
      uint8_t recieve_options = read_byte();

      char* write_needle = message_buffer;
      /*while (payload_bytes_read < length) {
        /*if (!(payload_bytes_read%10))*/ /*Serial.flush(), yield();
        const auto byte = read_byte();
        //Serial.write(byte);
        *write_needle++ = byte;
      }*/
      write_needle = write_needle + Serial.readBytes(message_buffer, length-payload_bytes_read);

      *write_needle++ = '\0';
      auto checksum = read_byte();
      --payload_bytes_read; // correct for checksum
      
      char* message_to_send = message_buffer;

      const auto actual_msg_length = strlen(message_to_send);
      Serial.printf("message(length := %d): %s\n", actual_msg_length, message_to_send);

      if (!actual_msg_length) {
        Serial.print("aborting since message is empty\n");
      } else if (!is_valid_message(message_to_send)) {
        Serial.print("aborting due to corrupted message\n");
      } else if (message_buffer[0] == '!') {
        Serial.print("init request\n");
        if (!register_SmartSensor(message_buffer+1, source_adrr64)) return;

        char topic[max_id_length+5+8+1];
        sprintf(topic, "node/%s/message", message_buffer+1);

        Serial.printf("subscribing to %s\n", topic);
        client.subscribe(topic, 1);

        Serial.print("sending init\n");

        message_to_send = write_needle;
        write_needle += sprintf(message_to_send, 
R"!({
    "type":  "simulation",
    "mode": 0,
    "id":    "%s",
    "name":  "test 1",
    "measurements": [{
        "name": "temperature",
        "description": "Temperature sensor -40 to 100 with 0.1 accuracy.",
        "unit": "degree of Celsius"
    },
    {
        "name": "humidity",
        "description": "Humidity sensor 0 to 100 with 0.5 accuracy.",
        "unit": ""
    }],
    "actuators": []
}
)!", message_buffer + 1);
        *(++write_needle) = '\0';
        Serial.print(message_to_send);
        client.publish("node/init", 
          message_to_send,
        false);
      } else {
        Serial.print("normal JSON\n");
        Serial.print("uploading to MQTT\n");
        client.publish("node/data", 
          message_to_send,
        false);
      }

      
    }
  }

  /*
  if ((millis() - last) > 1000) {
    Serial.println("publishing");
    
    last = millis();

  }*/
}