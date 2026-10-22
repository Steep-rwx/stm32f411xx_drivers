
#include "stm32f411xx.h"
#include "stm32f411xx_gpio_driver.h"
#include "stm32f411xx_spi_driver.h"

#include <stdint.h>
#include <string.h>


//SPI1 AF05: PA4 - NSS PA5 - SCKL PA6 - MISO PA7 - MOSI

SPI_Handle_TypeDef SPI2Handle;

volatile uint8_t button_pressed = 0;
volatile uint8_t tx_complete = 0;

volatile char ReadByte;

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
    SPIPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
    SPIPins.GPIO_PinConfig.GPIO_PinAltFunMode = 0;
    SPIPins.GPIO_PinConfig.GPIO_PinOPType = GPIO_OUT_TYPER_PP;
    SPIPins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
    SPIPins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
    
    GPIO_Init(&SPIPins);
}

void SPI2_Inits(void)
{

    SPI2Handle.pSPIx = SPI2;
    SPI2Handle.SPIConfig.SPI_BusConfig = SPI_BUS_CONFIG_FULLDUPLEX;
    SPI2Handle.SPIConfig.SPI_DeviceMode = SPI_DEVICE_MODE_MASTER;
    SPI2Handle.SPIConfig.SPI_SclkSpeed = SPI_SCLK_SPEED_DIV32;
    SPI2Handle.SPIConfig.SPI_DFF = SPI_DFF_8BIT;
    SPI2Handle.SPIConfig.SPI_CPOL = SPI_CPOL_LOW;
    SPI2Handle.SPIConfig.SPI_CPHA = SPI_CPHA_FIRST_CAPTURE;
    SPI2Handle.SPIConfig.SPI_SSM = SPI_SSM_ENABLED;
    SPI2Handle.SPIConfig.SPI_SSOE = SPI_SSOE_DISABLED;

    SPI_Init(&SPI2Handle);

    SPI_IRQPriorityConfig(IRQ_SPI2, NVIC_IRQ_PRIO14);
    SPI_IRQConfig(IRQ_SPI2, ENABLE);
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
    SPI2_GPIOInits();
    GPIO_Button_Init();
    SPI2_Inits();
    SPI_SSISet(SPI2, ENABLE);
    SPI_PeripheralControl(SPI2, ENABLE);

    while(1)
    {
        while(!button_pressed);
        
        GPIO_IRQConfig(IRQ_NO_EXTI0, DISABLE);

        tx_complete = 0;
        GPIO_WriteToOutputPin(GPIOB, GPIO_PIN_NO_12, RESET);
        
        while(SPI_SendDataIT(&SPI2Handle, (uint8_t*)user_data, 12) == SPI_BUSY_TX);
        
        while(!tx_complete);

        while(SPI_GetFlagStatus(SPI2, SPI_BUSY_FLAG));

        GPIO_WriteToOutputPin(GPIOB, GPIO_PIN_NO_12, SET);

        button_pressed = 0;

        GPIO_IRQConfig(IRQ_NO_EXTI0, ENABLE);
    }
    return 0;
}


void EXTI0_IRQHandler(void)
{
    GPIO_IRQHandling(GPIO_PIN_NO_0);
    for(volatile uint32_t i = 0; i < 500000; i++);
    button_pressed = 1;
    
}

void SPI2_IRQHandler(void)
{
    SPI_IRQHandling(&SPI2Handle);
}

void SPI_ApplicationEventCallback(SPI_Handle_TypeDef *pSPIHandle, uint8_t ApplicationEvent)
{
    if(ApplicationEvent == SPI_EVENT_TX_CMPLT)
    {
        tx_complete = 1;
    }
}