# Coordinator

Coordinator ontwikkeld om de data van de SmartSensor te ontvangen en die door te sturen over MQTT.
Voor development is Platformio gebruikt. 


## Configuratie
Er is een config-template.h bestand in de include folder hier kan de WiFi en MQTT configuratie aangepast worden.


## Data 
Er wordt vanuit de Smart Sensor een JSON gestuurd die wordt uitgelezen met de Coordinator, in de Coordinator wordt er gecheckt of het een valide JSON is, zo ja dan wordt doorgestuurd naar een MQTT server die je hebt ingesteld in de configuratiebestand.