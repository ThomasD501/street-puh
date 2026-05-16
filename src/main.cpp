#include <Arduino.h>
#include <WiFi.h>

#include "config.h"
#include "secrets.h"
#include "app_config.h"
#include "weather.h"
#include "time o day.h"
#include "timer.h"

WeatherInfo currentWeather;
// Function prototypes
void connectToWiFi() {
  WiFi.mode(WIFI_STA);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.print("Connecting to WiFi");

  int attempts = 0;

  while (WiFi.status() != WL_CONNECTED && attempts < 20) {
    delay(500);
    Serial.print(".");
    attempts++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println();
    Serial.println("Connected!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println();
    Serial.println("Failed to connect.");
  }
}

void drawScreen() {
  display.setFullWindow();
  display.firstPage();

  do {
    display.fillScreen(GxEPD_WHITE);

    display.setTextColor(GxEPD_BLACK);
    display.setTextSize(1);

    display.setCursor(5, 15);
    display.print("WiFi: ");
    display.print(WiFi.status() == WL_CONNECTED ? "Connected" : "Failed");

    display.setCursor(5, 35);
    display.print("Time: ");
    display.print(getTimeString());

    display.setCursor(5, 55);
    if (currentWeather.valid) {
      display.print("Temp: ");
      display.print(currentWeather.temperature, 1);
      display.print(" F");
    } else {
      display.print("Weather error");
    }

    display.setCursor(5, 75);
    if (currentWeather.valid) {
      display.print("Wind: ");
      display.print(currentWeather.windSpeed, 1);
      display.print(" mph");
    }

    display.setCursor(5, 95);
    display.print("Timer: ");
    display.print(getTimerString());

  } while (display.nextPage());
}

void setup() {
  Serial.begin(115200);

  pinMode(EPD_PWR, OUTPUT);
  digitalWrite(EPD_PWR, HIGH);
  delay(200);

  pinMode(ENC_CLK, INPUT_PULLUP);
  pinMode(ENC_DT, INPUT_PULLUP);
  pinMode(ENC_SW, INPUT_PULLUP);

  display.init(115200);
  display.setRotation(DISPLAY_ROTATION);

  connectToWiFi();

  if (WiFi.status() == WL_CONNECTED) {
    syncTime();
    currentWeather = getWeather();
  }

  startTimer(TIMER_MINUTES);

  drawScreen();
}

void loop() {
  static unsigned long lastScreenUpdate = 0;

  // Restart timer with button press
  if (digitalRead(ENC_SW) == LOW) {
    startTimer(TIMER_MINUTES);
    drawScreen();
    delay(300);
  }

  // Refresh screen every minute
  if (millis() - lastScreenUpdate >= SCREEN_UPDATE_INTERVAL) {
    lastScreenUpdate = millis();

    if (WiFi.status() == WL_CONNECTED) {
      currentWeather = getWeather();
    }

    drawScreen();
  }
}