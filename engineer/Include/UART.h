#pragma once
#include<stm32f4xx_usart.h>
#include <stm32f4xx_dma.h>
#include <stm32f4xx_rcc.h>
#include"GPIO.h"
#include<vector>
#include"TIMER.h"
constexpr int MAXLEN = 100;
class UART
{
	
	USART_TypeDef* m_uart;
	DMA_Stream_TypeDef* m_stream;
	void DMA_RX_Config(DMA_Stream_TypeDef* DMA_Streamx, u32 chx, u32 par, u32 mar, u16 ndtr);
	void DMA_TX_Config(DMA_Stream_TypeDef* DMA_Streamx, u32 chx, u32 par, u32 mar, u16 ndtr);
	uint16_t m_transmit_length = 0;
public:
	uint8_t m_trains_data[MAXLEN],m_receive_date[MAXLEN];
	bool m_open_dma;
	USART_TypeDef* get_UARTx();
	void receive();
	void init(USART_TypeDef* UARTx, uint32_t BaudRate, std::vector<GPIO> UART_GPIO,uint32_t length,bool open_DMA=false);
	//打开dma后length失效
	void* p_use;
	void (*UART_IRQHandler)(void(*));
	uint32_t receive_count;//接收中断计数
	uint32_t m_length;//空闲中断接收到的长度
	void transmit_data();
	void set_transmit_data(uint8_t* data, uint32_t length);

};
extern UART uart1, uart2, uart3, uart4, uart5, uart6;
