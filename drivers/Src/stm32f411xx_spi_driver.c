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
void SPI_Init(SPI_Handle_TypeDef *pSPIHandle);          /* Initialise SPI through SPI reg + SPI settings struct */

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