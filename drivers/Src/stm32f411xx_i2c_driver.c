#include "stm32f411xx_i2c_driver.h"
#include "stm32f411xx.h"

#include <stdint.h>
#include <sys/types.h>


/************************Private functions prototypes*********************************/
static uint32_t RCC_GetPLLOutputClock(void);
static uint32_t RCC_GetPCLK1Value(void);
static void I2C_GenerateStartCondition(I2C_Reg_TypeDef *pI2Cx);
static void I2C_ExecuteAddressPhase(I2C_Reg_TypeDef *pI2Cx, uint8_t slaveAddr, uint8_t rw_condition);
static void I2C_ClearADDRFlag(I2C_Handle_TypeDef *pI2CHandle);
static void I2C_GenerateStopCondition(I2C_Reg_TypeDef *pI2Cx);
static void I2C_MasterHandleRXInterrupt(I2C_Handle_TypeDef *pI2CHandle);
static void I2C_MasterHandleTXInterrupt(I2C_Handle_TypeDef *pI2CHandle);
static void I2C_CloseSendData(I2C_Handle_TypeDef *pI2CHandle);
static void I2C_CloseReceiveData(I2C_Handle_TypeDef *pI2CHandle);

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

    I2C_PeriClockControl(pI2CHandle->pI2Cx, ENABLE);

    uint32_t tempreg = 0;

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

    I2C_PeripheralControl(pI2CHandle->pI2Cx, ENABLE);

    // ack control bit
    tempreg |= (pI2CHandle->I2C_Config.I2C_ACKControl << I2C_CR1_ACK);
    pI2CHandle->pI2Cx->CR1 = tempreg;
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
 * @fn                  - I2C_MasterSendData
 *
 * @brief               - Send data through I2C
 *
 * @param[in]           - pSPIx: base address
 * @param[in]           - pTxBuffer: Tx buffer
 * @param[in]           - length: length of info
 * @param[in]           - slaveAddr: slave addres in 7-bit format
 * @param[in]           - repeatedStart: enable or disable repeated start
 *
 * @return              - none
 *
 * @Note                - This is blocking call
 *
 */
void I2C_MasterSendData(I2C_Handle_TypeDef *pI2CHandle, 
                        uint8_t *pTxBuffer, 
                        uint32_t length, 
                        uint8_t slaveAddr, 
                        uint8_t repeatedStart)
{
    I2C_GenerateStartCondition(pI2CHandle->pI2Cx);

    while(!(I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_SB)));

    I2C_ExecuteAddressPhase(pI2CHandle->pI2Cx, slaveAddr, I2C_WRITE);

    while(!(I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_ADDR)));

    I2C_ClearADDRFlag(pI2CHandle);

    while(length > 0)
    {
        while(!(I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_TXE)));
        pI2CHandle->pI2Cx->DR = *pTxBuffer;
        pTxBuffer++;
        length--;
    }

    while(!(I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_TXE)));
    while(!(I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_BTF)));
    if(repeatedStart == I2C_REPEATED_START_DISABLE)
    {
        I2C_GenerateStopCondition(pI2CHandle->pI2Cx);
    }
}

/********************************************************************
 * @fn                  - I2C_MasterReceiveData
 *
 * @brief               - Receive data through I2C
 *
 * @param[in]           - pSPIx: base address
 * @param[in]           - pRxBuffer: Rx buffer
 * @param[in]           - length: length of info
 * @param[in]           - slaveAddr: slave addres in 7 bit format
 * @param[in]           - repeatedStart: enable or disable repeated start
 *
 * @return              - none
 *
 * @Note                - This is blocking call
 *
 */
