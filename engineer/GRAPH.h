#pragma once
#include "JUDGEMENT_DATA_PACKAGE.h"
#include<cstdlib>
#include"UART.h"
#include<cstring>
class GRAPH
{
	static uint32_t id;
public:
	GRAPH(uint8_t is_char);
	graphic_data_struct_t m_data;
	uint32_t m_id;
	uint8_t is_char = 0;
	uint8_t m_char_data[30];
};

class RECTENGLE:public GRAPH
{
public:
	RECTENGLE(uint16_t beginX, uint16_t beginY, uint16_t endX, uint16_t endY, uint16_t line_size = 1);
};
class CIRCLE:public GRAPH
{
public:
	CIRCLE(uint16_t focusX,uint16_t focusY,uint16_t r, uint16_t line_size=1);
};
class ELLIPSE :public GRAPH
{
public:
	ELLIPSE(uint16_t focusX, uint16_t focusY, uint16_t a,uint16_t b, uint16_t line_size=1);
};
class ARC :public GRAPH
{
public:
	ARC(uint16_t focusX, uint16_t focusY, uint16_t beginAngle, uint16_t endAngle,uint16_t a,uint16_t b, uint16_t line_size=1);
};
class NUMBER_INTGER :public GRAPH
{
public:
	NUMBER_INTGER(uint16_t beginX, uint16_t beginY, uint32_t num, uint16_t font_size=20, uint16_t line_size=1);
};
class CHARACTER :public GRAPH
{
public:
	CHARACTER(uint16_t beginX, uint16_t beginY, uint32_t length, uint8_t* data, uint16_t font_size=20, uint16_t line_size=1);
};
class NUMBER_FLOAT :public GRAPH
{
public:
	NUMBER_FLOAT(uint16_t beginX, uint16_t beginY, uint32_t num, uint16_t font_size=20, uint16_t line_size=1);

};
class LINE:public GRAPH
{
public:
	LINE(uint16_t beginX, uint16_t beginY, uint16_t endX, uint16_t endY, uint16_t line_size = 1);
};
