#include "stm32f411xx_rcc_driver.h"
#include "stm32f411xx.h"
#include <stdint.h>

static const uint32_t AHB_Prescaler[8]  = {2, 4, 8, 16, 64, 128, 256, 512};
static const uint32_t APBx_Prescaler[4] = {2, 4, 8, 16};

/********************************************************************
 * @fn                  - RCC_GetPCLK1Value
 *
 * @brief               - Getting APB1 value
 *
 *
 * @return              - APB1 Pclk value
 *
 * @Note                - none
 *
 */
uint32_t RCC_GetPCLK1Value(void)
{

    uint32_t pclk1, system_clk;
    uint16_t ahbprescl_value, apb1prescl_value;
    uint8_t clksrc, prescl_val_binary;

    clksrc = ((RCC->CFGR >> 2U) & 0x3);
    if (clksrc == 0)
    {
        system_clk = 16000000;
    } 
    else if (clksrc == 1)
    {
        system_clk = 25000000;
    } 
    else if (clksrc == 2)
    {
        system_clk = RCC_GetPLLOutputClock();
    }

    //ahb
    prescl_val_binary = ((RCC->CFGR >> 4) & 0xF);
    if (prescl_val_binary < 8)
    {
        ahbprescl_value = 1;
    } 
    else
    {
        ahbprescl_value = AHB_Prescaler[prescl_val_binary - 8];
    }
    
    //apb1
    prescl_val_binary = ((RCC->CFGR >> 10) & 0x7);
    if (prescl_val_binary < 4)
    {
        apb1prescl_value = 1;
    } 
    else
    {
        apb1prescl_value = APBx_Prescaler[prescl_val_binary - 4];
    }

    pclk1 = (system_clk / ahbprescl_value / apb1prescl_value);

    return pclk1;
}

/********************************************************************
 * @fn                  - RCC_GetPCLK2Value
 *
 * @brief               - Getting APB2 value
 *
 *
 * @return              - APB2 Pclk value
 *
 * @Note                - none
 *
 */
uint32_t RCC_GetPCLK2Value(void)
{
    uint32_t SystemClk = 0, temp, pclk2;
    uint8_t ahb_prescale_value, apb2_prescaler_value;
    uint8_t clk_selected = ((RCC->CFGR >> 2) & 0x03);

    if (clk_selected == 0)
    {
        SystemClk = 16000000;
    } 
    else if (clk_selected == 1)
    {
        SystemClk = 25000000;
    }
    else if (clk_selected == 2)
    {
        RCC_GetPLLOutputClock();
    }

    temp = ((RCC->CFGR >> 4) & 0xF);

    if (temp < 8)
    {
        ahb_prescale_value = 1;
    }
    else
    {
        ahb_prescale_value = AHB_Prescaler[temp - 8];
    }

    temp = ((RCC->CFGR >> 13) & 0x7);

    if (temp < 4)
    {
        apb2_prescaler_value = 1;
    }
    else
    {
        apb2_prescaler_value = APBx_Prescaler[temp - 4];
    }

    pclk2 = SystemClk / ahb_prescale_value / apb2_prescaler_value;

    return pclk2;
}

// Not used
uint32_t RCC_GetPLLOutputClock(void)
{
    return 0;
}