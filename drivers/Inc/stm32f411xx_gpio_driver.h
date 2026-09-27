

#ifndef INC_STM32F411XX_GPIO_DRIVER_H_
#define INC_STM32F411XX_GPIO_DRIVER_H_

#include "stm32f411xx.h"
#include <stdint.h>


typedef struct
{
    uint8_t GPIO_PinNumber;
    uint8_t GPIO_PinMode;
    uint8_t GPIO_PinSpeed;
    uint8_t GPIO_PinPuPdControl;
    uint8_t GPIO_PinOPType;
    uint8_t GPIO_PinAltFunMode;
} GPIO_PinConfig_TypeDef;


typedef struct
{
    GPIO_Reg_TypeDef *pGPIOx;                       /*!< Base address of the GPIO */
    GPIO_PinConifg_TypeDef GPIO_PinConfig;          /*!< GPIO configuration of pin */
} GPIO_Handler_TypeDef;



/************************APIs supported by this driver**********************************/

/*
 * Peripheral Clock setup
 */
void GPIO_PeriClockControl(void);

/*
 * Init and De-init
 */
void GPIO_Init(void);
void GPIO_DeInit(void);

/*
 * Read and write
 */
void GPIO_ReadFromInputPin(void);
void GPIO_ReadFromInputPort(void);
void GPIO_WriteToOutputPin(void);
void GPIO_WriteToOutputPort(void);
void GPIO_ToggleOutputPin(void);

/*
 * IRQ configuration and handling 
 */

void GPIO_IRQConfig(void);
void GPIO_IRQHandling(void);





#endif /* INC_STM32F411XX_GPIO_DRIVER_H_ */