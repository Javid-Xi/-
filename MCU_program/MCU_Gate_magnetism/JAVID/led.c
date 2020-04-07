/**
************************************************************
* @file         led.c
* @brief        LED����

* @author       Javid
* @date         2019-02-20
* @version      1.0
*
***********************************************************/

#include "led.h"
#include "stm32f10x.h"

//LED IO��ʼ��
void LED_Init(void)
{

    GPIO_InitTypeDef  GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //ʹ��PB

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //�������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//IO���ٶ�Ϊ50MHz
    GPIO_Init(GPIOB, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOB.0,1
    GPIO_ResetBits(GPIOB, GPIO_Pin_0 | GPIO_Pin_1); //PB0,1 �����
}

