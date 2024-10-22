#include <Arduino.h>
#include <TFT_eSPI.h>

#define SERIAL_BAUD_RATE 9600
#define SECOND 1

// peripheral objects
TFT_eSPI tft = TFT_eSPI();

// other variables
uint16_t clockSeconds = 0;

void initTFT();

void initBoardSerialBus();

void setup() {
    // write your initialization code here

    initBoardSerialBus();
    Serial.println("Initializing...");

    initTFT();
    Serial.println("All systems up");
}

void loop() {
    // write your code here
    tft.fillScreen(TFT_BLACK);
    tft.setCursor(0, 0);
    tft.print(clockSeconds);
    sleep(1 * SECOND);
    clockSeconds++;
}

void initBoardSerialBus() { Serial.begin(SERIAL_BAUD_RATE); }

void initTFT() {
    tft.init();
    tft.setRotation(1);
    tft.fillScreen(TFT_BLACK);
    tft.setCursor(0,0);
    tft.setTextColor(TFT_WHITE);
    tft.setTextSize(3);
}
