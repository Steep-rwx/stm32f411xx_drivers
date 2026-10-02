

#ifndef INC_STM32F411XX_GPIO_DRIVER_H_
#define INC_STM32F411XX_GPIO_DRIVER_H_

#include "stm32f411xx.h"
#include <stdint.h>


typedef struct
{
    uint8_t GPIO_PinNumber;                         /*!< possibly values from @GPIO_PIN_NUMBERS */
    uint8_t GPIO_PinMode;                           /*!< possibly values from @GPIO_PIN_MODES */
    uint8_t GPIO_PinSpeed;                          /*!< possibly values from @GPIO_SPEED_MODES */
    uint8_t GPIO_PinPuPdControl;                    /*!< possibly values from @GPIO_PUPD_MODES */
    uint8_t GPIO_PinOPType;                         /*!< pissibly values from @GPIO_PIN_OP_MODES */
    uint8_t GPIO_PinAltFunMode;
} GPIO_PinConfig_TypeDef;


typedef struct
{
    GPIO_Reg_TypeDef *pGPIOx;                       /*!< Base address of the GPIO */
    GPIO_PinConfig_TypeDef GPIO_PinConfig;          /*!< GPIO configuration of pin */
} GPIO_Handle_TypeDef;


/*
 * @GPIO_PIN_NUMBERS
 * GPIO pin numbers
 */

#define GPIO_PIN_NO_0           0
#define GPIO_PIN_NO_1           1
#define GPIO_PIN_NO_2           2
#define GPIO_PIN_NO_3           3
#define GPIO_PIN_NO_4           4
#define GPIO_PIN_NO_5           5
#define GPIO_PIN_NO_6           6
#define GPIO_PIN_NO_7           7
#define GPIO_PIN_NO_8           8
#define GPIO_PIN_NO_9           9
#define GPIO_PIN_NO_10          10
#define GPIO_PIN_NO_11          11
#define GPIO_PIN_NO_12          12
#define GPIO_PIN_NO_13          13
#define GPIO_PIN_NO_14          14
#define GPIO_PIN_NO_15          15

/*
 * @GPIO_PIN_MODES
 * GPIO pin modes
 */
#define GPIO_MODE_IN                0
#define GPIO_MODE_OUT               1
#define GPIO_MODE_AF                2
#define GPIO_MODE_AN                3
#define GPIO_MODE_FT                4
#define GPIO_MODE_RT                5
#define GPIO_MODE_RFT               6


/*
 * @GPIO_PIN_OP_MODES
 * GPIO port output configuration modes
 */
#define GPIO_OUT_TYPER_PP               0
#define GPIO_OUT_TYPER_OD               1

/*
 * @GPIO_SPEED_MODES
 * GPIO output speed configuration modes
 */
#define GPIO_SPEED_LOW                  0
#define GPIO_SPEED_MEDIUM               1
#define GPIO_SPEED_FAST                 2
#define GPIO_SPEED_HIGH                 3

/*
 * @GPIO_PUPD_MODES
 * GPIO port pull-up/pull-down modes
 */
#define GPIO_NO_PUPD                    0
#define GPIO_PIN_PU                     1
#define GPIO_PIN_PD                     2

/************************APIs supported by this driver**********************************/

/*
 * Peripheral Clock setup
 */
void GPIO_PeriClockControl(GPIO_Reg_TypeDef *pGPIOx, uint8_t enOrDi);       /* enOrDi - enable or disable value */

/*
 * Init and De-init
 */
void GPIO_Init(GPIO_Handle_TypeDef *pGPIOHandle);          /* Initialise GPIO through GPIO reg + GPIO settings struct */
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

void GPIO_IRQConfig(uint8_t IRQNumber, uint8_t enOrDi);
void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority);
void GPIO_IRQHandling(uint8_t pinNumber);





#endif /* INC_STM32F411XX_GPIO_DRIVER_H_ */