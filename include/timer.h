#pragma once
#include <Arduino.h>

struct TimerInfo {
  unsigned long startTime;
  unsigned long duration;
  bool running;
};

void startTimer(int minutes);
String getTimerString();