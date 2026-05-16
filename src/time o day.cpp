#include "time o day.h"
#include "app_config.h"

#include <Arduino.h>
#include <time.h>

void syncTime() {
  configTzTime(TIMEZONE_INFO, "pool.ntp.org", "time.nist.gov");
}

String getTimeString() {
  struct tm timeinfo;

  if (!getLocalTime(&timeinfo)) {
    return "Time error";
  }

  char buffer[20];
  strftime(buffer, sizeof(buffer), "%I:%M %p", &timeinfo);

  return String(buffer);
}