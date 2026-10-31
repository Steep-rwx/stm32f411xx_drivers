#include "stm32f411xx_usart_driver.h"
#include "stm32f411xx.h"

#include <stdint.h>


/********************************************************************
 * @fn                  - USART_PeriClockControl
 *
 * @brief               - Function which enables/disables clock for choosen USART
 *
 * @param[in]           - pUSARTx: USART base address
 * @param[in]           - enOrDi: ENABLE or DISABLE macro
 *
 * @return              - none
 *
 * @Note                - none
 *
 */
void USART_PeriClockControl(USART_Reg_TypeDef *pUSARTx, uint8_t EnOrDi)
{
    if (EnOrDi)
    {
        if (pUSARTx == USART1)      {USART1_PCLK_EN();}
        else if (pUSARTx == USART2) {USART2_PCLK_EN();}
        else if (pUSARTx == USART6) {USART6_PCLK_EN();}
    } else
    {
        if (pUSARTx == USART1)      {USART1_PCLK_DI();}
        else if (pUSARTx == USART2) {USART2_PCLK_DI();}
        else if (pUSARTx == USART6) {USART6_PCLK_DI();}
    }
}