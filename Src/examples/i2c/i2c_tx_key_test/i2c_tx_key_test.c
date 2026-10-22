
#include "stm32f411xx.h"
#include "stm32f411xx_gpio_driver.h"
#include "stm32f411xx_i2c_driver.h"
#include "stm32f411xx_spi_driver.h"

#include <stdint.h>
#include <string.h>


//I2C1: PB6 - SCL, PB7 - SDA

I2C_Handle_TypeDef I2C1Handle;

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
    I2C1Handle.I2C_Config.I2C_DeviceAddress = 0x28;
    

    I2C_Init(&I2C1Handle);
}

void GPIO_Button_Init(void)
{
    GPIO_Handle_TypeDef gpio_key;

    gpio_key.pGPIOx = GPIOA;
    gpio_key.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_0;
    gpio_key.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
    gpio_key.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_LOW;
    gpio_key.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;


    GPIO_Init(&gpio_key);
}


int main(void)
{
    uint8_t user_data[] = "Hello world!";

    I2C1_GPIOInits();

    GPIO_Button_Init();

    I2C1_Inits();

    while(1)
    {
        while((GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_0)));

        for(volatile uint32_t i = 0; i < 500000; i++);

        I2C_PeripheralControl(I2C1, ENABLE); 

        I2C_MasterSendData(&I2C1Handle, user_data, strlen((char*) user_data), I2C1Handle.I2C_Config.I2C_DeviceAddress, REPEATED_START_DISABLE);

    }
    return 0;
}