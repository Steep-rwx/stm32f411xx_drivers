# stm32f411xx_drivers

## Main Goal;
Написать драйвера для GPIO, SPI, I2C, USART и протестить их через examples


## GPIO driver:


### Examples:


## SPI driver:


### Examples:
1. В данном примере реализовано использование функции SPI_SendData, также прикреплён тест через логический анализатор:
[spitest](Src/examples/spi/spitest/README.md)
2. В данном примере реализована связь STM32 с ESP32, также прикреплены скриншоты тестов приёма данных на ESP32, а также тесты при помощи логического анализатора:
[spi_esp_communication](Src/examples/spi/spi_esp_communication/README.md)
3. В данном примере реализована связь STM32 с ESP32, также реализованы отправка данных и приём, протестировано через логический анализатор и дебаггер STM32CubeIDE:
[spi_esp_tx_rx_test](Src/examples/spi/spi_esp_tx_rx_test/README.md)