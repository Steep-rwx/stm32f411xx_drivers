
#include "stm32f411xx.h"
#include "stm32f411xx_gpio_driver.h"

#include <stdint.h>


int main(void)
{
    GPIO_Handle_TypeDef ledunit;
    ledunit.pGPIOx = GPIOC;

    ledunit.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
    ledunit.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
    ledunit.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_LOW;
    ledunit.GPIO_PinConfig.GPIO_PinOPType = GPIO_OUT_TYPER_PP;
    ledunit.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;


    GPIO_PeriClockControl(ledunit.pGPIOx, ENABLE);

    GPIO_Init(&ledunit);

    while(1)
    {
        GPIO_ToggleOutputPin(ledunit.pGPIOx, ledunit.GPIO_PinConfig.GPIO_PinNumber);
        for(uint32_t i = 0; i < 500000; i++);
    }
}