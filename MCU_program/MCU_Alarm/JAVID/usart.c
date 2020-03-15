#include "sys.h"
#include "usart.h"	
#include "stdio.h"

dataPoint_t currentDataPoint;
//u8 Voice_work=Voice_Free;
//////////////////////////////////////////////////////////////////

//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
_sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{      
	while((USART3->SR&0X40)==0);//ѭ������,ֱ���������   
    USART3->DR = (u8) ch;      
	return ch;
}
#endif 


 

//����״̬
  
void uart_1_init(u32 bound)
	{
		//GPIO�˿�����
		GPIO_InitTypeDef GPIO_InitStructure;
		USART_InitTypeDef USART_InitStructure;
		NVIC_InitTypeDef NVIC_InitStructure;
		 
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��USART1��GPIOAʱ��
		
		//USART1_TX   GPIOA.9
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
		GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.9
		 
		//USART1_RX	  GPIOA.10��ʼ��
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
		GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.10  

		//Usart1 NVIC ����
		NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;//��ռ���ȼ�0
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		//�����ȼ�0
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
		NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
		
		 //USART ��ʼ������

		USART_InitStructure.USART_BaudRate = bound;//���ڲ�����
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
		USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
		USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

		USART_Init(USART1, &USART_InitStructure); //��ʼ������1
		USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
		USART_Cmd(USART1, ENABLE);                    //ʹ�ܴ���1 

}

void uart_2_init(u32 bound)
	{
  //GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
		
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE); //ʹ��USART2ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��GPIOAʱ��
  
	//USART1_TX   GPIOA.2
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //PA.2
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.2
   
  //USART1_RX	  GPIOA.3��ʼ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;//PA3
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.3 
				
	//Usart2 NVIC ����
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;//��ռ���ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		//�����ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���

   //USART ��ʼ������

	USART_InitStructure.USART_BaudRate = bound;//���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

  USART_Init(USART2, &USART_InitStructure); //��ʼ������2
//	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
  USART_Cmd(USART2, ENABLE);                    //ʹ�ܴ���2

	}

void uart_3_init(u32 bound)
{
  //GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
		
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE); //ʹ��USART3ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	//ʹ��GPIOBʱ��
  
	//USART3_TX   
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //PB.10
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
  GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIOB.10
   
  //USART3_RX	  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;//PB11
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
  GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIOB.11 

   //USART ��ʼ������

	USART_InitStructure.USART_BaudRate = bound;//���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

  USART_Init(USART3, &USART_InitStructure); //��ʼ������3
  USART_Cmd(USART3, ENABLE);                    //ʹ�ܴ���3
}
	
void USART1_IRQHandler(void)  //����1�жϷ������
	{
	u8 Zigbee_data=0;

	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //�����ж�
		{
		Zigbee_data=USART_ReceiveData(USART1);//��ȡ���յ�������
		USART1_data_handle(Zigbee_data);
		}   		 
			USART_ClearITPendingBit(USART1,USART_IT_RXNE);
  } 
	

void USART1_data_handle(u8 data)//����1�������ݴ�����
{
	if((data&0xF0)==0x80)
	{	
		if((data&0x0F)==0x00)
		{
			currentDataPoint.valueAlarm=0;
		//������
		}
		else if((data&0x0F)==0x01)
		{
			currentDataPoint.valueAlarm=1;
		//����ģʽ1
		}
		else if((data&0x0F)==0x02)
		{
			currentDataPoint.valueAlarm=2;
		//����ģʽ2
		}
		else if((data&0x0F)==0x03)
		{
			currentDataPoint.valueAlarm=3;
		//����ģʽ3
		}
	}
	else if((data&0xF0)==0x90)
	{
		if((data&0x0F)==0x00)
		{
			currentDataPoint.valueMODEL=0;
		//ģʽ0
		}
		else if((data&0x0F)==0x01)
		{
			currentDataPoint.valueMODEL=1;
		//ģʽ1
		}
	}
	else if((data&0xF0)==0x10)//�����Ŵ�1
	{
		if(data&0x0F)
		{
			currentDataPoint.valueMENCI_1=1;
		//�Ŵ�1 on
		}
		else currentDataPoint.valueMENCI_1=0;//menci off
	}
	else if((data&0xF0)==0x20)//�����Ŵ�2
	{
		if(data&0x0F)
		{
			currentDataPoint.valueMENCI_2 =1;
		//�Ŵ�2 on
		}
		else currentDataPoint.valueMENCI_2 =0;//menci off
	}
	else if((data&0xF0)==0x30)//����
	{
		if(data&0x0F)
		{
			currentDataPoint.valueMQ_2=1;
		//yanwu on
		}
		else currentDataPoint.valueMQ_2=0;//yanwu off
	}
	else if((data&0xF0)==0x40)//����
	{
		if(data&0x0F)
		{
			currentDataPoint.valueflame_1=1;
		//huoyan on
		}
		else currentDataPoint.valueflame_1=0;//huoyan off
	}
}

/************************************************************************
���������� ���ڷ����ַ�������
��ڲ����� 	*DAT���ַ���ָ��
�� �� ֵ�� none
����˵���� API ���ⲿʹ�ã�ֱ�ۣ�
**************************************************************************/
void Send_stringdata(uint8_t *DAT,uint8_t len)
{
	uint8_t i;
	for(i=0;i<len;i++)
	{
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET) 	;
	USART_SendData(USART2,*DAT++);
	USART_ClearFlag(USART2,USART_FLAG_TXE);
	}	
}
