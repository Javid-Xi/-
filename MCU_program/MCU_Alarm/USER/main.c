/**
************************************************************
* @file         main.c
* @brief        Alarm control function
* @author       Javid Xi
* @date         2019-02-22
* @version      1.0
* @copyright    LElink
* 
* @note         Alarm_model KEY: 1000
*  				Manual/Automatic_alarm_mode KEY: 1001 
*
***********************************************************/
#include "stm32f10x.h"
#include "delay.h"
#include "alarm.h"
#include "usart.h"
/**************SYN6288оƬ��������*********************/
uint8_t SYN_StopCom[]={0xFD,0X00,0X02,0X02,0XFD};//ֹͣ�ϳ�
uint8_t SYN_SuspendCom[]={0XFD,0X00,0X02,0X03,0XFC};//��ͣ�ϳ�
uint8_t SYN_RecoverCom[]={0XFD,0X00,0X02,0X04,0XFB};//�ָ��ϳ�
uint8_t SYN_ChackCom[]={0XFD,0X00,0X02,0X21,0XDE};//״̬��ѯ
uint8_t SYN_PowerDownCom[]={0XFD,0X00,0X02,0X88,0X77};//����POWER DOWN ״̬����
uint8_t Voice_max[]={0xFD,0x00,0x08,0x01,0x01,0x5B,0x76,0x31,0x36,0x5D,0x82};//�������11
uint8_t Voice_medium[]={0xFD,0x00,0x08,0x01,0x01,0x5B,0x76,0x31,0x30,0x5D,0x84};//�е�����11
uint8_t Voice_min[]={0xFD,0x00,0x07,0x01,0x01,0x5B,0x76,0x32,0x5D,0xB8};//��С����
uint8_t Voice_medium_1[]={0xFD,0x00,0x07,0x01,0x01,0x5B,0x76,0x39,0x5D,0xB3};//�еȼ�1����10
uint8_t Background_music_max[]={0xFD,0x00,0x08,0x01,0x01,0x5B,0x6D,0x31,0x36,0x5D,0x99};//��󱳾�����11
uint8_t Background_music_medium[]={0xFD,0x00,0x07,0x01,0x01,0x5B,0x6D,0x39,0x5D,0xA8};//�еȱ�������10
uint8_t Background_music_min[]={0xFD,0x00,0x07,0x01,0x01,0x5B,0x6D,0x31,0x5D,0xA0};//��С��������
uint8_t Background_music_medium_1[]={0xFD,0x00,0x08,0x01,0x01,0x5B,0x6D,0x31,0x31,0x5D,0x9E};//�еȼ�1��������11
uint8_t MENCI_1_voice[]={0xFD,0x00,0x11,0x01,0x01,0xC3,0xC5,0xB4,0xB0,0xD2,0xBB,0xD2,0xD1,0xB1,0xBB,0xB4,0xF2,0xBF,0xAA,0xDD};//�Ŵ�һ�ѱ���20
uint8_t MENCI_2_voice[]={0xFD,0x00,0x11,0x01,0x01,0xC3,0xC5,0xB4,0xB0,0xB6,0xFE,0xD2,0xD1,0xB1,0xBB,0xB4,0xF2,0xBF,0xAA,0xFC };//�Ŵ����ѱ���
uint8_t MQ_2_voice[]={0xFD,0x00,0x0F,0x01,0x01,0xD1,0xCC,0xCE,0xED,0xC5,0xA8,0xB6,0xC8,0xB9,0xFD,0xB8,0xDF,0xFC};//����Ũ�ȹ���18
uint8_t Flame_1_voice[]={0xFD,0x00,0x0D,0x01,0x01,0xBC,0xEC,0xB2,0xE2,0xB5,0xBD,0xBB,0xF0,0xD1,0xE6,0x84};//��⵽����16
uint8_t Alarm_1_voice[]={0xFD,0x00,0x0B,0x01,0x01,0xB1,0xA8,0xBE,0xAF,0xCC,0xE1,0xCA,0xBE,0xA7};//������ʾ1
uint8_t Model_0_voice[]={0xFD,0x00,0x15,0x01,0x01,0xD7,0xD4,0xB6,0xAF,0xB1,0xA8,0xBE,0xAF,0xC4,0xA3,0xCA,0xBD,0xD2,0xD1,0xBF,0xAA,0xC6,0xF4,0xCE};//�Զ�����ģʽ�ѿ��� 24
uint8_t Model_1_voice[]={0xFD,0x00,0x15,0x01,0x01,0xBC,0xE0,0xBF,0xD8,0xB9,0xA4,0xD7,0xF7,0xC4,0xA3,0xCA,0xBD,0xD2,0xD1,0xBF,0xAA,0xC6,0xF4,0xDA};//��ع���ģʽ�ѿ��� 24
uint8_t Welcome_1_voice[]={0xFD,0x00,0x17,0x01,0x01,0xBB,0xB6,0xD3,0xAD,0xC0,0xB4,0xB5,0xBD,0xB6,0xFE,0xC1,0xE3,0xBE,0xC5,0xCA,0xB5,0xD1,0xE9,0xCA,0xD2,0xAB};//��ӭ����209ʵ����
uint8_t Initialization_voice[]={0xFD,0x00,0x39,0x01,0x21,0xCF,0xB5,0xCD,0xB3,0xB3,0xF5,0xCA,0xBC,0xBB,0xAF,0xD6,0xD0,0xA3,0xAC,0xA3,0xAC,0xD4,0xB8,0xC4,0xFA,0xD3,0xD0,0xD2,
	0xBB,0xB8,0xF6,0xB0,0xB2,0xC8,0xAB,0xB5,0xC4,0xBC,0xD2,0xA3,0xAC,0xA3,0xAC,0xA3,0xAC,0xCF,0xB5,0xCD,0xB3,0xB3,0xF5,0xCA,0xBC,0xBB,0xAF,0xCD,0xEA,0xB3,0xC9,0xB8};//ϵͳ��ʼ���У���Ը����һ����ȫ�ļң���ϵͳ��ʼ�����	60
	
