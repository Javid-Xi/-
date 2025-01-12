/**
************************************************************
* @file         led.c
* @brief        LED驱动

* @author       Javid
* @date         2019-02-20
* @version      1.0
*
***********************************************************/

#include "led.h"
#include "stm32f10x.h"

//LED IO初始化
void LED_Init(void)
{

    GPIO_InitTypeDef  GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //使能PB

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//IO口速度为50MHz
    GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.0,1
    GPIO_ResetBits(GPIOB, GPIO_Pin_0 | GPIO_Pin_1); //PB0,1 输出低
}

