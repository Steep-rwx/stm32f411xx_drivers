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
 * Handle structure for USARTx
 */
typedef struct
{
    USART_Reg_TypeDef       *pUSARTx;
    USART_Config_TypeDef    USART_Config;
} USART_Handle_TypeDef;


#endif /* INC_STM32F411XX_I2C_DRIVER_H_ */