#ifndef INC_STM32F411XX_USART_DRIVER_H_
#define INC_STM32F411XX_USART_DRIVER_H_

#include "stm32f411xx.h"

#include <stdint.h>

/*
 * Configuration structure for USARTx
 */
typedef struct
{
    uint8_t     USART_Mode;                         
    uint32_t    USART_Baudrate;                 
    uint8_t     USART_NumberOfStopBits;         
    uint8_t     USART_WordLength;               
    uint8_t     USART_ParityControl;
    uint8_t     USART_HardwareFlowControl;
} USART_Config_TypeDef;

/*
 * @USART_Mode
 */
#define USART_MODE_DUPLEX       0
#define USART_MODE_TX_ONLY      1
#define USART_MODE_RX_ONLY      2



/*
 * @USART_Baudrate
 */
#define USART_BAUDRATE_1200         0
#define USART_BAUDRATE_2400         1
#define USART_BAUDRATE_9600         2
#define USART_BAUDRATE_19200        3
#define USART_BAUDRATE_38400        4
#define USART_BAUDRATE_57600        5
#define USART_BAUDRATE_115200       6

/*
 * @USART_NumberOfStopBits
 */
#define USART_NUMBER_OF_STOP_BITS_1_0         0
#define USART_NUMBER_OF_STOP_BITS_0_5         1
#define USART_NUMBER_OF_STOP_BITS_2_0         2
#define USART_NUMBER_OF_STOP_BITS_1_5         3

/*
 * @USART_WordLength
 */
#define USART_WORD_LENGTH_8_BITS                0
#define USART_WORD_LENGTH_9_BITS                1

/*
 * @USART_ParityControl
 */
#define USART_PARITY_CONTROL_DISABLED           0
#define USART_PARITY_CONTROL_ENABLED            1

/*
 * @USART_HardwareFlowControl
 */
#define USART_HARDWARE_FLOW_CONTROL_DISABLED    0
#define USART_HARDWARE_FLOW_CONTROL_ENABLED     1

/*
 * Handle structure for USARTx
 */
typedef struct
{
    USART_Reg_TypeDef       *pUSARTx;
    USART_Config_TypeDef    USART_Config;
} USART_Handle_TypeDef;

/*************************utility functions*******************************/

static inline uint8_t USART_GetFlagStatus(USART_Reg_TypeDef *pUSARTx, uint32_t FlagName)
{
    return (pUSARTx->SR & FlagName) ? FLAG_SET : FLAG_RESET;
}

static inline void USART_ClearFLag(USART_Reg_TypeDef *pUSARTx, uint32_t FlagName)
{
    pUSARTx->SR &= ~(FlagName);
}

/******************APIs supported by this driver**********************/

/*
 * Peripheral Clock setup
 */
void USART_PeriClockControl(USART_Reg_TypeDef *pUSARTx, uint8_t EnOrDi);

/*
 * Init and De-init
 */
void USART_Init(USART_Handle_TypeDef *pUSARTHandle);
void USART_DeInit(USART_Reg_TypeDef *pUSARTx);

/*
 * Data send and receive
 */
void USART_SendData(USART_Handle_TypeDef *pUSARTHandle, uint8_t *pTxBuffer, uint32_t Length);
void USART_ReceiveData(USART_Handle_TypeDef *pUSARTHandle, uint8_t *pRxBuffer, uint32_t Length);

/*
 * IRQ Configuration and ISR handling
 */
void USART_IRQConfig(uint8_t IRQNumber, uint8_t EnOrDi);
void USART_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority);
void USART_IRQHandling(USART_Handle_TypeDef *pUSARTHandle);

/*
 * Other Peripheral Control
 */
void USART_PeripheralControl(USART_Reg_TypeDef *pUSARTx, uint8_t EnOrDi);

/*
 * Application callback
 */
void USART_ApplicationEventCallback(USART_Handle_TypeDef *pUSARTHandle, uint8_t ApplicationEvent);

#endif /* INC_STM32F411XX_I2C_DRIVER_H_ */