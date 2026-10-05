

#ifndef INC_STM32F411XX_H_
#define INC_STM32F411XX_H_


#include <stdint.h>


/***************** Processor Specific Details ****************/

/*
 * NVIC ISERx register adresses
 */
typedef struct
{
  volatile uint32_t ISER[8];              /*!< NVIC Interrupt Set-enable Registers,     address offset: TODO */
  uint32_t RESERVED0[24];                 /*!< Reserved,                                address offset: TODO */
  volatile uint32_t ICER[8];              /*!< NVIC Interrupt Clear-enable Registers,   address offset: TODO */
  uint32_t RESERVED1[24];                 /*!< Reserved,                                address offset: TODO */
  volatile uint32_t ISPR[8];              /*!< NVIC Interrupt Set-pending Registers,    address offset: TODO */
  uint32_t RESERVED2[24];                 /*!< Reserved,                                address offset: TODO */
  volatile uint32_t ICPR[8];              /*!< NVIC Interrupt Clear-pending Registers,  address offset: TODO */
  uint32_t RESERVED3[24];                 /*!< Reserved,                                address offset: TODO */
  volatile uint32_t IABR[8];              /*!< NVIC Interrupt Active Bit Registers,     address offset: TODO */
  uint32_t RESERVED4[56];                 /*!< Reserved,                                address offset: TODO */
  volatile uint32_t IPR[60];              /*!< NVIC Interrupt Priority Registers,       address offset: TODO */
} NVIC_Reg_TypeDef;


#define NO_PR_BITS_IMPLEMENTED              4


#define FLASH_BASEADDR                      0x08000000U                     /*!< Flash memory */
#define SRAM_BASEADDR                       0x20000000U                     /*!< SRAM memory */
#define ROM_BASEADDR                        0x1FFF0000U                     /*!< ROM memory */



#define PERIPH_BASEADDR                     0x40000000U                     /*!< Base address of peripheral */
#define APB1PERIPH_BASEADDR                 PERIPH_BASEADDR                 /*!< Base address of APB1 */
#define APB2PERIPH_BASEADDR                 0x40010000U                     /*!< Base address of APB2 */
#define AHB1PERIPH_BASEADDR                 0x40020000U                     /*!< Base address of AHB1 */
#define AHB2PERIPH_BASEADDR                 0x50000000U                     /*!< Base address of AHB2 */
#define NVIC_BASEADDR                       0xE000E100U                     /*!< Base address of NVIC */


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



/****************** peripheral register definition structures *********************/


/*
 *  @Brief GPIO registers structure
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
} GPIO_Reg_TypeDef;


/*
 * @Brief RCC registers structure
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
} RCC_Reg_TypeDef;

/*
 * @Brief EXTI registers structure
 */

typedef struct
{
  volatile uint32_t IMR;            /*!< EXTI Interrupt mask register,                  address offset: 0x00 */
  volatile uint32_t EMR;            /*!< EXTI Event mask register,                      address offset: 0x04 */
  volatile uint32_t RTSR;           /*!< EXTI Rising trigger selection register,        address offset: 0x08 */
  volatile uint32_t FTSR;           /*!< EXTI Falling trigger selection register,       address offset: 0x0C */
  volatile uint32_t SWIER;          /*!< EXTI Software interrupt event register,        address offset: 0x10 */
  volatile uint32_t PR;             /*!< EXTI Pending register,                         address offset: 0x14 */
} EXTI_Reg_TypeDef;

/*
 * @Brief SYSCFG registers structure
 */

 typedef struct
 {
  volatile uint32_t MEMRMP;         /*!< SYSCFG memory remap register,                            address offset: 0x00 */
  volatile uint32_t PMC;            /*!< SYSCFG peripheral mode configuration register,           address offset: 0x04 */
  volatile uint32_t EXTICR[4];      /*!< SYSCFG external interrupt configuration registers 1-4,   address offset: 0x08-0x14 */
  uint32_t RESERVED[2];    /*!< Reserved,                                                address offset: 0x18-0x1C */
  volatile uint32_t CMPCR;          /*!< SYSCFG Compensation cell control register,               address offset: 0x20 */
 } SYSCFG_Reg_TypeDef;


/*******************************peripheral interfaces structures***********************************************/

