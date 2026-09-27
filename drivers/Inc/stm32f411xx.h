

#ifndef INC_STM32F411XX_H_
#define INC_STM32F411XX_H_


#include <stdint.h>



#define FLASH_BASEADDR                      0x08000000U                     /*!< Flash memory */
#define SRAM_BASEADDR                       0x20000000U                     /*!< SRAM memory */
#define ROM_BASEADDR                        0x1FFF0000U                     /*!< ROM memory */



#define PERIPH_BASEADDR                     0x40000000U                     /*!< Base address of peripheral */
#define APB1PERIPH_BASEADDR                 PERIPH_BASEADDR                 /*!< Base address of APB1 */
#define APB2PERIPH_BASEADDR                 0x40010000U                     /*!< Base address of APB2 */
#define AHB1PERIPH_BASEADDR                 0x40020000U                     /*!< Base address of AHB1 */
#define AHB2PERIPH_BASEADDR                 0x50000000U                     /*!< Base address of AHB2 */


/**
  * Base addresses of AHB1 bus
  */

#define GPIOA_BASEADDR                      (AHB1PERIPH_BASEADDR + 0x0000U)
#define GPIOB_BASEADDR                      (AHB1PERIPH_BASEADDR + 0x0400U)
#define GPIOC_BASEADDR                      (AHB1PERIPH_BASEADDR + 0x0800U)
#define GPIOD_BASEADDR                      (AHB1PERIPH_BASEADDR + 0x0C00U)
#define GPIOE_BASEADDR                      (AHB1PERIPH_BASEADDR + 0x1000U)
#define GPIOH_BASEADDR                      (AHB1PERIPH_BASEADDR + 0x1C00U)

#define RCC_BASEADDR                        (AHB1PERIPH_BASEADDR + 0x3800U)


/**
  * Base addresses of APB1 bus
  */

#define I2C1_BASEADDR                       (APB1PERIPH_BASEADDR + 0x5400U)
#define I2C2_BASEADDR                       (APB1PERIPH_BASEADDR + 0x5800U)
#define I2C3_BASEADDR                       (APB1PERIPH_BASEADDR + 0x5C00U)
#define SPI2_BASEADDR                       (APB1PERIPH_BASEADDR + 0x3800U)
#define SPI3_BASEADDR                       (APB1PERIPH_BASEADDR + 0x3C00U)
#define USART2_BASEADDR                     (APB1PERIPH_BASEADDR + 0x4400U)

/**
  * Base addresses of APB2 bus
  */

#define SPI1_BASEADDR                       (APB2PERIPH_BASEADDR + 0x3000U)
#define USART1_BASEADDR                     (APB2PERIPH_BASEADDR + 0x1000U)
#define USART6_BASEADDR                     (APB2PERIPH_BASEADDR + 0x1400U)
#define EXTI_BASEADDR                       (APB2PERIPH_BASEADDR + 0x3C00U)
#define SYSCFG_BASEADDR                     (APB2PERIPH_BASEADDR + 0x3800U)    



/******************peripheral register definition structures*********************/


/**
  * GPIO registers structure
  */
typedef struct
{
    volatile uint32_t MODER;         /*!< GPIO port mode,                    address offset: 0x00 */
    volatile uint32_t OTYPER;        /*!< GPIO port output type,             address offset: 0x04 */
    volatile uint32_t OSPEEDR;       /*!< GPIO port speed,                   address offset: 0x08 */
    volatile uint32_t PUPDR;         /*!< GPIO port pull-up/pull-down,       address offset: 0x0C */
    volatile uint32_t IDR;           /*!< GPIO port input data,              address offset: 0x10 */
    volatile uint32_t ODR;           /*!< GPIO port output data,             address offset: 0x14 */
    volatile uint32_t BSRR;          /*!< GPIO port bit set/reset,           address offset: 0x18 */
    volatile uint32_t LCKR;          /*!< GPIO port lock,                    address offset: 0x1C */
    volatile uint32_t AFR[2];        /*!< GPIO port alternative func,        address offset: 0x20 for AF low, 0x24 for AF high */
}GPIO_Reg_TypeDef;


