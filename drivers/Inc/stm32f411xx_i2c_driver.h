#ifndef INC_STM32F411XX_I2C_DRIVER_H_
#define INC_STM32F411XX_I2C_DRIVER_H_

#include "stm32f411xx.h"

#include <stdint.h>

/*
 * I2C config structure
 */
typedef struct
{
    uint32_t I2C_SCLSpeed;
    uint8_t  I2C_DeviceAddress;
    uint8_t  I2C_ACKControl;
    uint8_t  I2C_FMDutyCycle;
} I2C_Config_TypeDef;

/*
 * I2C handle structure
 */
typedef struct
{
    I2C_Reg_TypeDef     *pI2Cx;
    I2C_Config_TypeDef  I2C_Config;
    uint8_t             *pTxBuffer;
    uint8_t             *pRxBuffer;
    uint32_t            TxLen;
    uint32_t            RxLen;
    uint8_t             TxRxState;
    uint8_t             DevAddr;
    uint32_t            RxSize;
    uint8_t             RepeatedStart;
} I2C_Handle_TypeDef;

/*
 * @I2C_SCLSpeed
 */
#define I2C_SCL_SPEED_SM    100000
#define I2C_SCL_SPEED_FM    400000

/*
 * @I2C_ACKControl;
 */
#define I2C_ACK_ENABLE      1
#define I2C_ACK_DISABLE     0

/*
 * @I2C_FMDutyCycle;
 */
#define I2C_FM_DUTY_2       0
#define I2C_FM_DUTY_16_9    1

/*
 * I2C flag definitions
 */
#define I2C_FLAG_TXE            (1 << I2C_SR1_TXE)
#define I2C_FLAG_RXNE           (1 << I2C_SR1_RXNE)
#define I2C_FLAG_SB             (1 << I2C_SR1_SB)
#define I2C_FLAG_ADDR           (1 << I2C_SR1_ADDR)
#define I2C_FLAG_BTF            (1 << I2C_SR1_BTF)
#define I2C_FLAG_STOPF          (1 << I2C_SR1_STOPF)
#define I2C_FLAG_BERR           (1 << I2C_SR1_BERR)
#define I2C_FLAG_ARLO           (1 << I2C_SR1_ARLO)
#define I2C_FLAG_AF             (1 << I2C_SR1_AF)
#define I2C_FLAG_OVR            (1 << I2C_SR1_OVR)
#define I2C_FLAG_TIMEOUT        (1 << I2C_SR1_TIMEOUT)

/*
 * I2C Read or write definitions
 */
#define I2C_WRITE           0
#define I2C_READ            1

/*
 * Repeated start definitions
 */
#define I2C_REPEATED_START_ENABLE           1
#define I2C_REPEATED_START_DISABLE          0

/*
 * I2C states
 */
#define I2C_READY           0
#define I2C_BUSY_RX         1
#define I2C_BUSY_TX         2

/*
 * I2C Application events
 */
#define I2C_EVENT_TX_CMPLT  1
#define I2C_EVENT_RX_CMPLT  2
#define I2C_EVENT_STOP      3

/*
 * I2C Application events errors
 */
#define I2C_ERROR_BERR      4
#define I2C_ERROR_ARLO      5
#define I2C_ERROR_AF        6
#define I2C_ERROR_OVR       7
#define I2C_ERROR_TIMEOUT   8

/*************************utility functions*******************************/

static inline uint8_t I2C_GetFlagStatus(I2C_Reg_TypeDef *pI2Cx, uint32_t FlagName)
{
    return (pI2Cx->SR1 & FlagName) ? FLAG_SET : FLAG_RESET;
}

/******************APIs supported by this driver**********************/

/*
 * Peripheral Clock setup
 */
void I2C_PeriClockControl(I2C_Reg_TypeDef *pI2Cx, uint8_t enOrDi);       /* enOrDi - enable or disable value */

/*
 * Init and De-init
 */
void I2C_Init(I2C_Handle_TypeDef *pI2CHandle);          /* Initialise I2C through I2C reg + I2C settings struct */
void I2C_DeInit(I2C_Reg_TypeDef *pI2Cx);                /* Reset through RCC */

/*
 * Data send and receive
 */
void I2C_MasterSendData(I2C_Handle_TypeDef *pI2CHandle, 
                        uint8_t *pTxBuffer, 
                        uint32_t length, 
                        uint8_t slaveAddr, 
                        uint8_t repeatedStart);
void I2C_MasterReceiveData(I2C_Handle_TypeDef *pI2CHandle, 
                           uint8_t *pRxBuffer, 
                           uint32_t length, 
                           uint8_t slaveAddr, 
                           uint8_t repeatedStart);

/*
 * Data send and receive with interrupts 
 */
uint8_t I2C_MasterSendDataIT(I2C_Handle_TypeDef *pI2CHandle, 
                          uint8_t *pTxBuffer, 
                          uint32_t length, 
                          uint8_t slaveAddr, 
                          uint8_t repeatedStart);
uint8_t I2C_MasterReceiveDataIT(I2C_Handle_TypeDef *pI2CHandle, 
                             uint8_t *pRxBuffer, 
                             uint32_t length, 
                             uint8_t slaveAddr, 
                             uint8_t repeatedStart);

/*
 * Data send and receive slave versions
 */
void I2C_SlaveSendData(I2C_Reg_TypeDef *pI2Cx, uint8_t data);
uint8_t I2C_SlaveReceiveData(I2C_Reg_TypeDef *pI2Cx);

/*
 * IRQ Configuration and ISR handling
 */
void I2C_IRQConfig(uint8_t IRQNumber, uint8_t enOrDi);
void I2C_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority);
void I2C_EV_IRQHandling(I2C_Handle_TypeDef *pI2CHandle);
void I2C_ER_IRQHandling(I2C_Handle_TypeDef *pI2CHandle);

/*
 * Other Peripheral Control
 */
void I2C_PeripheralControl(I2C_Reg_TypeDef *pI2Cx, uint8_t enOrDi);
void I2C_ACKToggle(I2C_Reg_TypeDef *pI2Cx, uint8_t enOrDi);

void I2C_GenerateStopCondition(I2C_Reg_TypeDef *pI2Cx);

/*
 * Application callback
 */
void I2C_ApplicationEventCallback(I2C_Handle_TypeDef *pI2CHandle, uint8_t ApplicationEvent);

#endif /* INC_STM32F411XX_I2C_DRIVER_H_ */