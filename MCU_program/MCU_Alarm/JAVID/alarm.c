/**
************************************************************
* @file         alarm.c
* @brief        ��������������

* @author       Javid
* @date         2019-02-20
* @version      1.0
*
***********************************************************/

#include "alarm.h"
#include "delay.h"

void Alarm_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //ʹ��PB

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_7;		
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOB.0,1
	GPIO_ResetBits(GPIOB,GPIO_Pin_0|GPIO_Pin_1);//PB0,1 �����
	GPIO_ResetBits(GPIOB,GPIO_Pin_7);//PB7 �����

}

void LED_model_1(void)
{
	LED0=0;
	LED1=1;
}

void LED_model_2(void)
{
	LED0=0;
	LED1=1;
}

void Beep_Alarm_ON(void)
{
	Alarm=0;
}

void Beep_Alarm_OFF(void)
{
	Alarm=1;
}

void Beep_Initialization(void)
{
	Alarm=0;
	delay_ms(150);
	Alarm=1;
	delay_ms(150);
	Alarm=0;
	delay_ms(150);
	Alarm=1;

}
