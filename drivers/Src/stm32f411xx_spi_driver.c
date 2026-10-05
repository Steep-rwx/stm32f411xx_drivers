#include "stm32f411xx_spi_driver.h"
#include "stm32f411xx.h"


#include <stdint.h>
#include <stddef.h>


/********************************************************************
 * @fn                  - SPI_PeriClockControl
 *
 * @brief               - Function which enables/disables clock for choosed SPI
 *
 * @param[in]           - pSPIx: SPI base address
 * @param[in]           - enOrDi: ENABLE or DISABLE macro
 *
 * @return              - none
 *
 * @Note                - none
 *
 */
void SPI_PeriClockControl(SPI_Reg_TypeDef *pSPIx, uint8_t enOrDi)
{
    if(enOrDi == ENABLE) 
    {
        if (pSPIx == SPI1)      { SPI1_PCLK_EN(); }
        else if (pSPIx == SPI2) { SPI2_PCLK_EN(); }
        else if (pSPIx == SPI3) { SPI3_PCLK_EN(); }
    } else
    {
        if (pSPIx == SPI1)      { SPI1_PCLK_DI(); }
        else if (pSPIx == SPI2) { SPI2_PCLK_DI(); }
        else if (pSPIx == SPI3) { SPI3_PCLK_DI(); }
    }
}


/********************************************************************
 * @fn                  - SPI_Handler_TypeDef
 *
 * @brief               - Initializes the specifies SPI
 *
 * @param[in]           - pSPIHandle: A structure that contains pin base address and pin config
 *
 * @return              - none
 *
 * @Note                - none
 *
 */
void SPI_Init(SPI_Handle_TypeDef *pSPIHandle)
{
    uint32_t tempreg = 0;

    //configuring mode
    tempreg |= (pSPIHandle->SPIConfig.SPI_DeviceMode << 2);

    //configuring bus config
    if (pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_FULLDUPLEX)
    {
        tempreg &= ~(1 << 15);
    } else if (pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_HALFDUPLEX)
    {
        tempreg |= (1 << 15);
    } else if (pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_SIMPLEX_RXONLY)
    {
        tempreg &= ~(1 << 15);
        tempreg |= (1 << 10);
    }

    //configuring Sclk speed
    tempreg |= (pSPIHandle->SPIConfig.SPI_SclkSpeed << 3);

    //configuring DFF
    tempreg |= (pSPIHandle->SPIConfig.SPI_DFF << 11);

    //configuring CPOL
    tempreg |= (pSPIHandle->SPIConfig.SPI_CPOL << 1);
    
    //configuring CPHA
    tempreg |= (pSPIHandle->SPIConfig.SPI_CPHA << 0);

    //configuring SSM
    tempreg |= (pSPIHandle->SPIConfig.SPI_SSM << 9);

    pSPIHandle->pSPIx->CR1 = tempreg;
}

/********************************************************************
 * @fn                  - SPI_DeInit
 *
 * @brief               - Deinitializes the specified pin
 *
 * @param[in]           - pSPIx: A base address of SPIx
 *
 * @return              - none
 *
 * @Note                - none
 *
 */
void SPI_DeInit(SPI_Reg_TypeDef *pSPIx);                /* Reset through RCC */

/********************************************************************
 * @fn                  - SPI_SendData
 *
 * @brief               - Send data through SPI
 *
 * @param[in]           - pSPIx: base address
 * @param[in]           - pTxBuffer: Tx buffer
 * @param[in]           - length: length of info
 *
 * @return              - none
 *
 * @Note                - none
 *
 */
void SPI_SendData(SPI_Reg_TypeDef *pSPIx, uint8_t *pTxBuffer, uint32_t length);

/********************************************************************
 * @fn                  - SPI_ReceiveData
 *
 * @brief               - Receive data through SPI
 *
 * @param[in]           - pSPIx: base address
 * @param[in]           - pRxBuffer: Rx buffer
 * @param[in]           - length: length of info
 *
 * @return              - none
 *
 * @Note                - none
 *
 */
void SPI_ReceiveData(SPI_Reg_TypeDef *pSPIx, uint8_t *pRxBuffer, uint32_t length);

/*******************************************************************
 * @fn                  - SPI_IRQConfig
 *
 * @brief               - Configures IRQ from number
 *
 * @param[in]           - IRQNumber: Number choosed IRQ
 * @param[in]           - enOrDi: ENABLE or DISABLE macro
 *
 * @return              - none
 *
 * @Note                - none
 *
 */
void SPI_IRQConfig(uint8_t IRQNumber, uint8_t enOrDi);

/*******************************************************************
 * @fn                  - SPI_IRQPriority
 *
 * @brief               - Configures IRQ Priority
 *
 * @param[in]           - IRQNumber: Number choosed IRQ
 * @param[in]           - IRQPriority: Choosed priority 0-15
 *
 * @return              - none
 *
 * @Note                - none
 *
 */
void SPI_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority);

/********************************************************************
 * @fn                  - SPI_IRQHandling
 *
 * @brief               - Clears pending interrupt
 *
 * @param[in]           - pinNumber: number which need to clear
 * @param[in]           - 
 * @param[in]           -
 *
 * @return              - none
 *
 * @Note                - none
 *
 */
void SPI_IRQHandling(SPI_Handle_TypeDef *pSPIHandle);