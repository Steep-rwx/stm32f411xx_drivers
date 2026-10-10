
#include "stm32f411xx.h"
#include "stm32f411xx_gpio_driver.h"
#include "stm32f411xx_spi_driver.h"

#include <stdint.h>
#include <string.h>


//SPI2 AF05: PB12 - NSS PB13 - SCKL PB14 - MISO PB15 - MOSI

void SPI2_GPIOInits(void)
{
    GPIO_Handle_TypeDef SPIPins;
    SPIPins.pGPIOx = GPIOB;
    SPIPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_AF;
    SPIPins.GPIO_PinConfig.GPIO_PinAltFunMode = 5;
    SPIPins.GPIO_PinConfig.GPIO_PinOPType = GPIO_OUT_TYPER_PP;
    SPIPins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
    SPIPins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

    //SCKL
    SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
    GPIO_Init(&SPIPins);

    //MOSI
    SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_15;
    GPIO_Init(&SPIPins);

    //MISO
    SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_14;
    GPIO_Init(&SPIPins);
    
    //NSS
    SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
    GPIO_Init(&SPIPins);
}

void SPI2_Inits(void)
{
    SPI_Handle_TypeDef SPI2Handle;

    SPI2Handle.pSPIx = SPI2;
    SPI2Handle.SPIConfig.SPI_BusConfig = SPI_BUS_CONFIG_FULLDUPLEX;
    SPI2Handle.SPIConfig.SPI_DeviceMode = SPI_DEVICE_MODE_MASTER;
    SPI2Handle.SPIConfig.SPI_SclkSpeed = SPI_SCLK_SPEED_DIV32;
    SPI2Handle.SPIConfig.SPI_DFF = SPI_DFF_8BIT;
    SPI2Handle.SPIConfig.SPI_CPOL = SPI_CPOL_LOW;
    SPI2Handle.SPIConfig.SPI_CPHA = SPI_CPHA_FIRST_CAPTURE;
    SPI2Handle.SPIConfig.SPI_SSM = SPI_SSM_ENABLED;

    SPI_Init(&SPI2Handle);
}


int main(void)
{
    char user_data[] = "Hello world!";

    SPI2_GPIOInits();

    SPI2_Inits();
    //enabling SPI2 peripheral
    SPI_PeripheralControl(SPI2, ENABLE);

    while(1)
    {
        SPI_SendData(SPI2, (uint8_t*) user_data, strlen(user_data));
        for(volatile uint32_t i = 0; i < 100000; i++);
    }

}