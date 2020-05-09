/**
************************************************************
* @file         gpio.c
* @brief        �������ģ������

* @author       Javid
* @date         2019-02-20
* @version      1.0
*
***********************************************************/

#include "stm32f10x.h"
#include "gpio.h"
#include "led.h"

/*****************IO��ʼ������******************/
void INPUT_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); //ʹ��GPIOBʱ��

    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_5 | GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //���ó���������
    GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIOB
}

/*****************����״̬���ͺ���******************/
void MQ_2_Send(void)
{
    static u8 MQ_2_up = 1, MQ_2_down = 1;
    if(MQ_2_up && !MQ_2)
    {
        MQ_2_up = 0;
        MQ_2_down = 1;
        USART_SendData(USART1, MQ_2_ON);
    }
    else if(MQ_2_down && (!MQ_2 == 0))
    {
        MQ_2_down = 0;
        MQ_2_up = 1;
        USART_SendData(USART1, MQ_2_OFF);
    }
}

/*****************����״̬���ͺ���******************/
void Flame_1_Send(void)
{
    static u8 Flame_1_up = 1, Flame_1_down = 1;
    if(Flame_1_up && Flame_1)
    {
        Flame_1_up = 0;
        Flame_1_down = 1;
        USART_SendData(USART1, Flame_1_ON);
    }
    else if(Flame_1_down && Flame_1 == 0)
    {
        Flame_1_down = 0;
        Flame_1_up = 1;
        USART_SendData(USART1, Flame_1_OFF);
    }
}

/*****************LED���º���******************/
void LED_Update(void)
{
    if(!MQ_2)
    {
        led_MQ_2 = ON;
    }
    else
    {
        led_MQ_2 = OFF;
    }
    if(Flame_1)
    {
        LED_Flame_1 = ON;
    }
    else
    {
        LED_Flame_1 = OFF;
    }
}



