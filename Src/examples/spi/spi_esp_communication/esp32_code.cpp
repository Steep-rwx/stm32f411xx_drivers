/* SPI Slave Demo for ESP32 (VSPI / SPI3_HOST)
 *
 * SPI pin numbers (ESP32 default VSPI):
 * SCK   18  // Serial Clock
 * MISO  19  // Master In Slave Out
 * MOSI  23  // Master Out Slave In
 * SS     5  // Slave Select (CS)
 *
 * Протокол: первый байт = длина, далее данные.
 * Мастер должен передать всё одной транзакцией (CS низкий всё время).
 */
#include <Arduino.h>
#include "driver/spi_slave.h"

#define SPI_SCK   18
#define SPI_MISO  19
#define SPI_MOSI  23
#define SPI_SS     5

#define SPI_HOST_ID  SPI3_HOST   // VSPI
#define MAX_DATA_LEN 500
#define BUF_SIZE     504         // 1 байт длины + данные, кратно 4 для DMA

WORD_ALIGNED_ATTR uint8_t rxBuf[BUF_SIZE];
WORD_ALIGNED_ATTR uint8_t txBuf[BUF_SIZE];
char dataBuff[MAX_DATA_LEN + 1];

void SPI_SlaveInit(void)
{
  spi_bus_config_t buscfg = {};
  buscfg.mosi_io_num = SPI_MOSI;
  buscfg.miso_io_num = SPI_MISO;
  buscfg.sclk_io_num = SPI_SCK;
  buscfg.quadwp_io_num = -1;
  buscfg.quadhd_io_num = -1;

  spi_slave_interface_config_t slvcfg = {};
  slvcfg.mode = 0;               // SPI mode 0 (CPOL=0, CPHA=0)
  slvcfg.spics_io_num = SPI_SS;
  slvcfg.queue_size = 1;
  slvcfg.flags = 0;

  // Подтяжки, чтобы линии не "плавали", пока мастер не подключён
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
  SPI_SlaveInit();
  Serial.println("Slave Initialized");
}

void loop()
{
  memset(rxBuf, 0, BUF_SIZE);
  memset(txBuf, 0, BUF_SIZE);

  spi_slave_transaction_t t = {};
  t.length    = BUF_SIZE * 8;   // максимум, в битах
  t.tx_buffer = txBuf;
  t.rx_buffer = rxBuf;

  Serial.println("Slave waiting for ss to go low");

  // Блокируется, пока мастер не опустит и снова не поднимет SS
  esp_err_t ret = spi_slave_transmit(SPI_HOST_ID, &t, portMAX_DELAY);
  if (ret != ESP_OK) {
    Serial.printf("transmit error: %d\n", ret);
    return;
  }

  Serial.printf("trans_len=%u bits\n", (unsigned)t.trans_len);
  for (int i = 0; i < 16; i++) Serial.printf("%02X ", rxBuf[i]);
  Serial.println();

  size_t rxBytes = t.trans_len / 8;       // сколько реально принято
  if (rxBytes == 0) return;

  uint16_t dataLen = rxBuf[0];            // первый байт — длина
  if (dataLen > rxBytes - 1) dataLen = rxBytes - 1;   // защита от выхода за пределы
  if (dataLen > MAX_DATA_LEN) dataLen = MAX_DATA_LEN;

  memcpy(dataBuff, &rxBuf[1], dataLen);
  dataBuff[dataLen] = '\0';

  Serial.println("Rcvd:");
  Serial.println(dataBuff);
  Serial.print("Length:");
  Serial.println(dataLen);
}