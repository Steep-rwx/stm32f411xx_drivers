/**
 * @file    stm32f411xx_rcc_driver.h
 * @brief   RCC function signatures
 *
 */

#ifndef INC_STM32F411XX_RCC_DRIVER_H_
#define INC_STM32F411XX_RCC_DRIVER_H_

#include <stdint.h>
#include <stm32f411xx.h>

/* AHB1 */
uint32_t RCC_GetPCLK1Value(void);

/* AHB2 */
uint32_t RCC_GetPCLK2Value(void);

/* PLL */
uint32_t RCC_GetPLLOutputClock(void);

#endif /* INC_STM32F411XX_I2C_DRIVER_H_ */