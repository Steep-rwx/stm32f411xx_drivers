#include <Arduino.h>
#include <Wire.h>

#define I2C_DEV_ADDR 0x08
#define SDA_PIN 21
#define SCL_PIN 22

static const uint8_t txBuffer[] = "Hello world";
static const size_t  txLen      = sizeof(txBuffer) - 1;

void onRequest() {
    Wire.slaveWrite(txBuffer, txLen);
}

void setup() {
    Serial.begin(115200);

    Wire.onRequest(onRequest);
    Wire.begin((uint8_t)I2C_DEV_ADDR, SDA_PIN, SCL_PIN, 100000);

    Wire.slaveWrite(txBuffer, txLen);

}

void loop() {
    delay(10);
}