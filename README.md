# SmartSensor
Author: _Maurice Snoeren (Lectoraat Smart Energy en Datascience & ICT)_

De SmartSensor is een resultaat van verschillende onderzoeken sinds 2018. Focus is gegeven aan laag vermogen, controle over energiestromen en eenvoud. Deze SmartSensor wordt binnen onderzoek en onderwijs toegepast.

<img src="Documentation/SmartSensor v1 Board.png" width="400px"/>

_3D generated model_

## Inleiding
Meten is weten! Het belang van meten en het verzamelen van informatie is wel bekend. Echter komt het vaak  voor dat data niet voorhanden is of dat de data van beschikbare systemen van onvoldoende kwaliteit is. Bestaande meetsystemen zijn vaak kostbaar en onvoldoende flexibel om de benodigde aanpassingen te maken die nodig zijn binnen de verschillende onderzoeken. De SmartSensor biedt een open platform, waarmee eenvoudig vele meetpunten in een omgeving geïnstalleerd kunnen worden. Het platform biedt de mogelijkheid eigen metingen toe te voegen. Uniek is dat het met de SmartSensor mogelijk wordt om met andere systemen te communiceren. Hierdoor wordt het mogelijk om tevens sturing aan te brengen. Een open platform dat binnen Avans Hogeschool wordt ingezet voor het onderzoek en onderwijs.

## SmartSensor specificatie
- Atmega324PB (Microcontroller)
- ATECC608B (Trusted Platform Module)
- Zigbee module (of nRF24L01)
- Real-time klok
- Omgevingslichtsensor (0lx t/m 167klx, 5mlx res.) 
- Temperatuursensor (±0.5˚C, -40 t/m 100˚C)
- Luchtvochtigheidssensor (±4.5 %RH)
- CO2 sensor (optional, eCO2, 400 t/m 8192ppm) 
- Interfaces: RS232 (3.3V), I2C en SPI
- Uitbreiden met header

## Werking
Alle SmartSensoren staan met elkaar in verbinding door middel van een Zigbee mesh-netwerk. Eén van de sensoren dient als een coördinator te dienen om de meet¬gegevens uit het systeem te krijgen. Via deze coördinator kunnen tevens commando’s naar de verschillende sensoren gestuurd worden om bijvoorbeeld een batterij op te laden of de verwarming in te stellen op 20 graden Celsius.

## Metingen bestaande gebouwen
Door op verschillende punten te meten, krijgt men inzicht in de energiehuishouding van het bestaande gebouw. In veel (oude) gebouwen zijn er geen of onvoldoende meetpunten aanwezig. Met behulp van de SmartSensor kunnen deze meetpunten eenvoudig worden toegevoegd. Doordat met gebouwsystemen communiceert kan worden, is het tevens mogelijk de gegevens van deze systemen te verzamelen en mee te nemen in de analyse.

## Verduurzaming gebouwen
Binnen gebouwen kan de SmartSensor meetpunten realiseren én communiceren met gebouwsystemen. Hierdoor wordt het mogelijk om een regelsysteem te realiseren waarbij het gebouw kan worden verduurzaamd. Gebouwsystemen worden dan aangestuurd op basis van verschillende metingen. Door de flexibiliteit van deze SmartSensor wordt het eenvoudig om verschillende strategieën en technieken te onderzoeken en ontdekken.

## Nieuwbouw
Nieuwe gebouwen worden vaak opgeleverd met veel sensoren en gebouwbeheersystemen. Meer meetpunten is vaak niet nodig. In dit geval is het mogelijk om de SmartSensor te gebruiken om het gebouw-beheersysteem te valideren. Door vele metingen aan te brengen krijgt men inzicht in de kwaliteit en effectiviteit van het bestaande systeem. Daarnaast is het mogelijk om met de SmartSensor eenvoudig extra meetpunten aan te brengen binnen het gebouw.

## Onderzoek
De SmartSensor speelt steeds meer een rol binnen de onderzoeken naar slimme duurzame energiesystemen, datascience vraagstukken en het zelfbewuste huis.

## Interesse
Interesse voor samenwerking? Neem contact met ons op!
>>>>>>> development