typedef struct 
{
  volatile uint32_t CR1;          /*!< SPI control register 1,                address offset: 0x00 */
  volatile uint32_t CR2;          /*!< SPI control register 2,                address offset: 0x04 */
  volatile uint32_t SR;           /*!< SPI status register,                   address offset: 0x08 */
  volatile uint32_t DR;           /*!< SPI data register,                     address offset: 0x0C */
  volatile uint32_t CRCPR;        /*!< SPI CRC polynomial register,           address offset: 0x10 */
  volatile uint32_t RXCRCR;       /*!< SPI RX CRC register,                   address offset: 0x14 */
  volatile uint32_t TXCRCR;       /*!< SPI TX CRC register,                   address offset: 0x18 */
  volatile uint32_t I2SCFGR;      /*!< SPI_I2S configuration register,        address offset: 0x1C */
  volatile uint32_t I2SPR;        /*!< SPI_I2S prescaler register,            address offset: 0x20 */
} SPI_Reg_TypeDef;


/********************************peripheral definitions*****************************************************************/


/*
 * peripheral definition
 */
#define GPIOA   ((GPIO_Reg_TypeDef*) GPIOA_BASEADDR)
#define GPIOB   ((GPIO_Reg_TypeDef*) GPIOB_BASEADDR)
#define GPIOC   ((GPIO_Reg_TypeDef*) GPIOC_BASEADDR)
#define GPIOD   ((GPIO_Reg_TypeDef*) GPIOD_BASEADDR)
#define GPIOE   ((GPIO_Reg_TypeDef*) GPIOE_BASEADDR)
#define GPIOH   ((GPIO_Reg_TypeDef*) GPIOH_BASEADDR)

#define EXTI    ((EXTI_Reg_TypeDef*) EXTI_BASEADDR)
#define SYSCFG  ((SYSCFG_Reg_TypeDef*) SYSCFG_BASEADDR)

#define RCC     ((RCC_Reg_TypeDef*) RCC_BASEADDR)

#define NVIC    ((NVIC_Reg_TypeDef*) NVIC_BASEADDR)


/*
 * SPI definition
 */
#define SPI1          ((SPI_Reg_TypeDef*) SPI1_BASEADDR)
#define SPI2          ((SPI_Reg_TypeDef*) SPI2_BASEADDR)
#define SPI3          ((SPI_Reg_TypeDef*) SPI3_BASEADDR)


/**
  * Clock enable GPIO peripherals
  */
#define GPIOA_PCLK_EN()   (RCC->AHB1ENR |= (1U << 0U))
#define GPIOB_PCLK_EN()   (RCC->AHB1ENR |= (1U << 1U))
#define GPIOC_PCLK_EN()   (RCC->AHB1ENR |= (1U << 2U))
#define GPIOD_PCLK_EN()   (RCC->AHB1ENR |= (1U << 3U))
#define GPIOE_PCLK_EN()   (RCC->AHB1ENR |= (1U << 4U))
#define GPIOH_PCLK_EN()   (RCC->AHB1ENR |= (1U << 7U))


/**
  * Clock enable for I2Cx peripherals
  */
#define I2C1_PCLK_EN()      (RCC->APB1ENR |= (1U << 21U))
#define I2C2_PCLK_EN()      (RCC->APB1ENR |= (1U << 22U))
#define I2C3_PCLK_EN()      (RCC->APB1ENR |= (1U << 23U))

/**
  * Clock enable for SPIx peripherals
  */
#define SPI1_PCLK_EN()      (RCC->APB2ENR |= (1U << 12U))
#define SPI2_PCLK_EN()      (RCC->APB1ENR |= (1U << 14U))
#define SPI3_PCLK_EN()      (RCC->APB1ENR |= (1U << 15U))

/**
  * Clock enable for USARTx peripherals
  */
#define USART1_PCLK_EN()    (RCC->APB2ENR |= (1U << 4U))
#define USART2_PCLK_EN()    (RCC->APB1ENR |= (1U << 17U))
#define USART6_PCLK_EN()    (RCC->APB2ENR |= (1U << 5U))

/**
  * Clock enable for SYSCFG peripheral
  */
#define SYSCFG_PCLK_EN()    (RCC->APB2ENR |= (1U << 14U))

/**
  * Clock disable for I2Cx peripherals
  */

#define I2C1_PCLK_DI()      (RCC->APB1ENR &= ~(1U << 21U))
#define I2C2_PCLK_DI()      (RCC->APB1ENR &= ~(1U << 22U))
#define I2C3_PCLK_DI()      (RCC->APB1ENR &= ~(1U << 23U))

/**
  * Clock disable for SPIx peripherals
  */
