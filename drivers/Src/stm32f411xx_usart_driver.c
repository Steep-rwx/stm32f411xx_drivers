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

/********************************************************************
 * @fn                  - USART_Init
 *
 * @brief               - Initializes the specifies USART
 *
 * @param[in]           - pUSARTHandle: A structure that contains pin base address and pin config
 *
 * @return              - none
 *
 * @Note                - none
 *
 */
void USART_Init(USART_Handle_TypeDef *pUSARTHandle);

/********************************************************************
 * @fn                  - USART_DeInit
 *
 * @brief               - Deinitializes the specified pin
 *
 * @param[in]           - pUSARTx: A base address of USARTx
 *
 * @return              - none
 *
 * @Note                - none
 *
 */
void USART_DeInit(USART_Reg_TypeDef *pUSARTx);

/********************************************************************
 * @fn                  - USART_SendData
 *
 * @brief               - Send data through USART
 *
 * @param[in]           - pUSARTx: base address
 * @param[in]           - pTxBuffer: Tx buffer
 * @param[in]           - Length: length of info
 *
 * @return              - none
 *
 * @Note                - This is blocking call
 *
 */
void USART_SendData(USART_Handle_TypeDef *pUSARTHandle, uint8_t *pTxBuffer, uint32_t Length);

/********************************************************************
 * @fn                  - USART_ReceiveData
 *
 * @brief               - Receive data through USART
 *
 * @param[in]           - pUSARTx: base address
 * @param[in]           - pRxBuffer: Rx buffer
 * @param[in]           - Length: length of info
 *
 * @return              - none
 *
 * @Note                - none
 *
 */
void USART_ReceiveData(USART_Handle_TypeDef *pUSARTHandle, uint8_t *pRxBuffer, uint32_t Length);

/*******************************************************************
 * @fn                  - USART_IRQConfig
 *
 * @brief               - Configures IRQ from number
 *
 * @param[in]           - IRQNumber: Number choosed IRQ
 * @param[in]           - EnOrDi: ENABLE or DISABLE macro
 *
 * @return              - none
 *
 * @Note                - none
 *
 */
void USART_IRQConfig(uint8_t IRQNumber, uint8_t EnOrDi)
{
    if (IRQNumber >= 240) return;

    uint8_t ipr_idx = IRQNumber / 32;
    uint8_t bit_pos = IRQNumber % 32;
    if (EnOrDi)
    {
        NVIC->ISER[ipr_idx] |= (1UL << bit_pos);
    } else 
    {
        NVIC->ICER[ipr_idx] |= (1UL << bit_pos);
    }
}

/*******************************************************************
 * @fn                  - USART_IRQPriority
 *
 * @brief               - Configures IRQ Priority
 *
 * @param[in]           - IRQNumber: Number choosed IRQ
 * @param[in]           - IRQPriority: Choosed priority 0-15
 *
 * @return              - none
 *
 * @Note                - none
 *
 */
void USART_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority)
{
    if (IRQNumber >= 240) return;

    uint8_t ipr_idx = IRQNumber / 4;
    uint8_t byte_shift = ((IRQNumber % 4) * 8);

    uint8_t shift_amount = (byte_shift + (8 - NO_PR_BITS_IMPLEMENTED));

    NVIC->IPR[ipr_idx] &= ~(0xFFUL << byte_shift);

    NVIC->IPR[ipr_idx] |= ((uint32_t)IRQPriority << shift_amount);
}

/********************************************************************
 * @fn                  - USART_PeripheralControl
 *
 * @brief               - Enables USART choosen peripheral
 *
 * @param[in]           - pUSARTx: base address
 * @param[in]           - EnOrDi: ENABLE or DISABLE
 *
 * @return              - none
 *
 * @Note                - none
 *
 */
void USART_PeripheralControl(USART_Reg_TypeDef *pUSARTx, uint8_t EnOrDi)
{
    if (EnOrDi)
    {
        pUSARTx->CR1 |= (1U << USART_CR1_UE);
    } else
    {
        pUSARTx->CR1 &= ~(1U << USART_CR1_UE);
    }
}

/********************************************************************
 * @fn                  - USART_ApplicationEventCallback
 *
 * @brief               - Application callback function
 *
 * @param[in]           - pUSARTHandle: pointer to the handle of the USART peripheral
 * @param[in]           - ApplicationEvent: event code
 *
 * @return              - none
 *
 * @Note                - none
 *
 */
__attribute__((weak)) void USART_ApplicationEventCallback(USART_Handle_TypeDef *pUSARTHandle, uint8_t ApplicationEvent)
{

}