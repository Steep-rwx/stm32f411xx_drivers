#include <Arduino.h>
#include "driver/i2c.h"

#define I2C_SDA     21
#define I2C_SCL     22
#define I2C_PORT    I2C_NUM_1
#define SLAVE_ADDR  0x28
#define BUF_SIZE    256

void setup()
{
  Serial.begin(115200);
  while (!Serial);
  delay(1000);

  i2c_driver_delete(I2C_PORT);

  i2c_config_t conf = {};
  conf.mode = I2C_MODE_SLAVE;
  conf.sda_io_num = I2C_SDA;
  conf.scl_io_num = I2C_SCL;
  conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
  conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
  conf.slave.addr_10bit_en = 0;
  conf.slave.slave_addr = SLAVE_ADDR;

  esp_err_t err = i2c_param_config(I2C_PORT, &conf);
  if (err != ESP_OK) {
    Serial.printf("i2c_param_config failed: 0x%x\n", err);
    while(1);
  }

  err = i2c_driver_install(I2C_PORT, I2C_MODE_SLAVE, BUF_SIZE, BUF_SIZE, 0);
  if (err != ESP_OK) {
    Serial.printf("i2c_driver_install failed: 0x%x\n", err);
    while(1);
  }

  Serial.println("I2C Slave Initialized Successfully on I2C_NUM_1!");
}

void loop()
{
  uint8_t rxBuf[BUF_SIZE];
  memset(rxBuf, 0, sizeof(rxBuf));

  int len = i2c_slave_read_buffer(I2C_PORT, rxBuf, sizeof(rxBuf), pdMS_TO_TICKS(1000));

  if (len > 0) {
    Serial.printf("Received %d bytes: ", len);
    for (int i = 0; i < len; i++) {
      Serial.printf("%02X ", rxBuf[i]);
    }
    Serial.print(" Text: ");
    for (int i = 0; i < len; i++) {
      Serial.print((char)rxBuf[i]);
    }
    Serial.println();
  } 
  else if (len == 0) {
    Serial.println("Waiting");
  } 
  else {
    Serial.printf("ERROR (%d)\n", len);
    i2c_reset_rx_fifo(I2C_PORT);
    i2c_reset_tx_fifo(I2C_PORT);
  }
}