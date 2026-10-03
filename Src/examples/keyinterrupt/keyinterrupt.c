
#include "stm32f411xx.h"
#include "stm32f411xx_gpio_driver.h"

#include <stdint.h>
#include <string.h>


void delay(void)
{
    for(uint32_t i = 0; i < 500000; i++);
}


int main(void)
{
    GPIO_Handle_TypeDef ledunit, gpio_key;
    
    memset(&ledunit, 0, sizeof(ledunit));
    memset(&gpio_key, 0, sizeof(gpio_key));

    ledunit.pGPIOx = GPIOC;
    ledunit.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
    ledunit.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
    ledunit.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_LOW;
    ledunit.GPIO_PinConfig.GPIO_PinOPType = GPIO_OUT_TYPER_PP;
    ledunit.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

    gpio_key.pGPIOx = GPIOA;
    gpio_key.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_0;
    gpio_key.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_FT;
    gpio_key.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_LOW;
    gpio_key.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;

    GPIO_PeriClockControl(ledunit.pGPIOx, ENABLE);
    GPIO_PeriClockControl(gpio_key.pGPIOx, ENABLE);

    GPIO_Init(&ledunit);
    GPIO_Init(&gpio_key);

    GPIO_IRQPriorityConfig(IRQ_NO_EXTI0, NVIC_IRQ_PRIO15);
    GPIO_IRQConfig(IRQ_NO_EXTI0, ENABLE);

    while(1);

}

void EXTI0_IRQHandler(void)
{
    delay();
    GPIO_IRQHandling(GPIO_PIN_NO_0);
    GPIO_ToggleOutputPin(GPIOC, GPIO_PIN_NO_13);
}