/*!
 * RCC registers structure
 */
typedef struct
{
    volatile uint32_t CR;           /*!< RCC clock control register,                                    address offset: 0x00 */
    volatile uint32_t PLLCFGR;      /*!< RCC PLL configuration register,                                address offset: 0x04 */
    volatile uint32_t CFGR;         /*!< RCC clock configuration register,                              address offset: 0x08 */
    volatile uint32_t CIR;          /*!< RCC clock interrupt register,                                  address offset: 0x0C */
    volatile uint32_t AHB1RSTR;     /*!< RCC AHB1 peripheral reset register,                            address offset: 0x10 */
    volatile uint32_t AHB2RSTR;     /*!< RCC AHB2 peripheral reset register,                            address offset: 0x14 */
    uint32_t      RESERVED0[2];     /*!< Reserved,                                                      address offset: 0x18-0x1C */
    volatile uint32_t APB1RSTR;     /*!< RCC APB1 peripheral reset register,                            address offset: 0x20 */
    volatile uint32_t APB2RSTR;     /*!< RCC APB2 peripheral reset register,                            address offset: 0x24 */
    uint32_t      RESERVED1[2];     /*!< Reserved,                                                      address offset: 0x28-0x2C */
    volatile uint32_t AHB1ENR;      /*!< RCC AHB1 periph clock enable register,                         address offset: 0x30 */
    volatile uint32_t AHB2ENR;      /*!< RCC AHB2 periph clock enable register,                         address offset: 0x34 */
    uint32_t      RESERVED2[2];     /*!< Reserved,                                                      address offset: 0x38-0x3C */
    volatile uint32_t APB1ENR;      /*!< RCC APB1 periph clock enable register,                         address offset: 0x40 */
    volatile uint32_t APB2ENR;      /*!< RCC APB2 periph clock enable register,                         address offset: 0x44 */
    uint32_t      RESERVED3[2];     /*!< Reserved,                                                      address offset: 0x48-0x4C */
    volatile uint32_t AHB1LPENR;    /*!< RCC AHB1 peripheral clock enable in low power mode register,   address offset: 0x50 */
    volatile uint32_t AHB2LPENR;    /*!< RCC AHB2 peripheral clock enable in low power mode register,   address offset: 0x54 */
    uint32_t      RESERVED4[2];     /*!< Reserved,                                                      address offset: 0x58-0x5C */
    volatile uint32_t APB1LPENR;    /*!< RCC APB1 peripheral clock enable in low power mode register,   address offset: 0x60 */
    volatile uint32_t APB2LPENR;    /*!< RCC APB2 peripheral clock enable in low power mode register,   address offset: 0x64 */
    uint32_t      RESERVED5[2];     /*!< Reserved,                                                      address offset: 0x68-0x6C */
    volatile uint32_t BDCR;         /*!< RCC Backup domain control register,                            address offset: 0x70 */
    volatile uint32_t CSR;          /*!< RCC clock control & status register,                           address offset: 0x74 */
    uint32_t      RESERVED6[2];     /*!< Reserved,                                                      address offset: 0x78-0x7C */
    volatile uint32_t SSCGR;        /*!< RCC spread spectrum clock generation register,                 address offset: 0x80 */
    volatile uint32_t PLLI2SCFGR;   /*!< RCC PLLI2S configuration register,                             address offset: 0x84 */
    uint32_t      RESERVED7;        /*!< Reserved,                                                      address offset: 0x88 */
    volatile uint32_t DCKCFGR;      /*!< RCC Dedicated Clocks Configuration Register,                   address offset: 0x8C */
}RCC_Reg_TypeDef;



/**
  * peripheral definition
  */

#define GPIOA ((GPIO_Reg_TypeDef*) GPIOA_BASEADDR)
#define GPIOB ((GPIO_Reg_TypeDef*) GPIOB_BASEADDR)
#define GPIOC ((GPIO_Reg_TypeDef*) GPIOC_BASEADDR)
#define GPIOD ((GPIO_Reg_TypeDef*) GPIOD_BASEADDR)
#define GPIOE ((GPIO_Reg_TypeDef*) GPIOE_BASEADDR)
#define GPIOH ((GPIO_Reg_TypeDef*) GPIOH_BASEADDR)

