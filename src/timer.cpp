#include "timer.h"

TimerInfo timer;


void startTimer(int minutes) {
  timer.startTime = millis();
  timer.duration = minutes * 60UL * 1000UL;
  timer.running = true;
}

String getTimerString() {
  if (!timer.running) {
    return "Timer off";
  }

  unsigned long elapsed = millis() - timer.startTime;

  if (elapsed >= timer.duration) {
    timer.running = false;
    return "Done!";
  }

  unsigned long remaining = timer.duration - elapsed;
  int totalSeconds = remaining / 1000;
  int minutesLeft = totalSeconds / 60;
  int secondsLeft = totalSeconds % 60;

  char buffer[10];
  sprintf(buffer, "%02d:%02d", minutesLeft, secondsLeft);

  return String(buffer);
}