void I2C_MasterReceiveData(I2C_Handle_TypeDef *pI2CHandle, 
                           uint8_t *pRxBuffer, 
                           uint32_t length, 
                           uint8_t slaveAddr,
                           uint8_t repeatedStart)
{
    I2C_GenerateStartCondition(pI2CHandle->pI2Cx);

    while(!(I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_SB)));

    I2C_ExecuteAddressPhase(pI2CHandle->pI2Cx, slaveAddr, I2C_READ);

    while(!(I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_ADDR)));

    if (length == 1)
    {
        I2C_ACKToggle(pI2CHandle->pI2Cx, I2C_ACK_DISABLE);

        I2C_ClearADDRFlag(pI2CHandle);

        if(repeatedStart == I2C_REPEATED_START_DISABLE)
        {
            I2C_GenerateStopCondition(pI2CHandle->pI2Cx);
        }

        while(!(I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_RXNE)));
        *pRxBuffer = pI2CHandle->pI2Cx->DR;
    } else if (length == 2)
    {
        while(!(I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_ADDR)));
        
        I2C_ACKToggle(pI2CHandle->pI2Cx, DISABLE);

        pI2CHandle->pI2Cx->CR1 |= (1U << I2C_CR1_POS);

        I2C_ClearADDRFlag(pI2CHandle);

        while(!(I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_BTF)));

        if(repeatedStart == I2C_REPEATED_START_DISABLE)
        {
            I2C_GenerateStopCondition(pI2CHandle->pI2Cx);
        }

        while(!(I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_RXNE)));
        *pRxBuffer = pI2CHandle->pI2Cx->DR;
        pRxBuffer++;

        while(!(I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_RXNE)));
        *pRxBuffer = pI2CHandle->pI2Cx->DR;

        pI2CHandle->pI2Cx->CR1 &= ~(1U << I2C_CR1_POS);
    } else
    {
        I2C_ClearADDRFlag(pI2CHandle);
        for (uint32_t i = length; i > 3; i--)
        {
            while(!(I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_RXNE)));
            *pRxBuffer++ = pI2CHandle->pI2Cx->DR;
        }

        while(!(I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_BTF)));
        I2C_ACKToggle(pI2CHandle->pI2Cx, I2C_ACK_DISABLE);
        *pRxBuffer++ = pI2CHandle->pI2Cx->DR;

        while(!(I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_BTF)));
        if (repeatedStart == I2C_REPEATED_START_DISABLE)
            I2C_GenerateStopCondition(pI2CHandle->pI2Cx);
        *pRxBuffer++ = pI2CHandle->pI2Cx->DR;

        while(!(I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_RXNE)));
        *pRxBuffer = pI2CHandle->pI2Cx->DR;
    }

    if(pI2CHandle->I2C_Config.I2C_ACKControl == I2C_ACK_ENABLE)
    {
        I2C_ACKToggle(pI2CHandle->pI2Cx, I2C_ACK_ENABLE);
    }
}

/********************************************************************
 * @fn                  - I2C_MasterSendDataIT
 *
 * @brief               - Send data through I2C
 *
 * @param[in]           - pSPIx: base address
 * @param[in]           - pTxBuffer: Tx buffer
 * @param[in]           - length: length of info
 * @param[in]           - slaveAddr: slave addres in 7-bit format
 * @param[in]           - repeatedStart: enable or disable repeated start
 *
 * @return              - none
 *
 * @Note                - This is blocking call
 *
 */
uint8_t I2C_MasterSendDataIT(I2C_Handle_TypeDef *pI2CHandle, 
                     uint8_t *pTxBuffer, 
                     uint32_t length, 
                     uint8_t slaveAddr, 
                     uint8_t repeatedStart)
{
    /* Checking busy state, if line busy there nothing to do */
    uint8_t busy_state = pI2CHandle->TxRxState;

    if((busy_state != I2C_BUSY_TX) && (busy_state != I2C_BUSY_RX))
    {
        pI2CHandle->pTxBuffer = pTxBuffer;          /* saving Tx buffer addr */
        pI2CHandle->TxLen = length;                 /* saving length of buffer */
        pI2CHandle->TxRxState = I2C_BUSY_TX;        /* saving state */
        pI2CHandle->DevAddr = slaveAddr;            /* saving slave addr */
        pI2CHandle->RepeatedStart = repeatedStart;  /* saving repeated start condition */

        /* Generating start condition */
        I2C_GenerateStartCondition(pI2CHandle->pI2Cx);

        /* Enabling buffer interrupts */
        pI2CHandle->pI2Cx->CR2 |= (1U << I2C_CR2_ITBUFEN);

        /* Enabling event interrupts */
        pI2CHandle->pI2Cx->CR2 |= (1U << I2C_CR2_ITEVTEN);

        /* Enabling error interrupts */
        pI2CHandle->pI2Cx->CR2 |= (1U << I2C_CR2_ITERREN);
    }
    return busy_state;
}

/********************************************************************
 * @fn                  - I2C_MasterReceiveDataIT
 *
 * @brief               - Receive data through I2C
 *
 * @param[in]           - pSPIx: base address
 * @param[in]           - pRxBuffer: Rx buffer
 * @param[in]           - length: length of info
 * @param[in]           - slaveAddr: slave addres in 7 bit format
 * @param[in]           - repeatedStart: enable or disable repeated start
 *
 * @return              - none
 *
 * @Note                - This is blocking call
 *
 */
