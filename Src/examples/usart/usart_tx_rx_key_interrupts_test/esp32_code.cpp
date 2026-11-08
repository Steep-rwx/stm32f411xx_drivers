#include <Arduino.h>

#define UART_RX_PIN 16
#define UART_TX_PIN 17
#define UART_BAUD   115200

void setup() {
  Serial.begin(115200);
  Serial2.begin(UART_BAUD, SERIAL_8N1, UART_RX_PIN, UART_TX_PIN);
}

void loop() {
  size_t n = Serial2.available();
  if (n > 0) {
    uint8_t buf[128];
    if (n > sizeof(buf)) n = sizeof(buf);

    size_t len = Serial2.readBytes(buf, n);
    Serial2.write(buf, len);

    Serial.printf("Echo %u bytes\n", (unsigned)len);
  }
}