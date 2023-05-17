#include "BLUETOOTH.h"

void BLUETOOTH::init(UART* uart)
{
	m_uart = uart;
	m_uart->p_use = this;
	void (BLUETOOTH:: * p)(void) = &BLUETOOTH::BLUETOOTH_IRQHandler;
	auto func = reinterpret_cast<void(**)(void(*))>(&p);
	m_uart->UART_IRQHandler = *func;
}

void BLUETOOTH::transmit(uint8_t* data, int8_t length)
{
	memcpy(transmit_data + 2, data, sizeof(uint8_t) * length);
	transmit_data[length + 2] = 0xe0;
	transmit_data[length + 3] = 0x0e;
	m_uart->set_transmit_data(transmit_data, length+4);
	m_uart->transmit_data();
}

void BLUETOOTH::BLUETOOTH_IRQHandler(void)
{
	int head=0,begin=0,end=0;
	//m_length = m_uart->m_length;
	//if (m_uart->m_receive_date[0] == 0xa0 && m_uart->m_receive_date[1] == 0x0a && m_uart->m_receive_date[m_length - 2] == 0xe0 && m_uart->m_receive_date[m_length - 1] == 0x0e)
	//{
	//	m_ok //= true;
	//	memcpy(receive_data, m_uart->m_receive_date + 2, m_length - 4);
	//}

	m_length = m_uart->m_length;
	head = m_uart->m_receive_date[0];
	while (head != 0xa0 && m_uart->receive_count == m_length && begin < m_length / 2)
	{
		begin = begin + 1;
		head = m_uart->m_receive_date[begin];
	}
	if (m_uart->m_receive_date[begin] == 0xa0 && m_uart->m_receive_date[begin+1] == 0x0a)
	{
		memcpy(receive_data, m_uart->m_receive_date + begin + 2, m_length/2 -4);
		m_ok = true;
	}
}
