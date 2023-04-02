#pragma once
#include"CAN.h"
#include"GPIO.h"
#include<stm32f4xx_can.h>
#include<misc.h>
#include<map>
class RECEIVE_TEMP
{
public:
	uint8_t m_receive_data[8];
	RECEIVE_TEMP(uint8_t* t) { memcpy(m_receive_data, t, sizeof(uint8_t) * 8); };
	RECEIVE_TEMP() { memset(m_receive_data, 0, sizeof(uint8_t) * 8); };
};
class TRANSMIT_TEMP
{
public:
	uint8_t m_transmit_data[8];
	TRANSMIT_TEMP() { memset(m_transmit_data, 0, sizeof(uint8_t) * 8); };
};
class CAN
{
	CanRxMsg m_receive;
	CanTxMsg m_transmit;
	GPIO m_rx,m_tx;
	CAN_TypeDef* m_can;
	//uint8_t  m_transmit_data[8];
	std::map<uint32_t, TRANSMIT_TEMP> m_transmit_data;
	std::map<uint32_t, RECEIVE_TEMP> m_receive_data;
	void On_IQRHander();
public:
	void open_receive_interrput();
	void (*m_CANx_IRQHandler)(void);//中断任务执行函数指针
	std::map<uint32_t, RECEIVE_TEMP>::iterator read_data(uint32_t stdId);
	uint8_t transmit_data();
	void set_transmit_data(uint8_t* data,uint8_t length, uint8_t offset=0, uint32_t stdId=0);
	CAN& init(GPIO& rx,GPIO& tx, CAN_TypeDef* can, uint8_t tsjw= CAN_SJW_1tq, uint8_t tbs2= CAN_BS2_2tq, uint8_t tbs1= CAN_BS1_4tq, uint16_t brp=6, uint8_t mode= CAN_Mode_Normal);
};

