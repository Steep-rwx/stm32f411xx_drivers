

#include "stm32f411xx_gpio_driver.h"
#include "stm32f411xx.h"
#include <stdint.h>



/********************************************************************
 * @fn                  - GPIO_PeriClockControl
 *
 * @brief               - Function which enables/disables clock for choosed GPIO
 *
 * @param[in]           - pGPIOx: GPIO base address
 * @param[in]           - enOrDi: ENABLE or DISABLE macro
 * @param[in]           -
 *
 * @return              - none
 *
 * @Note                - none
 *
 */
void GPIO_PeriClockControl(GPIO_Reg_TypeDef *pGPIOx, uint8_t enOrDi)
{
    uint32_t index = ((uint32_t)pGPIOx - (uint32_t)GPIOA) / (0x0400);

    if (index > 7) return;

    if(enOrDi == ENABLE) 
    {
        RCC->AHB1ENR |= (1U << index);
    } else
    {
        RCC->AHB1ENR &= ~(1U << index);
    }
}


/********************************************************************
 * @fn                  - GPIO_Handler_TypeDef
 *
 * @brief               - Initializes the specifies pin
 *
 * @param[in]           - pGPIOHandle: A structure that contains pin base address and pin config
 * @param[in]           - 
 * @param[in]           -
 *
 * @return              - none
 *
 * @Note                - none
 *
 */
void GPIO_Init(GPIO_Handle_TypeDef *pGPIOHandle)
{

    uint32_t temp = 0;

    /* Setting mode */

    if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_AN)
    {
        temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
        pGPIOHandle->pGPIOx->MODER = |temp;
    } else
    {
        //TODO interrupt mode
    }

    temp = 0;
    
    /* Setting speed */
    temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
    pGPIOHandle->pGPIOx->OSPEEDR |= temp;
    temp = 0;

    /* Setting pupd */
    temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPdControl << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
    pGPIOHandle->pGPIOx->PUPDR |= temp;
    temp = 0;

    /* Setting output type*/
    temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinOPType << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
    pGPIOHandle->pGPIOx->OTYPER |= temp;
    temp = 0;

    if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_AF)
    {
        uint8_t AFR_choose = (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 8);
        uint8_t AFR_pin_pos = (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 8);
        pGPIOHandle->pGPIOx->AFR[AFR_choose] |= (pGPIOHandle->GPIO_PinConfig.GPIO_PinAltFunMode << (4 * AFR_pin_pos));
    }

}



/********************************************************************
 * @fn                  - GPIO_Reg_TypeDef
 *
 * @brief               - Deinitializes the specified pin
 *
 * @param[in]           - pGPIOHandle: A structure that contains pin base address and pin config
 * @param[in]           - 
 * @param[in]           -
 *
 * @return              - none
 *
 * @Note                - none
 *
 */
void GPIO_DeInit(GPIO_Reg_TypeDef *pGPIOx)
{

}





/********************************************************************
 * @fn                  - GPIO_ReadFromInputPin
 *
 * @brief               - Reads information from pin in the input mode
 *
 * @param[in]           - pGPIOx: base address of GPIO
 * @param[in]           - pinNumber: number of choosed pin
 * @param[in]           -
 *
 * @return              - Readed value from pin
 *
 * @Note                - none
 *
 */
uint8_t GPIO_ReadFromInputPin(GPIO_Reg_TypeDef *pGPIOx, uint8_t pinNumber)
{

}


/********************************************************************
 * @fn                  - GPIO_ReadFromInputPort
 *
 * @brief               - Reads information from port (16 pins)
 *
 * @param[in]           - pGPIOx: base address of GPIO
 * @param[in]           - 
 * @param[in]           -
 *
 * @return              - Readed value from port
 *
 * @Note                - none
 *
 */
uint16_t GPIO_ReadFromInputPort(GPIO_Reg_TypeDef *pGPIOx)
{
    
}


/********************************************************************
 * @fn                  - GPIO_WriteToOutputPin
 *
 * @brief               - Writes a value to pin in output mode
 *
 * @param[in]           - pGPIOx: base address of GPIO
 * @param[in]           - pinNumber: number of pin to write
 * @param[in]           - value: value that need to write (0 or 1)
 *
 * @return              - none
 *
 * @Note                - none
 *
 */
void GPIO_WriteToOutputPin(GPIO_Reg_TypeDef *pGPIOx, uint8_t pinNumber, uint8_t value)
{

}



/********************************************************************
 * @fn                  - GPIO_WriteToOutputPort
 *
 * @brief               - Writes a value to port in output mode
 *
 * @param[in]           - pGPIOx: base address of GPIO
 * @param[in]           - value: a value that need to write (0x3 - will be 1 to pin 0 and 1 to pin 1)
 * @param[in]           -
 *
 * @return              - none
 *
 * @Note                - none
 *
 */
void GPIO_WriteToOutputPort(GPIO_Reg_TypeDef *pGPIOx, uint16_t value)
{

}




/********************************************************************
 * @fn                  - GPIO_ToggleOutputPin
 *
 * @brief               - Toggles output pin
 *
 * @param[in]           - pGPIOx: base address of GPIO port
 * @param[in]           - pinNumber: a number of choosed pin
 * @param[in]           -
 *
 * @return              - none
 *
 * @Note                - none
 *
 */
void GPIO_ToggleOutputPin(GPIO_Reg_TypeDef *pGPIOx, uint8_t pinNumber)
{

}


/********************************************************************
 * @fn                  - GPIO_IRQConfig
 *
 * @brief               - Configures IRQ from number
 *
 * @param[in]           - IRQNumber: Number choosed IRQ
 * @param[in]           - IRQPriority: Priority of IRQ
 * @param[in]           - enOrDi: ENABLE or DISABLE macro
 *
 * @return              - none
 *
 * @Note                - none
 *
 */
void GPIO_IRQConfig(uint8_t IRQNumber, uint8_t IRQPriority, uint8_t enOrDi)
{

}



/********************************************************************
 * @fn                  - GPIO_IRQHandling
 *
 * @brief               - Clears pending interrupt
 *
 * @param[in]           - pinNumber: number which need to clear
 * @param[in]           - 
 * @param[in]           -
 *
 * @return              - none
 *
 * @Note                - none
 *
 */
void GPIO_IRQHandling(uint8_t pinNumber)
{

}