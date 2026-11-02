
#include "stm32f411xx.h"
#include "stm32f411xx_gpio_driver.h"
#include "stm32f411xx_usart_driver.h"


#include <stdint.h>
#include <string.h>


//USART1: PB6 - TX, PB7 - RX

USART_Handle_TypeDef USART1Handle;

volatile uint8_t button_pressed = 0;

void USART1_GPIOInits(void)
{
    GPIO_Handle_TypeDef USART1Pins;
    USART1Pins.pGPIOx = GPIOB;
    USART1Pins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_AF;
    USART1Pins.GPIO_PinConfig.GPIO_PinAltFunMode = 7;
    USART1Pins.GPIO_PinConfig.GPIO_PinOPType = GPIO_OUT_TYPER_PP;
    USART1Pins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;
    USART1Pins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

    //TX
    USART1Pins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_6;
    GPIO_Init(&USART1Pins);

    //RX
    USART1Pins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_7;
    GPIO_Init(&USART1Pins);
}

void USART1_Inits(void)
{
    USART1Handle.pUSARTx = USART1;
    USART1Handle.USART_Config.USART_Baudrate = USART_BAUDRATE_115200;
    USART1Handle.USART_Config.USART_Mode = USART_MODE_TX_RX;
    USART1Handle.USART_Config.USART_HardwareFlowControl = USART_HARDWARE_FLOW_CONTROL_DISABLED;
    USART1Handle.USART_Config.USART_ParityControl = USART_PARITY_CONTROL_DISABLED;
    USART1Handle.USART_Config.USART_WordLength = USART_WORD_LENGTH_8_BITS;
    USART1Handle.USART_Config.USART_NumberOfStopBits = USART_NUMBER_OF_STOP_BITS_1_0;
    
    USART_Init(&USART1Handle);
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


int main(void)
{
    uint8_t send_data[] = "Hello world!";

    USART1_GPIOInits();

    GPIO_Button_Init();

    USART1_Inits();

    USART_PeripheralControl(USART1Handle.pUSARTx, ENABLE);

    while(1)
    {
        while(!button_pressed);
        USART_SendData(&USART1Handle, send_data, 12);
        button_pressed = 0;
    }
    return 0;
}

void EXTI0_IRQHandler(void)
{
    GPIO_IRQHandling(GPIO_PIN_NO_0);
    for(volatile uint32_t i = 0; i < 500000; i++);
    button_pressed = 1;   
}