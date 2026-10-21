#include "stm32f411xx_i2c_driver.h"
#include "stm32f411xx.h"

#include <stdint.h>
#include <sys/types.h>


/************************Private functions prototypes*********************************/
static uint32_t RCC_GetPLLOutputClock(void);
static uint32_t RCC_GetPCLK1Value(void);
static void I2C_GenerateStartCondition(I2C_Reg_TypeDef *pI2Cx);
static void I2C_ExecuteAddressPhase(I2C_Reg_TypeDef *pI2Cx, uint8_t slaveAddr);
static void I2C_ClearADDRFlag(I2C_Reg_TypeDef *pI2Cx);
static void I2C_GenerateStopCondition(I2C_Reg_TypeDef *pI2Cx);

/************************API's implementations****************************/


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
    uint32_t tempreg = 0;

    // ack control bit
    tempreg |= (pI2CHandle->I2C_Config.I2C_ACKControl << I2C_CR1_ACK);
    pI2CHandle->pI2Cx->CR1 = tempreg;

    // freq control bits
    tempreg = 0;
    tempreg |= RCC_GetPCLK1Value() / 1000000U;
    pI2CHandle->pI2Cx->CR2 = (tempreg & 0x3F);

    // address config
    tempreg = 0;
    tempreg |= pI2CHandle->I2C_Config.I2C_DeviceAddress << I2C_OAR1_ADD71;
    tempreg |= (1U << 14U); //Always high bit, more info in docs
    pI2CHandle->pI2Cx->OAR1 = tempreg;

    // CCR config & calculations
    uint16_t ccr_value = 0;
    tempreg = 0;
    if (pI2CHandle->I2C_Config.I2C_SCLSpeed <= I2C_SCL_SPEED_SM)
    {
        ccr_value = (RCC_GetPCLK1Value() / (2 * pI2CHandle->I2C_Config.I2C_SCLSpeed));
        tempreg |= (ccr_value & 0xFFF);
    }
    else
    {
        tempreg |= (1U << I2C_CCR_FS);
        tempreg |= (pI2CHandle->I2C_Config.I2C_FMDutyCycle << I2C_CCR_DUTY);
        if (pI2CHandle->I2C_Config.I2C_FMDutyCycle == I2C_FM_DUTY_2)
        {
            ccr_value = (RCC_GetPCLK1Value() / (3 * pI2CHandle->I2C_Config.I2C_SCLSpeed));
        } else
        {
            ccr_value = (RCC_GetPCLK1Value() / (25 * pI2CHandle->I2C_Config.I2C_SCLSpeed));
        }
        tempreg |= (ccr_value & 0xFFF);
    }
    pI2CHandle->pI2Cx->CCR = tempreg;

    tempreg = 0;
    //TRISE config
    if (pI2CHandle->I2C_Config.I2C_SCLSpeed == I2C_SCL_SPEED_SM)
    {
        tempreg = (RCC_GetPCLK1Value() / 1000000U) + 1;
    } else
    {
        tempreg = ((RCC_GetPCLK1Value() * 300) / 1000000000U) + 1;
    }

    pI2CHandle->pI2Cx->TRISE = (tempreg & 0x3F);
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

/********************************************************************
 * @fn                  - I2C_SendData
 *
 * @brief               - Send data through I2C
 *
 * @param[in]           - pSPIx: base address
 * @param[in]           - pTxBuffer: Tx buffer
 * @param[in]           - length: length of info
 * @param[in]           - slaveAddr: slave addres in //TODO format
 *
 * @return              - none
 *
 * @Note                - This is blocking call
 *
 */
void I2C_MasterSendData(I2C_Handle_TypeDef *pI2CHandle, uint8_t *pTxBuffer, uint32_t length, uint8_t slaveAddr)
{
    I2C_GenerateStartCondition(pI2CHandle->pI2Cx);

    while(!(I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_SB)));

    I2C_ExecuteAddressPhase(pI2CHandle->pI2Cx, uint8_t slaveAddr);

    while(!(I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_ADDR)));

    I2C_ClearADDRFlag(pI2CHandle->pI2Cx);

    while(length > 0)
    {
        while(!(I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_TXE)));
        pI2CHandle->pI2Cx->DR = *pTxBuffer;
        pTxBuffer++;
        length--;
    }

    while(!(I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_TXE)));
    while(!(I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_BTF)));

    I2C_GenerateStopCondition(pI2CHandle->pI2Cx);
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
    if (enOrDi)
    {
        pI2Cx->CR1 |= (1U << I2C_CR1_PE);
    } else
    {
        pI2Cx->CR1 &= ~(1U << I2C_CR1_PE);
    }
 }


/********************************************************************
 * @fn                  - I2C_ApplicationEventCallback
 *
 * @brief               - Processes event 
 *
 * @param[in]           - pI2CHandle: base address of I2C struct
 * @param[in]           - ApplicationEvent: Event that you need to check
 *
 * @return              - none
 *
 * @Note                - You can rewrite this function in your code
 *
 */
 __attribute__((weak)) void I2C_ApplicationEventCallback(SPI_Handle_TypeDef *pI2CHandle, uint8_t ApplicationEvent)
{

}


/********************Private functions implementations*****************************/


/*
 * For init function
 */
static uint32_t RCC_GetPLLOutputClock(void)
{

}

/*
 * For init function
 */
static uint32_t RCC_GetPCLK1Value(void)
{
    static const AHB_Prescaler[8]  = {2, 4, 8, 16, 64, 128, 256, 512};
    static const APB1_Prescaler[4] = {2, 4, 8, 16};

    uint32_t pclk1, system_clk;
    uint16_t ahbprescl_value, apb1prescl_value;
    uint8_t clksrc, prescl_val_binary;

    clksrc = ((RCC->CFGR >> 2U) & 0x3);
    if (clksrc == 0)
    {
        system_clk = 16000000;
    } else if (clksrc == 1)
    {
        system_clk = 25000000;
    } else if (clksrc == 2)
    {
        system_clk = RCC_GetPLLOutputClock();
    }

    //ahb
    prescl_val_binary = ((RCC->CFGR >> 4) & 0xF);
    if (prescl_val_binary < 8)
    {
        ahbprescl_value = 1;
    } else
    {
        ahbprescl_value = AHB_Prescaler[prescl_val_binary - 8];
    }
    
    //apb1
    prescl_val_binary = ((RCC->CFGR >> 10) & 0x7);
    if (prescl_val_binary < 4)
    {
        apb1prescl_value = 1;
    } else
    {
        apb1prescl_value = APB1_Prescaler[prescl_val_binary - 4];
    }

    pclk1 = (system_clk / ahbprescl_value / apb1prescl_value);

    return pclk1;
}

/*
 * For send function
 */
static void I2C_GenerateStartCondition(I2C_Reg_TypeDef *pI2Cx)
{
    pI2Cx->CR1 |= (1U << I2C_CR1_START);
}

static void I2C_GenerateStopCondition(I2C_Reg_TypeDef *pI2Cx)
{
    pI2Cx->CR1 |= (1U << I2C_CR1_STOP);
}

static void I2C_ExecuteAddressPhase(I2C_Reg_TypeDef *pI2Cx, uint8_t slaveAddr)
{
    slaveAddr = slaveAddr << 1;
    slaveAddr &= ~(1);
    pI2Cx->DR = slaveAddr;
}

static void I2C_ClearADDRFlag(I2C_Reg_TypeDef *pI2Cx)
{
    uint32_t dummyRead = pI2Cx->SR1;
    dummyRead = pI2Cx->SR1;
    (void) dummyRead;
}