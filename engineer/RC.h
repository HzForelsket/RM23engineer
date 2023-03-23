#pragma once
#include"UART.h"
#include<stdlib.h>
class MOUSE
{
public:
	int16_t x, y, z;
	bool left, right;
};

class RC
{
	enum ROD_POSITION
	{
		UP=1,DOWN,MID
	};
	UART* m_uart = nullptr;
	void RC_IRQHandler();
	uint8_t *m_recieve_data=nullptr, *m_trainsmit_data=nullptr;
public:
	bool W, A, S, D, SHIFT, CTRL, Q, E, R, F, G, Z, X, C;
	int16_t left_horizontal, right_horizontal, left_vertical, right_vertical;
	ROD_POSITION right_rod, left_rod;
	MOUSE m_mouse;
	void init(UART* uart);
};

