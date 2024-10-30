#include <Arduino.h>
#include <TFT_eSPI.h>
#include <Adafruit_CAP1188.h>

#define SECOND 1

/*
 * peripheral constants
 */
#define SERIAL_BAUD_RATE 9600

// Capacitive touch sensor constants
// Reset Pin is used for I2C or SPI
#define CAP1188_RESET  9

// These are defined for software SPI, for hardware SPI, check your
// board's SPI pins in the Arduino documentation
#define CAP1188_MOSI  11
#define CAP1188_MISO  12
#define CAP1188_CLK  13

// For I2C, connect SDA to your Arduino's SDA pin, SCL to SCL pin
// Use I2C, with reset pin
Adafruit_CAP1188 cap = Adafruit_CAP1188();

/*
 * peripheral objects
 */
TFT_eSPI tft = TFT_eSPI();

/*
 * other variables
 */
uint8_t numSensorsTouchedPreviously = -1;

void initTFT();

void initBoardSerialBus();

void initCapacitiveTouchSensor();

void setup() {
    initBoardSerialBus();
    Serial.println("Initializing...");
    initTFT();
    initCapacitiveTouchSensor();
    Serial.println("All systems up");
}

void loop() {

    uint8_t numSensorsTouched = 0;
    uint8_t touchSensorBits = cap.touched();
    if (touchSensorBits != 0) {
        for (uint8_t i=0; i<8; i++) {
            if (touchSensorBits & (1 << i)) {
                Serial.print("C"); Serial.print(i+1); Serial.print("\t");
                numSensorsTouched++;
            }
        }
        Serial.println();
    }

    if (numSensorsTouchedPreviously != numSensorsTouched) {
        numSensorsTouchedPreviously = numSensorsTouched;
        tft.fillScreen(TFT_BLACK);
        tft.setCursor(50, 80);
        tft.print(numSensorsTouched);
    }
    delay(50);
}

void initBoardSerialBus() { Serial.begin(SERIAL_BAUD_RATE); }

void initTFT() {
    tft.init();
    tft.setTextSize(16);
    tft.setTextColor(TFT_CYAN);
    tft.fillScreen(TFT_BLACK);
}

void initCapacitiveTouchSensor() {
    // Initialize the sensor, if using i2c you can pass in the i2c address
     if (!cap.begin()) {
        Serial.println("CAP1188 not found...");
        while (1);
    }
    Serial.println("CAP1188 found!");
}
