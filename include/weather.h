#pragma once
#include <Arduino.h>

struct WeatherInfo {
  float temperature;
  float windSpeed;
  bool valid;
};

WeatherInfo getWeather();