#define RCC   ((RCC_Reg_TypeDef*) RCC_BASEADDR)


/**
  * Clock enable GPIO peripherals
  */

#define GPIOA_PCLK_EN()   (RCC->AHB1ENR |= (1 << 0))
#define GPIOB_PCLK_EN()   (RCC->AHB1ENR |= (1 << 1))
#define GPIOC_PCLK_EN()   (RCC->AHB1ENR |= (1 << 2))
#define GPIOD_PCLK_EN()   (RCC->AHB1ENR |= (1 << 3))
#define GPIOE_PCLK_EN()   (RCC->AHB1ENR |= (1 << 4))
#define GPIOH_PCLK_EN()   (RCC->AHB1ENR |= (1 << 7))


/**
  * Clock enable for I2Cx peripherals
  */

#define I2C1_PCLK_EN()      (RCC->APB1ENR |= (1 << 21))
#define I2C2_PCLK_EN()      (RCC->APB1ENR |= (1 << 22))
#define I2C3_PCLK_EN()      (RCC->APB1ENR |= (1 << 23))

/**
  * Clock enable for SPIx peripherals
  */
#define SPI1_PCLK_EN()      (RCC->APB2ENR |= (1 << 12))
#define SPI2_PCLK_EN()      (RCC->APB1ENR |= (1 << 14))
#define SPI3_PCLK_EN()      (RCC->APB1ENR |= (1 << 15))

/**
  * Clock enable for USARTx peripherals
  */
#define USART1_PCLK_EN()    (RCC->APB2ENR |= (1 << 4))
#define USART2_PCLK_EN()    (RCC->APB1ENR |= (1 << 17))
#define USART6_PCLK_EN()    (RCC->APB1ENR |= (1 << 5))

/**
  * Clock enable for SYSCFG peripheral
  */
#define SYSCFG_PCLK_EN()    (RCC->APB2ENR |= (1 << 14))

/**
  * Clock disable GPIO peripherals
  */

#define GPIOA_PCLK_DI()   (RCC->AHB1ENR &= ~(1 << 0))
#define GPIOB_PCLK_DI()   (RCC->AHB1ENR &= ~(1 << 1))
#define GPIOC_PCLK_DI()   (RCC->AHB1ENR &= ~(1 << 2))
#define GPIOD_PCLK_DI()   (RCC->AHB1ENR &= ~(1 << 3))
#define GPIOE_PCLK_DI()   (RCC->AHB1ENR &= ~(1 << 4))
#define GPIOH_PCLK_DI()   (RCC->AHB1ENR &= ~(1 << 7))


/**
  * Clock disable for I2Cx peripherals
  */

#define I2C1_PCLK_DI()      (RCC->APB1ENR &= ~(1 << 21))
#define I2C2_PCLK_DI()      (RCC->APB1ENR &= ~(1 << 22))
#define I2C3_PCLK_DI()      (RCC->APB1ENR &= ~(1 << 23))

/**
  * Clock disable for SPIx peripherals
  */
#define SPI1_PCLK_DI()      (RCC->APB2ENR &= ~(1 << 12))
#define SPI2_PCLK_DI()      (RCC->APB1ENR &= ~(1 << 14))
#define SPI3_PCLK_DI()      (RCC->APB1ENR &= ~(1 << 15))

/**
  * Clock disable for USARTx peripherals
  */
#define USART1_PCLK_DI()    (RCC->APB2ENR &= ~(1 << 4))
#define USART2_PCLK_DI()    (RCC->APB1ENR &= ~(1 << 17))
#define USART6_PCLK_DI()    (RCC->APB1ENR &= ~(1 << 5))

/**
  * Clock disable for SYSCFG peripheral
  */
#define SYSCFG_PCLK_DI()    (RCC->APB2ENR &= ~(1 << 14))


#endif /* INC_STM32F411XX_H_ */