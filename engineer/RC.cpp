#include "RC.h"

void RC::RC_IRQHandler()
{
	m_recieve_data = m_uart->m_receive_date;
	if (m_uart->m_length != 18)return;
	right_horizontal = ((m_recieve_data[0] | m_recieve_data[1] << 8) & 0x07FF) - 1024;
	right_vertical = ((m_recieve_data[1] >> 3 | m_recieve_data[2] << 5) & 0x07FF) - 1024;
	left_horizontal = ((m_recieve_data[2] >> 6 | m_recieve_data[3] << 2 | m_recieve_data[4] << 10) & 0x07FF) - 1024;
	left_vertical = ((m_recieve_data[4] >> 1 | m_recieve_data[5] << 7) & 0x07FF) - 1024;

	left_rod = (ROD_POSITION)(((m_recieve_data[5] >> 4) & 0x0C) >> 2);//s2
	right_rod = (ROD_POSITION)((m_recieve_data[5] >> 4) & 0x03);//s1

	m_mouse.x = ((int16_t)m_recieve_data[6]) | (((int16_t)m_recieve_data[7]) << 8);
	m_mouse.y = ((int16_t)m_recieve_data[8]) | (((int16_t)m_recieve_data[9]) << 8);

	m_mouse.z = ((int16_t)m_recieve_data[10]) | (((int16_t)m_recieve_data[11] << 8));

	m_mouse.left = m_recieve_data[12];
	m_mouse.right = m_recieve_data[13];

	
	W = m_recieve_data[14]&0x01;
	S = m_recieve_data[14] & 0x02;
	A = m_recieve_data[14] & 0x04;
	D = m_recieve_data[14] & 0x08;
	SHIFT = m_recieve_data[14] & 0x10;
	CTRL = m_recieve_data[14] & 0x20;
	Q = m_recieve_data[14] & 0x40;
	E = m_recieve_data[14] & 0x80;

	R = m_recieve_data[15]&0x01;
	F = m_recieve_data[15]&0x02;
	G = m_recieve_data[15]&0x04;
	Z = m_recieve_data[15]&0x08;
	X = m_recieve_data[15]&0x10;
	C = m_recieve_data[15]&0x20;
}

void RC::init(UART* uart)
{
	m_uart = uart;
	m_uart->p_use = this;
	void (RC:: * p)(void) = &RC::RC_IRQHandler;
	auto func = reinterpret_cast<void(**)(void(*))>(&p);
	m_uart->UART_IRQHandler = *func;
}

