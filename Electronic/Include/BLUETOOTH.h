#pragma once
#include"UART.h"
const auto BLUETOOTH_MAXLENGTH = 100;
class BLUETOOTH
{

	UART* m_uart;
	int m_length;
public:
	bool m_ok;
	void init(UART* uart);
	uint8_t receive_data[BLUETOOTH_MAXLENGTH], transmit_data[BLUETOOTH_MAXLENGTH] = { 0xa0,0x0a };
	void transmit(uint8_t* data, int8_t length);
	void BLUETOOTH_IRQHandler(void);
};