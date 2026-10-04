#ifndef INC_STM32F411XX_SPI_DRIVER_H_
#define INC_STM32F411XX_SPI_DRIVER_H_

#include "stm32f411xx.h"

#include <stdint.h>

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


typedef struct
{
    SPI_Reg_TypeDef *pSPIx;
    SPI_Config_TypeDef SPIConfig;
} SPI_Handle_TypeDef;

#endif /* INC_STM32F411XX_SPI_DRIVER_H_ */