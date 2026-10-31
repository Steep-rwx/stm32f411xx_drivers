#include "stm32f411xx_rcc_driver.h"
#include "stm32f411xx.h"



// APB1
uint32_t RCC_GetPCLK1Value(void)
{
    static const uint32_t AHB_Prescaler[8]  = {2, 4, 8, 16, 64, 128, 256, 512};
    static const uint32_t APB1_Prescaler[4] = {2, 4, 8, 16};

    uint32_t pclk1, system_clk;
    uint16_t ahbprescl_value, apb1prescl_value;
    uint8_t clksrc, prescl_val_binary;

    clksrc = ((RCC->CFGR >> 2U) & 0x3);
    if (clksrc == 0)
    {
        system_clk = 16000000;
    } else if (clksrc == 1)
    {
        system_clk = 25000000;
    } else if (clksrc == 2)
    {
        system_clk = RCC_GetPLLOutputClock();
    }

    //ahb
    prescl_val_binary = ((RCC->CFGR >> 4) & 0xF);
    if (prescl_val_binary < 8)
    {
        ahbprescl_value = 1;
    } else
    {
        ahbprescl_value = AHB_Prescaler[prescl_val_binary - 8];
    }
    
    //apb1
    prescl_val_binary = ((RCC->CFGR >> 10) & 0x7);
    if (prescl_val_binary < 4)
    {
        apb1prescl_value = 1;
    } else
    {
        apb1prescl_value = APB1_Prescaler[prescl_val_binary - 4];
    }

    pclk1 = (system_clk / ahbprescl_value / apb1prescl_value);

    return pclk1;
}

// Not used
uint32_t RCC_GetPLLOutputClock(void)
{
    return 0;
}