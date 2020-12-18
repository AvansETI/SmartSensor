# Coordinator

Coordinator ontwikkeld om de data van de SmartSensor te ontvangen en die door te sturen over MQTT.
Voor development is Platformio gebruikt. Arduino Uno met een Zigbee Shield en een WiFi shield gebruikt. De Zigbee module moet wel ingesteld worden via DIGI XCTU. PANID, AT modus.


## Configuratie
Er is een config-template.h bestand in de include folder hier kan de WiFi en MQTT configuratie aangepast worden.


## Data 
Er wordt vanuit de Smart Sensor een JSON gestuurd die wordt uitgelezen met de Coordinator, in de Coordinator wordt er gecheckt of het een valide JSON is, zo ja dan wordt doorgestuurd naar een MQTT server die je hebt ingesteld in de configuratiebestand.
