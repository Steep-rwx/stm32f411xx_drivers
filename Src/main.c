
#include "stm32f411xx.h"
#include "stm32f411xx_gpio_driver.h"

#include <stdint.h>


int main(void)
{
    GPIO_Handle_TypeDef ledunit, gpio_key;
    ledunit.pGPIOx = GPIOC;

    ledunit.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
    ledunit.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
    ledunit.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_LOW;
    ledunit.GPIO_PinConfig.GPIO_PinOPType = GPIO_OUT_TYPER_PP;
    ledunit.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

    gpio_key.pGPIOx = GPIOA;
    gpio_key.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_0;
    gpio_key.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
    gpio_key.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_LOW;
    gpio_key.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;

    GPIO_PeriClockControl(ledunit.pGPIOx, ENABLE);
    GPIO_PeriClockControl(gpio_key.pGPIOx, ENABLE);

    GPIO_Init(&ledunit);
    GPIO_Init(&gpio_key);

    while(1)
    {
        if (GPIO_ReadFromInputPin(gpio_key.pGPIOx, gpio_key.GPIO_PinConfig.GPIO_PinNumber) != ENABLE)
        {
            GPIO_WriteToOutputPin(ledunit.pGPIOx, ledunit.GPIO_PinConfig.GPIO_PinNumber, ENABLE);
        } else
        {
            GPIO_WriteToOutputPin(ledunit.pGPIOx, ledunit.GPIO_PinConfig.GPIO_PinNumber, DISABLE);
        }
    }
}