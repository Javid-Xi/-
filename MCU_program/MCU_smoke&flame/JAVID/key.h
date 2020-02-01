#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 



//#define KEY0 PEin(4)   	//PE4
//#define KEY1 PEin(3)	//PE3 
//#define KEY2 PEin(2)	//PE2
//#define WK_UP PAin(0)	//PA0  WK_UP

#define KEY0  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)//��ȡ����0
#define KEY1  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1)//��ȡ����1
#define KEY2  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2)//��ȡ����2 
#define KEY3  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3)//��ȡ����3 ģʽһ
#define KEY4  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4)//��ȡ����4 
#define KEY5  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5)//��ȡ����5 ģʽ��
#define KEY6  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)//��ȡ����6 ģʽ���λ



#define KEY0_PRES 1	//KEY0����
#define KEY1_PRES	2	//KEY1����
#define KEY2_PRES	3	//KEY2����
#define KEY3_PRES 4	//KEY3����
#define KEY4_PRES	5	//KEY4����
#define KEY5_PRES	6	//KEY5����
#define KEY6_PRES 7	//KEY6����


void KEY_Init(void);//IO��ʼ��
u8 KEY_Scan(u8);  	//����ɨ�躯��					    
#endif
