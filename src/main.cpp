#include <WiFi.h>
#include <GxEPD2_BW.h>
#include <Adafruit_GFX.h>
#include "config.h"

const char* ssid = "freakbob";
const char* password = "spencil69!";

void connectToWiFi() {
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

    Serial.print("Connecting to WiFi");

    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 20) {
        delay(500);
        Serial.print(".");
        attempts++;
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\nConnected!");
        Serial.print("IP Address: ");
        Serial.println(WiFi.localIP());
    } else {
        Serial.println("\nFailed to connect.");
    }
}

void setup() {
    Serial.begin(115200);

    pinMode(EPD_PWR, OUTPUT);
    digitalWrite(EPD_PWR, HIGH);
    delay(200);

    pinMode(ENC_CLK, INPUT_PULLUP);
    pinMode(ENC_DT, INPUT_PULLUP);
    pinMode(ENC_SW, INPUT_PULLUP);

    connectToWiFi();

    display.init(115200);
    display.setRotation(DISPLAY_ROTATION);
    display.setFullWindow();

    display.firstPage();
do {
    display.fillScreen(GxEPD_WHITE);
    display.drawRect(0, 0, DISP_W, DISP_H, GxEPD_BLACK);

    display.setTextColor(GxEPD_BLACK);
    display.setTextSize(2);

    // Show WiFi name (SSID)
    display.setCursor(10, 30);
    display.print(WiFi.SSID());

    // Show connection status
    display.setCursor(10, 60);
    if (WiFi.status() == WL_CONNECTED) {
        display.print("Connected");
    } else {
        display.print("Failed");
    }

    // Show IP address
    display.setCursor(10, 90);
    if (WiFi.status() == WL_CONNECTED) {
        display.print(WiFi.localIP());
    }

} while (display.nextPage());

}

void loop() {
}