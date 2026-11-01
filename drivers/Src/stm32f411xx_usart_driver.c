#include "stm32f411xx_usart_driver.h"
#include "stm32f411xx.h"
#include "stm32f411xx_rcc_driver.h"

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
void USART_Init(USART_Handle_TypeDef *pUSARTHandle)
{

    uint32_t cr1, cr2, cr3;
    cr1 = 0; cr2 = 0; cr3 = 0;

    /*****************Configuring CR1 register*********************/

    // Configuring a mode TX, RX, TX_RX
    if (pUSARTHandle->USART_Config.USART_Mode == USART_MODE_TX_ONLY)
    {
        cr1 |= (1U << USART_CR1_TE);
    } 
    else if (pUSARTHandle->USART_Config.USART_Mode == USART_MODE_RX_ONLY)
    {
        cr1 |= (1U << USART_CR1_RE);
    } 
    else if (pUSARTHandle->USART_Config.USART_Mode == USART_MODE_TX_RX)
    {
        cr1 |= (1U << USART_CR1_TE);
        cr1 |= (1U << USART_CR1_RE);
    }

    // Configuring word length
    cr1 |= (pUSARTHandle->USART_Config.USART_WordLength << USART_CR1_M);

    // Configuring parity control
    if (pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_CONTROL_ENABLED_EVEN)
    {
        cr1 |= (1U << USART_CR1_PCE);
    } 
    else if (pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_CONTROL_ENABLED_ODD)
    {
        cr1 |= (1U << USART_CR1_PCE);
        cr1 |= (1U << USART_CR1_PS);
    }

    pUSARTHandle->pUSARTx->CR1 = cr1;

    /*****************Configuring CR2 register*********************/

    // Configuring number of stop bits
    cr2 |= (pUSARTHandle->USART_Config.USART_NumberOfStopBits << USART_CR2_STOP);

    pUSARTHandle->pUSARTx->CR2 = cr2;

    /*****************Configuring CR3 register*********************/

    // Configuring hardware flow control

    if (pUSARTHandle->USART_Config.USART_HardwareFlowControl == USART_HARDWARE_FLOW_CONTROL_ENABLED_CTS)
    {
        cr3 |= (1U << USART_CR3_CTSE);
    } 
    else if (pUSARTHandle->USART_Config.USART_HardwareFlowControl == USART_HARDWARE_FLOW_CONTROL_ENABLED_RTS)
    {
        cr3 |= (1U << USART_CR3_RTSE);
    } 
    else if (pUSARTHandle->USART_Config.USART_HardwareFlowControl == USART_HARDWARE_FLOW_CONTROL_ENABLED_CTS_RTS)
    {
        cr3 |= (1U << USART_CR3_CTSE);
        cr3 |= (1U << USART_CR3_RTSE);
    }

    pUSARTHandle->pUSARTx->CR3 = cr3;

    /*****************Configuring BRR register*********************/

    USART_SetBaudRate(pUSARTHandle->pUSARTx, pUSARTHandle->USART_Config.USART_Baudrate);

}

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
void USART_DeInit(USART_Reg_TypeDef *pUSARTx)
{
    if (pUSARTx == USART1)
    {
        RCC->APB2RSTR |= (1U << 4U);
        RCC->APB2RSTR &= ~(1U << 4U);
    } 
    else if (pUSARTx == USART2)
    {
        RCC->APB1RSTR |= (1U << 17U);
        RCC->APB1RSTR &= ~(1U << 17U);
    } 
    else if (pUSARTx == USART6)
    {
        RCC->APB2RSTR |= (1U << 5U);
        RCC->APB2RSTR &= ~(1U << 5U);
    }
}

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
    } 
    else 
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
    } 
    else
    {
        pUSARTx->CR1 &= ~(1U << USART_CR1_UE);
    }
}

/********************************************************************
 * @fn                  - USART_SetBaudRate
 *
 * @brief               - Sets the baudrate to BRR register
 *
 * @param[in]           - pUSARTx: base address
 * @param[in]           - BaudRate: choosen baud rate
 *
 * @return              - none
 *
 * @Note                - none
 *
 */
void USART_SetBaudRate(USART_Reg_TypeDef *pUSARTx, uint32_t BaudRate)
{
    // For APB clock
    uint32_t PCLKx;

    // coded number
    uint32_t USARTDIV;

    // For mantissa & fraction values
    uint32_t mantissa, fraction;

    uint32_t brr = 0;

    if ((pUSARTx == USART1) || (pUSARTx == USART6))
    {
        PCLKx = RCC_GetPCLK2Value();
    } 
    else
    {
        PCLKx = RCC_GetPCLK1Value();
    }

    if (pUSARTx->CR1 & (1U << USART_CR1_OVER8))
    {
        USARTDIV = ((PCLKx / (8 * BaudRate)) * 100);
    } 
    else
    {
        USARTDIV = ((PCLKx / (16 * BaudRate)) * 100);
    }

    mantissa = USARTDIV / 100;

    brr |= (mantissa << 4U);

    fraction = USARTDIV % 100;

    if (pUSARTx->CR1 & (1U << USART_CR1_OVER8))
    {
        fraction = (((fraction * 8) + 50) / 100) & ((uint8_t)0x07);
    } 
    else
    {
        fraction = (((fraction * 16) + 50) / 100) & ((uint8_t)0x0F);
    }

    brr |= fraction;
    
    pUSARTx->BRR = brr;
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