#define SPI1_PCLK_DI()      (RCC->APB2ENR &= ~(1U << 12U))
#define SPI2_PCLK_DI()      (RCC->APB1ENR &= ~(1U << 14U))
#define SPI3_PCLK_DI()      (RCC->APB1ENR &= ~(1U << 15U))

/**
  * Clock disable for USARTx peripherals
  */
#define USART1_PCLK_DI()    (RCC->APB2ENR &= ~(1U << 4U))
#define USART2_PCLK_DI()    (RCC->APB1ENR &= ~(1U << 17U))
#define USART6_PCLK_DI()    (RCC->APB1ENR &= ~(1U << 5U))

/**
  * Clock disable for SYSCFG peripheral
  */
#define SYSCFG_PCLK_DI()    (RCC->APB2ENR &= ~(1U << 14U))

/*
 * Two types implementations of gpio_base_to_code convertion function below 
 */


// #define GPIO_BASEADDR_TO_CODE(x)  ((x == GPIOA)?0:\
//                                    (x == GPIOB)?1:\
//                                    (x == GPIOC)?2:\
//                                    (x == GPIOD)?3:\
//                                    (x == GPIOE)?4:\
//                                    (x == GPIOH)?7:0)


static inline uint8_t gpio_base_to_code(const GPIO_Reg_TypeDef *pGPIOx) 
{
  if (pGPIOx == GPIOA) return 0;
  if (pGPIOx == GPIOB) return 1;
  if (pGPIOx == GPIOC) return 2;
  if (pGPIOx == GPIOD) return 3;
  if (pGPIOx == GPIOE) return 4;
  if (pGPIOx == GPIOH) return 7;
}


/*
 * IRQ Numbers from vector table
 */

#define IRQ_NO_EXTI0      6
#define IRQ_NO_EXTI1      7
#define IRQ_NO_EXTI2      8
#define IRQ_NO_EXTI3      9
#define IRQ_NO_EXTI4      10
#define IRQ_NO_EXTI9_5    23
#define IRQ_NO_EXTI15_10  40   

/*
 * IRQ Priority numbers
 */

#define NVIC_IRQ_PRIO0        0
#define NVIC_IRQ_PRIO1        1
#define NVIC_IRQ_PRIO2        2
#define NVIC_IRQ_PRIO3        3
#define NVIC_IRQ_PRIO4        4
#define NVIC_IRQ_PRIO5        5
#define NVIC_IRQ_PRIO6        6
#define NVIC_IRQ_PRIO7        7
#define NVIC_IRQ_PRIO8        8
#define NVIC_IRQ_PRIO9        9
#define NVIC_IRQ_PRIO10       10
#define NVIC_IRQ_PRIO11       11
#define NVIC_IRQ_PRIO12       12
#define NVIC_IRQ_PRIO13       13
#define NVIC_IRQ_PRIO14       14
#define NVIC_IRQ_PRIO15       15


/*
 * Other Macros
 */
#define ENABLE              1
#define DISABLE             0
#define SET                 ENABLE
#define RESET               DISABLE
#define GPIO_PIN_SET        SET
#define GPIO_PIN_RESET      RESET
#define FLAG_SET            SET
#define FLAG_RESET          RESET


/********************bit positions of SPI peripheral**********************************/
#define SPI_CR1_CPHA            0
#define SPI_CR1_CPOL            1
#define SPI_CR1_MSTR            2
#define SPI_CR1_BR              3
#define SPI_CR1_SPE             6
#define SPI_CR1_LSBFIRST        7
#define SPI_CR1_SSI             8
#define SPI_CR1_SSM             9
#define SPI_CR1_RXONLY          10
#define SPI_CR1_DFF             11
#define SPI_CR1_CRCNEXT         12
#define SPI_CR1_CRCEN           13
#define SPI_CR1_BIDIOE          14
#define SPI_CR1_BIDIMODE        15

#define SPI_CR2_RXDMAEN         0
#define SPI_CR2_TXDMAEN         1
#define SPI_CR2_SSOE            2
#define SPI_CR2_FRF             4
#define SPI_CR2_ERRIE           5
#define SPI_CR2_RXNEIE          6
#define SPI_CR2_TXEIE           7

#define SPI_SR_RXNE             0
#define SPI_SR_TXE              1
#define SPI_SR_CHSIDE           2
#define SPI_SR_UDR              3
#define SPI_SR_CRCERR           4
#define SPI_SR_MODF             5
#define SPI_SR_OVR              6
#define SPI_SR_BSY              7
#define SPI_SR_FRE              8

#endif /* INC_STM32F411XX_H_ */