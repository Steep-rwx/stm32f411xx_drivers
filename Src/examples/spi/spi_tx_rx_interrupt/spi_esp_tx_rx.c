
#include "stm32f411xx.h"
#include "stm32f411xx_gpio_driver.h"
#include "stm32f411xx_spi_driver.h"

#include <stdint.h>
#include <string.h>


//SPI1 AF05: PA4 - NSS PA5 - SCKL PA6 - MISO PA7 - MOSI

SPI_Handle_TypeDef SPI1Handle;

void SPI1_GPIOInits(void)
{
    GPIO_Handle_TypeDef SPIPins;
    SPIPins.pGPIOx = GPIOA;
    SPIPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_AF;
    SPIPins.GPIO_PinConfig.GPIO_PinAltFunMode = 5;
    SPIPins.GPIO_PinConfig.GPIO_PinOPType = GPIO_OUT_TYPER_PP;
    SPIPins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
    SPIPins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

    //SCKL
    SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_5;
    GPIO_Init(&SPIPins);

    //MOSI
    SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_7;
    GPIO_Init(&SPIPins);

    //MISO
    SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_6;
    GPIO_Init(&SPIPins);
    
    //NSS
    SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_4;
    GPIO_Init(&SPIPins);
}

void SPI1_Inits(void)
{

    SPI1Handle.pSPIx = SPI1;
    SPI1Handle.SPIConfig.SPI_BusConfig = SPI_BUS_CONFIG_FULLDUPLEX;
    SPI1Handle.SPIConfig.SPI_DeviceMode = SPI_DEVICE_MODE_MASTER;
    SPI1Handle.SPIConfig.SPI_SclkSpeed = SPI_SCLK_SPEED_DIV32;
    SPI1Handle.SPIConfig.SPI_DFF = SPI_DFF_8BIT;
    SPI1Handle.SPIConfig.SPI_CPOL = SPI_CPOL_LOW;
    SPI1Handle.SPIConfig.SPI_CPHA = SPI_CPHA_FIRST_CAPTURE;
    SPI1Handle.SPIConfig.SPI_SSM = SPI_SSM_ENABLED;
    SPI1Handle.SPIConfig.SPI_SSI = SPI_SSI_ENABLED;
    SPI1Handle.SPIConfig.SPI_SSOE = SPI_SSOE_DISABLED;

    SPI_Init(&SPI1Handle);

    SPI_IRQPriorityConfig(IRQ_SPI1, NVIC_IRQ_PRIO14);
    SPI_IRQConfig(IRQ_SPI1, ENABLE);
}

void GPIO_Button_Init(void)
{
    GPIO_Handle_TypeDef gpio_key;

    gpio_key.pGPIOx = GPIOA;
    gpio_key.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_0;
    gpio_key.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_FT;
    gpio_key.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_LOW;
    gpio_key.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;

    GPIO_Init(&gpio_key);

    GPIO_IRQPriorityConfig(IRQ_NO_EXTI0, NVIC_IRQ_PRIO15);
    GPIO_IRQConfig(IRQ_NO_EXTI0, ENABLE);
}

char user_data[] = "Hello world!";
char test_data[16] = "AAAAAA";

int main(void)
{

    SPI1_GPIOInits();
    GPIO_Button_Init();
    SPI1_Inits();


    SPI_PeripheralControl(SPI1, ENABLE);
    while(1)
    {

    }
    return 0;
}


void EXTI0_IRQHandler(void)
{
    GPIO_IRQHandling(GPIO_PIN_NO_0);
    if (SPI1Handle.TxState == SPI_READY)
    {
        SPI_SendDataIT(&SPI1Handle, (uint8_t*)user_data, strlen(user_data));
    }
}

void SPI1_IRQHandler(void)
{
    SPI_IRQHandling(&SPI1Handle);
}