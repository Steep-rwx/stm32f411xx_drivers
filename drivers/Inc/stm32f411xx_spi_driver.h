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

/*
 * @SPI_DeviceMode
 */
#define SPI_DEVICE_MODE_MASTER      1
#define SPI_DEVICE_MODE_SLAVE       0

/*
 * @SPI_BusConfig
 */
#define SPI_BUS_CONFIG_FULLDUPLEX       0
#define SPI_BUS_CONFIG_HALFDUPLEX       1
#define SPI_BUS_CONFIG_SIMPLEX_RXONLY   2

/*
 * @SPI_SclkSpeed
 */
#define SPI_SCLK_SPEED_DIV2                 0
#define SPI_SCLK_SPEED_DIV4                 1
#define SPI_SCLK_SPEED_DIV8                 2
#define SPI_SCLK_SPEED_DIV16                3
#define SPI_SCLK_SPEED_DIV32                4
#define SPI_SCLK_SPEED_DIV64                5
#define SPI_SCLK_SPEED_DIV128               6
#define SPI_SCLK_SPEED_DIV256               7

/*
 * @SPI_DFF
 */
#define SPI_DFF_8BIT            0
#define SPI_DFF_16BIT           1

/*
 * @SPI_CPOL
 */
#define SPI_CPOL_LOW            0
#define SPI_CPOL_HIGH           1

/*
 * @SPI_CPHA
 */
#define SPI_CPHA_FIRST_CAPTURE      0
#define SPI_CPHA_SECOND_CAPTURE     1

/*
 * @SPI_CPHA
 */
#define SPI_SSM_DISABLED            0
#define SPI_SSM_ENABLED             1

/*
 * SPI flag definitions
 */
#define SPI_TXE_FLAG            (1 << SPI_SR_TXE)
#define SPI_RXNE_FLAG           (1 << SPI_SR_RXNE)
#define SPI_BUSY_FLAG           (1 << SPI_SR_BSY)


/*************************utility functions*******************************/

static inline void SPI_WaitTxEmpty(SPI_Reg_TypeDef *pSPIx)
{
    while (!((pSPIx->SR >> SPI_SR_TXE) & 0x1));
}

static inline uint8_t SPI_GetFlagStatus(SPI_Reg_TypeDef *pSPIx, uint32_t FlagName)
{
    return (pSPIx->SR & FlagName) ? FLAG_SET : FLAG_RESET;
}

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