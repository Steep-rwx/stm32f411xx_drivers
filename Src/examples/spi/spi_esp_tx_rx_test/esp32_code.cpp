#include <Arduino.h>
#include "driver/spi_slave.h"

#define SPI_SCK   18
#define SPI_MISO  19
#define SPI_MOSI  23
#define SPI_SS     5

#define SPI_HOST_ID  SPI3_HOST   // VSPI
#define BUF_SIZE     32          // кратно 4 для DMA

WORD_ALIGNED_ATTR uint8_t rxBuf[BUF_SIZE];
WORD_ALIGNED_ATTR uint8_t txBuf[BUF_SIZE];

void SPI_SlaveInit(void)
{
  spi_bus_config_t buscfg = {};
  buscfg.mosi_io_num = SPI_MOSI;
  buscfg.miso_io_num = SPI_MISO;
  buscfg.sclk_io_num = SPI_SCK;
  buscfg.quadwp_io_num = -1;
  buscfg.quadhd_io_num = -1;

  spi_slave_interface_config_t slvcfg = {};
  slvcfg.mode = 0;
  slvcfg.spics_io_num = SPI_SS;
  slvcfg.queue_size = 1;
  slvcfg.flags = 0;

  gpio_set_pull_mode((gpio_num_t)SPI_MOSI, GPIO_PULLUP_ONLY);
  gpio_set_pull_mode((gpio_num_t)SPI_SCK,  GPIO_PULLUP_ONLY);
  gpio_set_pull_mode((gpio_num_t)SPI_SS,   GPIO_PULLUP_ONLY);

  esp_err_t ret = spi_slave_initialize(SPI_HOST_ID, &buscfg, &slvcfg, SPI_DMA_CH_AUTO);
  if (ret != ESP_OK) {
    Serial.printf("spi_slave_initialize failed: %d\n", ret);
  }
}

void setup()
{
  Serial.begin(9600);

  // Строка, которую слейв отдаёт на MISO в каждой транзакции
  memset(txBuf, 0, BUF_SIZE);
  memcpy(txBuf, "Hello world!", 12);

  SPI_SlaveInit();
  Serial.println("Slave Initialized");
}

void loop()
{
  memset(rxBuf, 0, BUF_SIZE);

  spi_slave_transaction_t t = {};
  t.length    = BUF_SIZE * 8;
  t.tx_buffer = txBuf;          // не меняется между транзакциями
  t.rx_buffer = rxBuf;

  esp_err_t ret = spi_slave_transmit(SPI_HOST_ID, &t, portMAX_DELAY);
  if (ret != ESP_OK) {
    Serial.printf("transmit error: %d\n", ret);
    return;
  }

  Serial.printf("transaction done, trans_len=%u bits\n", (unsigned)t.trans_len);
}