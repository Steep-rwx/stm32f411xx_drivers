

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
void GPIO_PeriClockControl(GPIO_Reg_TypeDef *pGPIOx, uint8_t enOrDi);       /* enOrDi - enable or disable value */

/*
 * Init and De-init
 */
void GPIO_Init(GPIO_Handler_TypeDef *pGPIOHandle);          /* Initialise GPIO through GPIO reg + GPIO settings struct */
void GPIO_DeInit(GPIO_Reg_TypeDef *pGPIOx);                 /* Reset through RCC */

/*
 * Read and write
 */
uint8_t GPIO_ReadFromInputPin(GPIO_Reg_TypeDef *pGPIOx, uint8_t pinNumber);
uint16_t GPIO_ReadFromInputPort(GPIO_Reg_TypeDef *pGPIOx);
void GPIO_WriteToOutputPin(GPIO_Reg_TypeDef *pGPIOx, uint8_t pinNumber, uint8_t value);
void GPIO_WriteToOutputPort(GPIO_Reg_TypeDef *pGPIOx, uint16_t value);
void GPIO_ToggleOutputPin(GPIO_Reg_TypeDef *pGPIOx, uint8_t pinNumber);

/*
 * IRQ configuration and handling 
 */

void GPIO_IRQConfig(uint8_t IRQNumber, uint8_t IRQPriority, uint8_t enOrDi);        /* enOrDi - enable or disable value */
void GPIO_IRQHandling(uint8_t pinNumber);





#endif /* INC_STM32F411XX_GPIO_DRIVER_H_ */