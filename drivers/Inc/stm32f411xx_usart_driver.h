/**
 * @file    stm32f411xx_usart_driver.h
 * @brief   USART structures and definitions
 *
 */

#ifndef INC_STM32F411XX_USART_DRIVER_H_
#define INC_STM32F411XX_USART_DRIVER_H_

#include "stm32f411xx.h"

#include <stdint.h>

/*
 * Configuration structure for USARTx
 */
typedef struct
{
    uint8_t     USART_Mode;                         /*!< possible values from @ref USART_MODE */
    uint32_t    USART_Baudrate;                     /*!< possible values from @ref USART_BAUDRATE */
    uint8_t     USART_NumberOfStopBits;             /*!< possible values from @ref USART_NUMBER_OF_STOP_BITS */
    uint8_t     USART_WordLength;                   /*!< possible values from @ref USART_WORD_LENGTH */
    uint8_t     USART_ParityControl;                /*!< possible values from @ref USART_PARITY_CONTROL */
    uint8_t     USART_HardwareFlowControl;          /*!< possible values from @ref USART_HARDWARE_FLOW_CONTROL */
} USART_Config_TypeDef;

/*
 * Handle structure for USARTx
 */
typedef struct
{
    USART_Reg_TypeDef                *pUSARTx;
    USART_Config_TypeDef             USART_Config;
    const uint8_t                    *pTxBuffer;
    uint8_t                          *pRxBuffer;
    volatile uint32_t                TxLength;
    volatile uint32_t                RxLength;
    volatile uint8_t                 TxState;
    volatile uint8_t                 RxState;
} USART_Handle_TypeDef;

/*
 * USART_MODE
 */
#define USART_MODE_TX_RX        0
#define USART_MODE_TX_ONLY      1
#define USART_MODE_RX_ONLY      2

/*
 * USART_BAUDRATE
 */
#define USART_BAUDRATE_1200         1200
#define USART_BAUDRATE_2400         2400
#define USART_BAUDRATE_9600         9600
#define USART_BAUDRATE_19200        19200
#define USART_BAUDRATE_38400        38400
#define USART_BAUDRATE_57600        57600
#define USART_BAUDRATE_115200       115200

/*
 * USART_NUMBER_OF_STOP_BITS
 */
#define USART_NUMBER_OF_STOP_BITS_1_0         0
#define USART_NUMBER_OF_STOP_BITS_0_5         1
#define USART_NUMBER_OF_STOP_BITS_2_0         2
#define USART_NUMBER_OF_STOP_BITS_1_5         3

/*
 * USART_WORD_LENGTH
 */
#define USART_WORD_LENGTH_8_BITS                0
#define USART_WORD_LENGTH_9_BITS                1

/*
 * USART_PARITY_CONTROL
 */
#define USART_PARITY_CONTROL_DISABLED           0
#define USART_PARITY_CONTROL_ENABLED_EVEN       1
#define USART_PARITY_CONTROL_ENABLED_ODD        2

/*
 * USART_HARDWARE_FLOW_CONTROL
 */
#define USART_HARDWARE_FLOW_CONTROL_DISABLED            0
#define USART_HARDWARE_FLOW_CONTROL_ENABLED_CTS         1
#define USART_HARDWARE_FLOW_CONTROL_ENABLED_RTS         2
#define USART_HARDWARE_FLOW_CONTROL_ENABLED_CTS_RTS     3

/*
 * USART flag definitions
 */
#define USART_FLAG_TXE              (1U << USART_SR_TXE)
#define USART_FLAG_TC               (1U << USART_SR_TC)
#define USART_FLAG_RXNE             (1U << USART_SR_RXNE)

/*
 * USART status definitions
 */
#define USART_READY             0
#define USART_BUSY_TX           1
#define USART_BUSY_RX           2

/*
 * USART Application Events
 */
#define USART_EVENT_TX_COMPLETE     1
#define USART_EVENT_RX_COMPLETE     2
#define USART_EVENT_CTS             3
#define USART_EVENT_IDLE            4
#define USART_EVENT_ORE             5
#define USART_EVENT_ERROR_FE        6
#define USART_EVENT_ERROR_NF        7



/*************************utility functions*******************************/

static inline uint8_t USART_GetFlagStatus(USART_Reg_TypeDef *pUSARTx, uint32_t FlagName)
{
    return (pUSARTx->SR & FlagName) ? FLAG_SET : FLAG_RESET;
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
void USART_SendData(USART_Handle_TypeDef *pUSARTHandle, const uint8_t *pTxBuffer, uint32_t Length);
void USART_ReceiveData(USART_Handle_TypeDef *pUSARTHandle, uint8_t *pRxBuffer, uint32_t Length);

void USART_SendDataIT(USART_Handle_TypeDef *pUSARTHandle, const uint8_t *pTxBuffer, uint32_t Length);
void USART_ReceiveDataIT(USART_Handle_TypeDef *pUSARTHandle, uint8_t *pRxBuffer, uint32_t Length);

/*
 * IRQ handling
 */
void USART_IRQHandling(USART_Handle_TypeDef *pUSARTHandle);

/*
 * Other Peripheral Control
 */
void USART_PeripheralControl(USART_Reg_TypeDef *pUSARTx, uint8_t EnOrDi);
void USART_SetBaudRate(USART_Reg_TypeDef *pUSARTx, uint32_t BaudRate);

/*
 * Application callback
 */
void USART_ApplicationEventCallback(USART_Handle_TypeDef *pUSARTHandle, uint8_t ApplicationEvent);

#endif /* INC_STM32F411XX_USART_DRIVER_H_ */