uint8_t I2C_MasterReceiveDataIT(I2C_Handle_TypeDef *pI2CHandle, 
                        uint8_t *pRxBuffer, 
                        uint32_t length, 
                        uint8_t slaveAddr, 
                        uint8_t repeatedStart)
{
    /* Checking busy state, if busy there nothing to do */
    uint8_t busy_state = pI2CHandle->TxRxState;

    if ((busy_state != I2C_BUSY_TX) && (busy_state != I2C_BUSY_RX))
    {
        pI2CHandle->pRxBuffer = pRxBuffer;
        pI2CHandle->RxLen = length;
        pI2CHandle->DevAddr = slaveAddr;
        pI2CHandle->RxSize = length;
        pI2CHandle->DevAddr = slaveAddr;
        pI2CHandle->RepeatedStart = repeatedStart;

        /* Generating start condition */
        I2C_GenerateStartCondition(pI2CHandle->pI2Cx);

        /* Enabling buffer interrupts */
        pI2CHandle->pI2Cx->CR2 |= (1U << I2C_CR2_ITBUFEN);

        /* Enabling event interrupts */
        pI2CHandle->pI2Cx->CR2 |= (1U << I2C_CR2_ITEVTEN);

        /* Enabling error interrupts */
        pI2CHandle->pI2Cx->CR2 |= (1U << I2C_CR2_ITERREN);
    }

    return busy_state;
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

/*******************************************************************
 * @fn                  - I2C_EV_IRQHandling
 *
 * @brief               - Handles the event IRQ's
 *
 * @param[in]           - pI2CHandle: address of I2C structure
 *
 * @return              - none
 *
 * @Note                - none
 *
 */
void I2C_EV_IRQHandling(I2C_Handle_TypeDef *pI2CHandle)
{
    uint32_t itevten_state, itbufen_state, sb_state;

    itevten_state = pI2CHandle->pI2Cx->CR2 & (1U << I2C_CR2_ITEVTEN);
    itbufen_state = pI2CHandle->pI2Cx->CR2 & (1U << I2C_CR2_ITBUFEN);

    sb_state      = pI2CHandle->pI2Cx->SR1 & (1U << I2C_SR1_SB);

    if(itevten_state && sb_state)
    {
        if(pI2CHandle->TxRxState == I2C_BUSY_TX)
        {
            I2C_ExecuteAddressPhase(pI2CHandle->pI2Cx, pI2CHandle->DevAddr, I2C_WRITE);
        } else if (pI2CHandle->TxRxState == I2C_BUSY_RX)
        {
            I2C_ExecuteAddressPhase(pI2CHandle->pI2Cx, pI2CHandle->DevAddr, I2C_READ);
        }
    }

    uint32_t addr_state;
    addr_state = pI2CHandle->pI2Cx->SR1 & (1U << I2C_SR1_ADDR);

    if(itevten_state && addr_state)
    {
        I2C_ClearADDRFlag(pI2CHandle);

    } 

    uint32_t btf_state;
    btf_state = pI2CHandle->pI2Cx->SR1 & (1U << I2C_SR1_BTF);
    
    if (itevten_state && btf_state)
    {
        if (pI2CHandle->TxRxState == I2C_BUSY_TX)
        {
            if (pI2CHandle->pI2Cx->SR1 & (1U << I2C_SR1_TXE))
            {
                if (pI2CHandle->TxLen == 0)
                {
                    if (pI2CHandle->RepeatedStart == I2C_REPEATED_START_DISABLE)
                        I2C_GenerateStopCondition(pI2CHandle->pI2Cx);

                    I2C_CloseSendData(pI2CHandle);

                    I2C_ApplicationEventCallback(pI2CHandle, I2C_EVENT_TX_CMPLT);
                }
            }
        } else if (pI2CHandle->TxRxState == I2C_BUSY_RX)
        {
            if (pI2CHandle->pI2Cx->SR1 & (1U << I2C_SR1_RXNE))
            {
                ;
            }
        }
    }

    uint32_t stop_state;
    stop_state = pI2CHandle->pI2Cx->SR1 & (1U << I2C_SR1_STOPF);

    if(itevten_state && stop_state)
    {
        /* Clearing the STOPF */
        pI2CHandle->pI2Cx->CR1 |= 0x0000;

        /* notify */
        I2C_ApplicationEventCallback(pI2CHandle, I2C_EVENT_STOP);
    }

    uint32_t txe_state;
    txe_state = pI2CHandle->pI2Cx->SR1 & (1U << I2C_SR1_TXE);
    
    if (itevten_state && itbufen_state && txe_state)
    {
        if (pI2CHandle->pI2Cx->SR2 & (1U << I2C_SR2_MSL))
        {
            if (pI2CHandle->TxRxState == I2C_BUSY_TX)
            {
                I2C_MasterHandleTXInterrupt(pI2CHandle);
            }
        }
    }

    uint32_t rxne_state;
    rxne_state = pI2CHandle->pI2Cx->SR1 & (1U << I2C_SR1_RXNE);

    if (itevten_state && itbufen_state && rxne_state)
    {
        if (pI2CHandle->pI2Cx->SR2 & (1U << I2C_SR2_MSL))
        {
            if (pI2CHandle->TxRxState == I2C_BUSY_RX)
            {
                I2C_MasterHandleRXInterrupt(pI2CHandle);
            }
        }
    }
}

/*******************************************************************
 * @fn                  - I2C_ER_IRQHandling
 *
 * @brief               - Handles the erorr IRQ's
 *
 * @param[in]           - pI2CHandle: address of I2C structure
 *
 * @return              - none
 *
 * @Note                - none
 *
 */
void I2C_ER_IRQHandling(I2C_Handle_TypeDef *pI2CHandle)
{
    uint32_t iterren_status = pI2CHandle->pI2Cx->CR2 & (1U << I2C_CR2_ITERREN);

    uint32_t berr_status = pI2CHandle->pI2Cx->SR1 & (1U << I2C_SR1_BERR);

    if (iterren_status && berr_status)
    {
        pI2CHandle->pI2Cx->SR1 &= ~(1U << I2C_SR1_BERR);

        I2C_ApplicationEventCallback(pI2CHandle, I2C_ERROR_BERR);
    }

    uint32_t arlo_status = pI2CHandle->pI2Cx->SR1 & (1U << I2C_SR1_ARLO);

    if (iterren_status && arlo_status)
    {
        pI2CHandle->pI2Cx->SR1 &= ~(1U << I2C_SR1_ARLO);

        I2C_ApplicationEventCallback(pI2CHandle, I2C_ERROR_ARLO);
    }

    uint32_t af_status = pI2CHandle->pI2Cx->SR1 & (1U << I2C_SR1_AF);

    if (iterren_status && af_status)
    {
        pI2CHandle->pI2Cx->SR1 &= ~(1U << I2C_SR1_AF);

        I2C_ApplicationEventCallback(pI2CHandle, I2C_ERROR_AF);
    }

    uint32_t ovr_status = pI2CHandle->pI2Cx->SR1 & (1U << I2C_SR1_OVR);

    if (iterren_status && ovr_status)
    {
        pI2CHandle->pI2Cx->SR1 &= ~(1U << I2C_SR1_OVR);

        I2C_ApplicationEventCallback(pI2CHandle, I2C_ERROR_OVR);
    }

    uint32_t timeout_status = pI2CHandle->pI2Cx->SR1 & (1U << I2C_SR1_TIMEOUT);

    if (iterren_status && timeout_status)
    {
        pI2CHandle->pI2Cx->SR1 &= ~(1U << I2C_SR1_TIMEOUT);

        I2C_ApplicationEventCallback(pI2CHandle, I2C_ERROR_TIMEOUT);
    }
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

 void I2C_ACKToggle(I2C_Reg_TypeDef *pI2Cx, uint8_t enOrDi)
 {
    if (enOrDi)
    {
        pI2Cx->CR1 |= (1U << I2C_CR1_ACK);
    } else
    {
        pI2Cx->CR1 &= ~(1U << I2C_CR1_ACK);
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
 __attribute__((weak)) void I2C_ApplicationEventCallback(I2C_Handle_TypeDef *pI2CHandle, uint8_t ApplicationEvent)
{

}




/********************Private functions implementations*****************************/


/*
 * For init function
 */
static uint32_t RCC_GetPLLOutputClock(void)
{
    return 0;
}

/*
 * For init function
 */
static uint32_t RCC_GetPCLK1Value(void)
{
    static const uint32_t AHB_Prescaler[8]  = {2, 4, 8, 16, 64, 128, 256, 512};
    static const uint32_t APB1_Prescaler[4] = {2, 4, 8, 16};

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

static void I2C_ExecuteAddressPhase(I2C_Reg_TypeDef *pI2Cx, uint8_t slaveAddr, uint8_t rw_condition)
{
    slaveAddr = slaveAddr << 1;
    if (rw_condition == I2C_WRITE)
    {
        slaveAddr &= ~(1);    
    }
    else
    {
        slaveAddr &= ~(1);
        slaveAddr |= 0x01;
    }
    pI2Cx->DR = slaveAddr;
}

static void I2C_ClearADDRFlag(I2C_Handle_TypeDef *pI2CHandle)
{
    uint32_t dummyRead; 

    if (pI2CHandle->pI2Cx->SR2 & (1U << I2C_SR2_MSL))
    {
        if (pI2CHandle->TxRxState == I2C_BUSY_RX)
        {
            if (pI2CHandle->RxSize == 1)
            {
                I2C_ACKToggle(pI2CHandle->pI2Cx, DISABLE);

                dummyRead = pI2CHandle->pI2Cx->SR1;
                dummyRead = pI2CHandle->pI2Cx->SR2;
                (void) dummyRead;
            }
        }
        else
        {
            dummyRead = pI2CHandle->pI2Cx->SR1;
            dummyRead = pI2CHandle->pI2Cx->SR2;
            (void) dummyRead;
        }
    }
    else
    {
        dummyRead = pI2CHandle->pI2Cx->SR1;
        dummyRead = pI2CHandle->pI2Cx->SR2;
        (void) dummyRead;
    }
}

static void I2C_MasterHandleTXInterrupt(I2C_Handle_TypeDef *pI2CHandle)
{
    if (pI2CHandle->TxLen > 0)
    {
        pI2CHandle->pI2Cx->DR = *(pI2CHandle->pTxBuffer);
        pI2CHandle->TxLen--;
        pI2CHandle->pTxBuffer++;
    }
}


static void I2C_MasterHandleRXInterrupt(I2C_Handle_TypeDef *pI2CHandle)
{
    if (pI2CHandle->RxSize == 1)
    {
        *pI2CHandle->pRxBuffer = pI2CHandle->pI2Cx->DR;
        pI2CHandle->RxLen--;
    }

    if (pI2CHandle->RxSize > 1)
    {
        if (pI2CHandle->RxLen == 2)
        {
            I2C_ACKToggle(pI2CHandle->pI2Cx, DISABLE);
        }
    
        *pI2CHandle->pRxBuffer = pI2CHandle->pI2Cx->DR;
        pI2CHandle->pRxBuffer++;
        pI2CHandle->RxLen--;
    }

    if (pI2CHandle->RxLen == 0)
    {
        if (pI2CHandle->RepeatedStart == I2C_REPEATED_START_DISABLE)
        {
            I2C_GenerateStopCondition(pI2CHandle->pI2Cx);
        }
    
        I2C_CloseReceiveData(pI2CHandle);
    
        I2C_ApplicationEventCallback(pI2CHandle, I2C_EVENT_RX_CMPLT);
    }
}

static void I2C_CloseSendData(I2C_Handle_TypeDef *pI2CHandle)
{
    pI2CHandle->pI2Cx->CR2 &= ~(1U << I2C_CR2_ITBUFEN);

    pI2CHandle->pI2Cx->CR2 &= ~(1U << I2C_CR2_ITEVTEN);

    pI2CHandle->TxRxState = I2C_READY;
    pI2CHandle->pTxBuffer = NULL;
    pI2CHandle->TxLen = 0;
}

static void I2C_CloseReceiveData(I2C_Handle_TypeDef *pI2CHandle)
{
    pI2CHandle->pI2Cx->CR2 &= ~(1U << I2C_CR2_ITBUFEN);

    pI2CHandle->pI2Cx->CR2 &= ~(1U << I2C_CR2_ITEVTEN);

    pI2CHandle->TxRxState = I2C_READY;
    pI2CHandle->pRxBuffer = NULL;
    pI2CHandle->RxLen = 0;
    pI2CHandle->RxSize = 0;
    if (pI2CHandle->I2C_Config.I2C_ACKControl == I2C_ACK_ENABLE)
    {
        I2C_ACKToggle(pI2CHandle->pI2Cx, ENABLE);
    }
}