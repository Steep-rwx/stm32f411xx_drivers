#include "stm32f411xx_i2c_driver.h"
#include "stm32f411xx.h"

#include <stdint.h>



/********************************************************************
 * @fn                  - I2C_PeriClockControl
 *
 * @brief               - Function which enables/disables clock for choosed I2C
 *
 * @param[in]           - pI2Cx: I2C base address
 * @param[in]           - enOrDi: ENABLE or DISABLE macro
 *
 * @return              - none
 *
 * @Note                - none
 *
 */
void I2C_PeriClockControl(I2C_Reg_TypeDef *pI2Cx, uint8_t enOrDi)
{

    if (enOrDi)
    {
        if (pI2Cx == I2C1) { I2C1_PCLK_EN(); }
        if (pI2Cx == I2C2) { I2C2_PCLK_EN(); }
        if (pI2Cx == I2C3) { I2C3_PCLK_EN(); }
    } else
    {
        if (pI2Cx == I2C1) { I2C1_PCLK_DI(); }
        if (pI2Cx == I2C2) { I2C2_PCLK_DI(); }
        if (pI2Cx == I2C3) { I2C3_PCLK_DI(); }
    }
}


/********************************************************************
 * @fn                  - I2C_Init
 *
 * @brief               - Initializes the specifies I2C
 *
 * @param[in]           - pI2CHandle: A structure that contains pin base address and pin config
 *
 * @return              - none
 *
 * @Note                - none
 *
 */
void I2C_Init(I2C_Handle_TypeDef *pI2CHandle)
{

}

/********************************************************************
 * @fn                  - I2C_DeInit
 *
 * @brief               - Deinitializes the specified pin
 *
 * @param[in]           - pI2Cx: A base address of I2Cx
 *
 * @return              - none
 *
 * @Note                - none
 *
 */
void I2C_DeInit(I2C_Reg_TypeDef *pI2Cx)
{
    if (pI2Cx == I2C1)
    {
        RCC->APB1RSTR |= (1U << 21U);
        RCC->APB1RSTR &= ~(1U << 21U);
    } else if (pI2Cx == I2C2)
    {
        RCC->APB1RSTR |= (1U << 22U);
        RCC->APB1RSTR &= ~(1U << 22U);
    } else if (pI2Cx == I2C3)
    {   
        RCC->APB1RSTR |= (1U << 23U);
        RCC->APB1RSTR &= ~(1U << 23U);
    }
}

/*******************************************************************
 * @fn                  - I2C_IRQConfig
 *
 * @brief               - Configures IRQ from number
 *
 * @param[in]           - IRQNumber: Number choosed IRQ
 * @param[in]           - enOrDi: ENABLE or DISABLE macro
 *
 * @return              - none
 *
 * @Note                - none
 *
 */
void I2C_IRQConfig(uint8_t IRQNumber, uint8_t enOrDi)
{
    if (IRQNumber >= 240) return;

    uint8_t ipr_idx = IRQNumber / 32;
    uint8_t bit_pos = IRQNumber % 32;
    if (enOrDi)
    {
        NVIC->ISER[ipr_idx] |= (1UL << bit_pos);
    } else 
    {
        NVIC->ICER[ipr_idx] |= (1UL << bit_pos);
    }
}

/*******************************************************************
 * @fn                  - I2C_IRQPriority
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
void I2C_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority)
{
    if (IRQNumber >= 240) return;

    uint8_t ipr_idx = IRQNumber / 4;
    uint8_t byte_shift = ((IRQNumber % 4) * 8);

    uint8_t shift_amount = (byte_shift + (8 - NO_PR_BITS_IMPLEMENTED));

    NVIC->IPR[ipr_idx] &= ~(0xFFUL << byte_shift);

    NVIC->IPR[ipr_idx] |= ((uint32_t)IRQPriority << shift_amount);
}

/********************************************************************
 * @fn                  - I2C_PeripheralControl
 *
 * @brief               - Enables I2C choosen peripheral
 *
 * @param[in]           - pI2Cx: base address
 * @param[in]           - enOrDi: ENABLE or DISABLE
 *
 * @return              - none
 *
 * @Note                - none
 *
 */
 void I2C_PeripheralControl(I2C_Reg_TypeDef *pI2Cx, uint8_t enOrDi)
 {

 }



 __attribute__((weak)) void I2C_ApplicationEventCallback(SPI_Handle_TypeDef *pI2CHandle, uint8_t ApplicationEvent)
{

}