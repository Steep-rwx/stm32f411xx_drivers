#include <Arduino.h>

#define UART_RX_PIN 16
#define UART_TX_PIN 17
#define UART_BAUD   115200

void setup() {
  Serial.begin(115200);
  Serial2.begin(UART_BAUD, SERIAL_8N1, UART_RX_PIN, UART_TX_PIN);

}

void loop() {
  if (Serial2.available()) {
    uint8_t buf[64];
    size_t len = Serial2.readBytes(buf, min((size_t)Serial2.available(), sizeof(buf)));

    Serial.write(buf, len);
    Serial.println();
  }
}