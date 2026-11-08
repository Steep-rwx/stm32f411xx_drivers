

#ifndef INC_STM32F411XX_NVIC_DRIVER_H_
#define INC_STM32F411XX_NVIC_DRIVER_H_

#include "stm32f411xx.h"
#include <stdint.h>

/**
  * @brief NVIC IRQ configuration
  */
void NVIC_IRQConfig(uint8_t IRQNumber, uint8_t enOrDi);

/**
  * @brief NVIC IRQ Priority configuration
  */
void NVIC_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority);


#endif /* INC_STM32F411XX_NVIC_DRIVER_H_ */