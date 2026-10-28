
#include "stm32f411xx.h"
#include "stm32f411xx_gpio_driver.h"
#include "stm32f411xx_i2c_driver.h"
#include "stm32f411xx_spi_driver.h"

#include <stdint.h>
#include <string.h>


//I2C1: PB6 - SCL, PB7 - SDA

I2C_Handle_TypeDef I2C1Handle;

volatile uint8_t button_pressed = 0;

void I2C1_GPIOInits(void)
{
    GPIO_Handle_TypeDef I2C1Pins;
    I2C1Pins.pGPIOx = GPIOB;
    I2C1Pins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_AF;
    I2C1Pins.GPIO_PinConfig.GPIO_PinAltFunMode = 4;
    I2C1Pins.GPIO_PinConfig.GPIO_PinOPType = GPIO_OUT_TYPER_OD;
    I2C1Pins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;
    I2C1Pins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

    //SCL
    I2C1Pins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_6;
    GPIO_Init(&I2C1Pins);

    //SDA
    I2C1Pins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_7;
    GPIO_Init(&I2C1Pins);
}

void I2C1_Inits(void)
{
    I2C1Handle.pI2Cx = I2C1;
    I2C1Handle.I2C_Config.I2C_ACKControl = I2C_ACK_ENABLE;
    I2C1Handle.I2C_Config.I2C_FMDutyCycle = I2C_FM_DUTY_2;
    I2C1Handle.I2C_Config.I2C_SCLSpeed = I2C_SCL_SPEED_SM;
    I2C1Handle.I2C_Config.I2C_DeviceAddress = 0xF;
    

    I2C_Init(&I2C1Handle);

    I2C_IRQPriorityConfig(IRQ_NO_I2C1_EV, NVIC_IRQ_PRIO14);
    I2C_IRQConfig(IRQ_NO_I2C1_EV, ENABLE);
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
    uint8_t user_data[] = "Hello world!";

    I2C1_GPIOInits();

    GPIO_Button_Init();

    I2C1_Inits();

    while(1)
    {
        while(!button_pressed);

        I2C_MasterSendDataIT(&I2C1Handle, 
                           user_data, 
                           strlen((char*) user_data), 
                           0x28, 
                           I2C_REPEATED_START_DISABLE);
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

void I2C1_EV_IRQHandler(void)
{
    I2C_EV_IRQHandling(&I2C1Handle);
}