/***********************************************/

#define delay_time 3	
	
extern dataPoint_t currentDataPoint;
extern u8 Voice_work;
	
void sys_Initialization(void);
void userHandle(void);
void Automatic_alarm_mode(void);
void Manual_alarm_mode(void);
void delay_s(u16 ns);


int main()
{
	delay_init();
 	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	Alarm_Init();
	uart_1_init(115200);
	uart_2_init(9600);
	sys_Initialization();
  while(1)
	{
		userHandle();
		delay_ms(100);
	}
}

/*****************ϵͳ��ʼ������******************/ 
void sys_Initialization(void)
{
	delay_ms(200);
	Send_stringdata(Background_music_medium_1,11);
	delay_ms(200);
	Send_stringdata(Voice_medium_1,10);
	delay_ms(200);
	Send_stringdata(Initialization_voice,60);
	delay_s(10);
	delay_ms(300);
	Beep_Initialization(); 
	Send_stringdata(Voice_max,11);
	delay_s(1);
}

/*****************�û����ݴ�����******************/ 
void userHandle(void)
{
	static u8 Model_up=0;
	if(currentDataPoint.valueMODEL)
	{
		if(Model_up)
		{
			Model_up=0;
					LED_model_1();
			Send_stringdata(Model_1_voice,24);
			delay_s(3);
		}
		Manual_alarm_mode();
	}
	else
	{
		if(Model_up==0)
		{
			Model_up=1;
			LED_model_2();
			Send_stringdata(Model_0_voice,24);
			delay_s(10);
		}
		Automatic_alarm_mode();

	}
}

/*****************�Զ�����ģʽ���ݴ�����******************/ 
void Automatic_alarm_mode(void)
{
	static u8 MENCI_1_up=1,MENCI_2_up=1,MQ_2_up=1,Flame_1_up=1;
	if(currentDataPoint.valueMENCI_1||currentDataPoint.valueMENCI_2||currentDataPoint.valueMQ_2||currentDataPoint.valueflame_1)//�Ŵ�1
	{
		if(currentDataPoint.valueMENCI_1&&MENCI_1_up)//�Ŵ�1
		{
			MENCI_1_up=0;
			Send_stringdata(MENCI_1_voice,20);
			delay_s(delay_time);
		}
		else if (!currentDataPoint.valueMENCI_1)
		{
			MENCI_1_up=1;
		}
		if(currentDataPoint.valueMENCI_2&&MENCI_2_up)//�Ŵ�2
		{
			MENCI_2_up=0;
			Send_stringdata(MENCI_2_voice,20);
			delay_s(delay_time);
		}
		else if (!currentDataPoint.valueMENCI_2)
		{
			MENCI_2_up=1;
		}
		if(currentDataPoint.valueMQ_2&&MQ_2_up)//����
		{
			MQ_2_up=0;
			Send_stringdata(MQ_2_voice,18);
			delay_s(delay_time);
		}
		else if (!currentDataPoint.valueMQ_2)
		{
			MQ_2_up=1;
		}
		if(currentDataPoint.valueflame_1&&Flame_1_up)//����
		{
			Flame_1_up=0;
			Send_stringdata(Flame_1_voice,16);
			delay_s(delay_time);
		}
		else if (!currentDataPoint.valueflame_1)
		{
			Flame_1_up=1;
		}
		Beep_Alarm_ON();
	}
	else 
	{
		Beep_Alarm_OFF();
		MENCI_1_up=1;
		MENCI_2_up=1;
		MQ_2_up=1;
		Flame_1_up=1;
	}
}

/*****************�ֶ�����ģʽ���ݴ�����******************/ 
void Manual_alarm_mode(void)
{
	if(currentDataPoint.valueAlarm==1)
	{
		Send_stringdata(Alarm_1_voice,14);
		Beep_Alarm_OFF();	
		delay_s(2);
	}
	else if(currentDataPoint.valueAlarm==2)
	{
		Beep_Alarm_ON();
	}
	else if(currentDataPoint.valueAlarm==3)
	{
		Beep_Alarm_ON();
		Send_stringdata(Alarm_1_voice,14);
		delay_s(2);
	}
	else 	Beep_Alarm_OFF();	
}


/*****************��ʱ����******************/ 
void delay_s(u16 ns)
{
	u16 i=0;
	while(i<ns)
	{
		i++;
		delay_ms(1000);
	}
}
