/**
************************************************************
* @file         hal_usart.c
* @brief        ����3���ݴ���

* @author       Javid
* @date         2019-02-20
* @version      1.0
*
***********************************************************/
#include "hal_usart.h"

dataPoint_t Zigbee_dataPoint_t;
extern UART_HandleTypeDef huart3;

/*****************�������ݴ���******************/ 
void Zigbee_data_handle(uint8_t Zigbee_data)
{
    if((Zigbee_data & 0xF0) == 0x10) //�����Ŵ�1
    {

        Zigbee_dataPoint_t.valueMENCI_1 = Zigbee_data & 0x01;
        GIZWITS_LOG("Recevice MENCI_1 data \n");
    }
    else if((Zigbee_data & 0xF0) == 0x20) //�����Ŵ�2
    {
        Zigbee_dataPoint_t.valueMENCI_2 = Zigbee_data & 0x01;
        GIZWITS_LOG("Recevice MENCI_2 data \n");
    }
    else if((Zigbee_data & 0xF0) == 0x30) //����
    {
        Zigbee_dataPoint_t.valueMQ_2 = Zigbee_data & 0x01;
        GIZWITS_LOG("Recevice MQ_2 data \n");
    }
    else if((Zigbee_data & 0xF0) == 0x40) //����
    {
        Zigbee_dataPoint_t.valueflame_1 = Zigbee_data & 0x01;
        GIZWITS_LOG("Recevice Flame_1 data \n");
    }

}

/*****************�������ݷ���******************/ 
void Zigbee_send(uint8_t Zigbee_Alarm)
{
    HAL_UART_Transmit(&huart3, &Zigbee_Alarm, 1, 10);
}



