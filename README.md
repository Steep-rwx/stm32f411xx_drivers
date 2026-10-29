# STM32 Bare-Metal Drivers

Учебный репозиторий с реализацией драйверов для микроконтроллера **STM32F411** (ARM Cortex-M4) на C (Register Level).

## GOAL:

Разработка драйверов базовых интерфейсов:
- [x] **GPIO**
- [x] **SPI**
- [x] **I2C**
- [ ] **USART** **(в разработке)**

---

## EXAMPLES:

### GPIO Driver
*(Примеры будут добавлены позже)*

---


### SPI Driver
Все примеры протестированы с использованием логического анализатора (Saleae) и отладчика ST-Link.

1. **[SPI Tx Test](Src/examples/spi/spitest/README.md)** — Базовая проверка передачи данных (`SPI_SendData`) и сигналов на логическом анализаторе.
2. **[STM32 to ESP32 Tx](Src/examples/spi/spi_esp_communication/README.md)** — Однонаправленная передача данных с STM32 на ESP32.
3. **[STM32 to ESP32 Full-Duplex (Tx/Rx)](Src/examples/spi/spi_esp_tx_rx_test/README.md)** — Полнодуплексный обмен данными (Tx/Rx) с проверкой в STM32CubeIDE debugger и Saleae.
4. **[SPI TX and RX interrupt functions tests](Src/examples/spi/spi_tx_rx_interrupt/README.md)** - Тестирование функций прерываний обмена данными с проверкой в STM32CubeIDE и Saleae.


## HARDWARE & SOFTWARE

* **MCU:** STM32F411CEU6 (Black Pill)
* **Slave-MCU:** ESP32 DevKit v1
* **Debugging:** Saleae Logic Analyzer, ST-Link v2
* **IDE:** VS Code with STM32CubeIDE extension