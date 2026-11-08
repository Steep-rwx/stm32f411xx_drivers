

#include "stm32f411xx_nvic_driver.h"
#include "stm32f411xx.h"


#include <stdint.h>

/*******************************************************************
 * @fn                  - NVIC_IRQConfig
 *
 * @brief               - Configures IRQ from number
 *
 * @param[in]           - IRQNumber: Number choosen IRQ
 * @param[in]           - enOrDi: ENABLE or DISABLE macro
 *
 * @return              - none
 *
 * @note                - none
 *
 */
void NVIC_IRQConfig(uint8_t IRQNumber, uint8_t enOrDi)
{
    if (IRQNumber >= 240) return;

    if (enOrDi)
    {
        NVIC->ISER[IRQNumber / 32U] = (1UL << IRQNumber % 32U);
    } 
    else 
    {
        NVIC->ICER[IRQNumber / 32U] = (1UL << IRQNumber % 32U);
    }
}

/*******************************************************************
 * @fn                  - NVIC_IRQPriorityConfig
 *
 * @brief               - Configures IRQ Priority
 *
 * @param[in]           - IRQNumber: Number choosen IRQ
 * @param[in]           - IRQPriority: choosen priority 0-15
 *
 * @return              - none
 *
 * @note                - none
 *
 */
void NVIC_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority)
{
    if (IRQNumber >= 240) return;

    if (IRQPriority >= (1U << NO_PR_BITS_IMPLEMENTED)) return;

    uint8_t byte_shift = ((IRQNumber % 4) * 8);

    /* Different MCU got different number of PR bits, more in docs */
    uint8_t shift_amount = (byte_shift + (8 - NO_PR_BITS_IMPLEMENTED));

    /* Clearing register bits */
    NVIC->IPR[IRQNumber / 4U] &= ~(0xFFUL << byte_shift);

    NVIC->IPR[IRQNumber / 4U] |= ((uint32_t)IRQPriority << shift_amount);
}