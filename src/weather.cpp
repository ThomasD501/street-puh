#include "weather.h"
#include "app_config.h"

#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

WeatherInfo getWeather() {
  WeatherInfo weather;
  weather.temperature = 0;
  weather.windSpeed = 0;
  weather.valid = false;

  if (WiFi.status() != WL_CONNECTED) {
    return weather;
  }

  HTTPClient http;

  String url = "https://api.open-meteo.com/v1/forecast?";
  url += "latitude=" + String(WEATHER_LATITUDE, 4);
  url += "&longitude=" + String(WEATHER_LONGITUDE, 4);
  url += "&current=temperature_2m,wind_speed_10m";
  url += "&temperature_unit=fahrenheit";
  url += "&wind_speed_unit=mph";

  http.begin(url);
  int httpCode = http.GET();

  if (httpCode == 200) {
    String payload = http.getString();

    JsonDocument doc;
    DeserializationError error = deserializeJson(doc, payload);

    if (!error) {
      weather.temperature = doc["current"]["temperature_2m"];
      weather.windSpeed = doc["current"]["wind_speed_10m"];
      weather.valid = true;
    }
  }

  http.end();
  return weather;
}