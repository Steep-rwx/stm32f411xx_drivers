#ifndef INC_STM32F411XX_SPI_DRIVER_H_
#define INC_STM32F411XX_SPI_DRIVER_H_

#include "stm32f411xx.h"

#include <stdint.h>


/*
 * SPIx config structure
 */
typedef struct 
{
    uint8_t SPI_DeviceMode;
    uint8_t SPI_BusConfig;
    uint8_t SPI_SclkSpeed;
    uint8_t SPI_DFF;
    uint8_t SPI_CPOL;
    uint8_t SPI_CPHA;
    uint8_t SPI_SSM;
} SPI_Config_TypeDef;

/*
 * SPIx handle structure
 */
typedef struct
{
    SPI_Reg_TypeDef *pSPIx;
    SPI_Config_TypeDef SPIConfig;
} SPI_Handle_TypeDef;


/******************APIs supported by this driver**********************/

/*
 * Peripheral Clock setup
 */
void SPI_PeriClockControl(SPI_Reg_TypeDef *pSPIx, uint8_t enOrDi);       /* enOrDi - enable or disable value */

/*
 * Init and De-init
 */
void SPI_Init(SPI_Handle_TypeDef *pSPIHandle);          /* Initialise SPI through SPI reg + SPI settings struct */
void SPI_DeInit(SPI_Reg_TypeDef *pSPIx);                /* Reset through RCC */

/*
 * Data send and receive
 */
void SPI_SendData(SPI_Reg_TypeDef *pSPIx, uint8_t *pTxBuffer, uint32_t length);
void SPI_ReceiveData(SPI_Reg_TypeDef *pSPIx, uint8_t *pRxBuffer, uint32_t length);

/*
 * IRQ Configuration and ISR handling
 */
void SPI_IRQConfig(uint8_t IRQNumber, uint8_t enOrDi);
void SPI_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority);
void SPI_IRQHandling(SPI_Handle_TypeDef *pSPIHandle);

#endif /* INC_STM32F411XX_SPI_DRIVER_H_ */