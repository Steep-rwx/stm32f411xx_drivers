

#include "stm32f411xx_gpio_driver.h"



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
void GPIO_Init(GPIO_Handler_TypeDef *pGPIOHandle)
{

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