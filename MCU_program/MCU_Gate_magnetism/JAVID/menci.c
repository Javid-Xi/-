/**
************************************************************
* @file         menci.c
* @brief        �����Ŵ����ݴ���

* @author       Javid
* @date         2019-02-20
* @version      1.0
*
***********************************************************/
#include "stm32f10x.h"
#include "menci.h"
#include "delay.h"
#include "led.h"

/*****************IO��ʼ������******************/
void MENCI_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); //ʹ��GPIOBʱ��

    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4; //�Ŵ�
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //���ó���������
    GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIOB
}

/*****************�����Ŵ����ݴ�����******************/
void MENCI_Send(void)
{
    static u8 menci_up = 1, menci_down = 1;
    if(menci_up && MENCI)
    {
        menci_up = 0; //�������Ŵ��Ѿ��ֿ�
        menci_down = 1;
        USART_SendData(USART1, MENCI_ON);
    }
    else if(menci_down && MENCI == 0)
    {
        menci_down = 0; //�������Ŵ��Ѿ�����
        menci_up = 1;
        USART_SendData(USART1, MENCI_OFF); //������
    }
}

/*****************LED״̬���º���******************/
void LED_Update(void)
{
    if(MENCI)//�Ŵŷֿ�
    {
        LED_safe = OFF;
        LED_danger = ON;
    }
    else
    {
        LED_safe = ON;
        LED_danger = OFF;
    }
}




