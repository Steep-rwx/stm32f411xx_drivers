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

#endif /* INC_STM32F411XX_I2C_DRIVER_H_ */