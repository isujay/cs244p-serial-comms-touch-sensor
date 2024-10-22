#include <Arduino.h>
#include <TFT_eSPI.h>

#define SERIAL_BAUD_RATE 9600

// peripheral objects
TFT_eSPI tft = TFT_eSPI();

void setup() {
    // write your initialization code here

    Serial.begin(SERIAL_BAUD_RATE);
    Serial.println("Initializing...");

    tft.init();
    tft.setRotation(1);
    tft.fillScreen(TFT_WHITE);
    tft.setCursor(0,0);
    tft.setTextColor(TFT_WHITE);
    tft.println("Hello from Irvine, CA");
    Serial.println("All systems up");
}

void loop() {
    // write your code here

}