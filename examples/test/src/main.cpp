// #include "stm32f4xx.h"
// #include "stm32f4xx_nucleo.h"
#include "stm32f401xe.h"
#include "system_stm32f4xx.h"
#include "stm32f4xx_hal_gpio.h"
#include "stm32f4xx_hal_rcc.h"

GPIO_InitTypeDef GPIO_InitStructure; 

int main(void)
{

    // HAL_Init(); 

    __GPIOA_CLK_ENABLE();
    GPIO_InitStructure.Pin   = GPIO_PIN_5;
    GPIO_InitStructure.Mode  = GPIO_MODE_OUTPUT_PP;    
    GPIO_InitStructure.Pull  = GPIO_PULLUP;
    GPIO_InitStructure.Speed = GPIO_SPEED_HIGH;  
    HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);    

    __GPIOC_CLK_ENABLE();
    GPIO_InitStructure.Pin   = GPIO_PIN_13;
    GPIO_InitStructure.Mode  = GPIO_MODE_INPUT;
    GPIO_InitStructure.Pull  = GPIO_PULLDOWN;
    GPIO_InitStructure.Speed = GPIO_SPEED_FAST;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStructure);

    while (1)
    {
        int stateOfPushButton = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13);
        if (stateOfPushButton == 1)
        {         
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET); 
        }
        else
        {
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
        }
    }
}