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
#define USART_PARITY_CONTROL_DISABLED           1

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


#endif /* INC_STM32F411XX_I2C_DRIVER_H_ */