# Weather data
Getting weather data from open API's. This documentation describes how this has been setted up.

## openweathermap.org
The openweathermap provides a free API that returns temperature, wind, humidity and pressure for example. No solar information is provided. You need to have an API token to make use of this service. In order to retrieve one, you need to register yourself.
1. Register yourself on https://openweathermap.org
2. Go to your API keys in your account
3. Generate a new API key with for example the name "SmartNetwork"
4. Put this token in the config-openweathermap.json file

To get more data you need to have a billing plan. In that case a lot of data can be provided. Also solar data is available, but somehow very expensive. An example of the output of the API is the following json:
````json
{
  "coord": {
    "lon": 4.776,
    "lat": 51.5866
  },
  "weather": [
    {
      "id": 520,
      "main": "Rain",
      "description": "light intensity shower rain",
      "icon": "09d"
    }
  ],
  "base": "stations",
  "main": {
    "temp": 278.99,
    "feels_like": 278.99,
    "temp_min": 278.1,
    "temp_max": 279.82,
    "pressure": 994,
    "humidity": 93
  },
  "visibility": 10000,
  "wind": {
    "speed": 0.89,
    "deg": 310,
    "gust": 1.79
  },
  "rain": {
    "1h": 0.21
  },
  "clouds": {
    "all": 75
  },
  "dt": 1638627849,
  "sys": {
    "type": 2,
    "id": 2039561,
    "country": "NL",
    "sunrise": 1638602937,
    "sunset": 1638632022
  },
  "timezone": 3600,
  "id": 2758401,
  "name": "Breda",
  "cod": 200
}
````

## Forecast.solar
This is both an open and a personal api. To get estimates on how much you solar panels are going to be producing use the API provided on https://doc.forecast.solar/doku.php?id=api:estimate. In this case, you can use the API url https://api.forecast.solar/estimate/:lat/:lon/:dec/:az/:kwp. If you would like to get it for Avans University of Applied Sciences at Breda you can use https://api.forecast.solar/estimate/51.58586805578371/4.793202206697863/0/0/1000. Just to check how it works. The following JSON is received:

````json
{
  "result": {
    "watts": {
      "2021-12-06 08:25:00": 0,
      "2021-12-06 08:43:00": 12000,
      "2021-12-06 09:00:00": 61151,
      "2021-12-06 10:00:00": 92900,
      "2021-12-06 11:00:00": 123163,
      "2021-12-06 12:00:00": 131180,
      "2021-12-06 13:00:00": 120669,
      "2021-12-06 14:00:00": 100118,
      "2021-12-06 15:00:00": 62252,
      "2021-12-06 16:00:00": 18455,
      "2021-12-06 16:20:00": 4000,
      "2021-12-06 16:40:00": 0,
      "2021-12-07 08:26:00": 0,
      "2021-12-07 08:43:00": 22000,
      "2021-12-07 09:00:00": 109762,
      "2021-12-07 10:00:00": 178663,
      "2021-12-07 11:00:00": 220607,
      "2021-12-07 12:00:00": 225307,
      "2021-12-07 13:00:00": 188688,
      "2021-12-07 14:00:00": 124494,
      "2021-12-07 15:00:00": 63795,
      "2021-12-07 16:00:00": 19094,
      "2021-12-07 16:20:00": 4000,
      "2021-12-07 16:40:00": 0
    },
    "watt_hours": {
      "2021-12-06 08:25:00": 0,
      "2021-12-06 08:43:00": 3600,
      "2021-12-06 09:00:00": 20926,
      "2021-12-06 10:00:00": 113826,
      "2021-12-06 11:00:00": 236989,
      "2021-12-06 12:00:00": 368169,
      "2021-12-06 13:00:00": 488838,
      "2021-12-06 14:00:00": 588956,
      "2021-12-06 15:00:00": 651208,
      "2021-12-06 16:00:00": 669663,
      "2021-12-06 16:20:00": 670996,
      "2021-12-06 16:40:00": 670996,
      "2021-12-07 08:26:00": 0,
      "2021-12-07 08:43:00": 6233,
      "2021-12-07 09:00:00": 37333,
      "2021-12-07 10:00:00": 215996,
      "2021-12-07 11:00:00": 436603,
      "2021-12-07 12:00:00": 661910,
      "2021-12-07 13:00:00": 850598,
      "2021-12-07 14:00:00": 975092,
      "2021-12-07 15:00:00": 1038887,
      "2021-12-07 16:00:00": 1057981,
      "2021-12-07 16:20:00": 1059314,
      "2021-12-07 16:40:00": 1059314
    },
    "watt_hours_day": {
      "2021-12-06": 670996,
      "2021-12-07": 1059314
    }
  },
  "message": {
    "code": 0,
    "type": "success",
    "text": "",
    "info": {
      "latitude": 51.5858,
      "longitude": 4.7928,
      "place": "4817 HC Breda, Noord-Brabant, NL",
      "timezone": "Europe/Amsterdam"
    },
    "ratelimit": {
      "period": 3600,
      "limit": 12,
      "remaining": 1
    }
  }
}
````

## NREL
Another interesting data source can be found at https://www.nrel.gov/. Solar information can be found here as well. Not really actual information about solar radiation. Data for analysis is provided mostly, like total radiation or kW/m^2 per month. To get the API key and access to the API itself go to https://developer.nrel.gov/. To get the API key, you need to register yourself at this website. A link is shown "Get an API key" where you can click on. You get immediatly an API key. It is also send to your e-mail. The following webservices are provided by the API:
1. Buildings
2. Electricity
3. Energy Optimization
4. Partnering
5. Solar
6. Transportation
7. Wave
8. Wind

For actual data this api is currently not used for the SmartNetwork.

## EU Science HUB
Another interesting web page is https://ec.europa.eu/jrc/en/pvgis from the EU. Solar data is on, but not yet found an actual API. It provides historical information on hourly radiation for example. A really good resource for research.

## Overview of other API resources
https://www.programmableweb.com/category/solar/api
