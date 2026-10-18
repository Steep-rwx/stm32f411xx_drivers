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
    uint16_t I2C_FMDutyCycle;
} I2C_Config_TypeDef;

/*
 * I2C handle structure
 */
typedef struct
{
    I2C_Reg_TypeDef     *pI2Cx;
    I2C_Config_TypeDef  I2C_Config;
} I2C_Handle_TypeDef;

#endif /* INC_STM32F411XX_I2C_DRIVER_H_ */