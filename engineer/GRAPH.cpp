#include"GRAPH.h"
uint32_t GRAPH::id = 0;

GRAPH::GRAPH(uint8_t is)
{
	id++;
	memset(&m_data, 0, sizeof(graphic_data_struct_t));
	m_id = id;
	uint32_t t = m_id;
	memcpy(m_data.graphic_name, &t, sizeof(uint8_t) * 3);
	m_data.operate_tpye = 1;
	m_data.width = 1;
	is_char = is;
}

RECTENGLE::RECTENGLE(uint16_t beginX, uint16_t beginY, uint16_t endX, uint16_t endY, uint16_t line_size):GRAPH(0)
{
	m_data.width = line_size;
	m_data.graphic_tpye = 1;
	m_data.start_x = beginX;
	m_data.start_y = beginY;
	m_data.end_x = endX;
	m_data.end_y = endY;
}

CIRCLE::CIRCLE(uint16_t focusX, uint16_t focusY, uint16_t r, uint16_t line_size) :GRAPH(0)
{
	m_data.graphic_tpye = 2;
	m_data.width = line_size;
	m_data.start_x = focusX;
	m_data.start_y = focusY;
	m_data.radius = r;
}

CHARACTER::CHARACTER(uint16_t beginX, uint16_t beginY, uint32_t length, uint8_t* data, uint16_t font_size, uint16_t line_size) : GRAPH(1)
{
	//is_char = 1;
	m_data.width = line_size;
	m_data.graphic_tpye = 7;
	m_data.start_angle = font_size;
	m_data.end_angle = length;
	m_data.start_x = beginX;
	m_data.start_y = beginY;
	memcpy(m_char_data, data, sizeof(uint8_t) * length);
}

ELLIPSE::ELLIPSE(uint16_t focusX, uint16_t focusY, uint16_t a, uint16_t b, uint16_t line_size) : GRAPH(0)
{
	m_data.graphic_tpye = 3;

	m_data.width = line_size;
	m_data.start_x = focusX;
	m_data.start_y = focusY;
	m_data.end_x = a;
	m_data.end_y = b;
}

NUMBER_INTGER::NUMBER_INTGER(uint16_t beginX, uint16_t beginY, uint32_t num, uint16_t font_size, uint16_t line_size) :GRAPH(0)
{
	m_data.start_angle = 20;
	m_data.width = line_size;
	m_data.graphic_tpye = 6;
	m_data.start_angle = font_size;
	m_data.start_x = beginX;
	m_data.start_y = beginY;

	memcpy(((uint8_t*)&m_data)+11, &num, sizeof(uint32_t));
}

ARC::ARC(uint16_t focusX, uint16_t focusY, uint16_t beginAngle, uint16_t endAngle, uint16_t a, uint16_t b, uint16_t line_size) :GRAPH(0)
{
	m_data.graphic_tpye = 4;

	m_data.width = line_size;
	m_data.start_x = focusX;
	m_data.start_y = focusY;
	m_data.start_angle = beginAngle;
	m_data.end_angle = endAngle;
	m_data.end_x = a;
	m_data.end_y = b;
}

NUMBER_FLOAT::NUMBER_FLOAT(uint16_t beginX, uint16_t beginY, uint32_t num,uint16_t font_size,uint16_t line_size) :GRAPH(0)
{
	m_data.width = line_size;
	m_data.graphic_tpye = 5;
	m_data.start_angle = font_size;
	m_data.end_angle = 3;
	m_data.start_x = beginX;
	m_data.start_y = beginY;
	memcpy(((uint8_t*)&m_data) + 11, &num, sizeof(uint8_t) * 4);
}

LINE::LINE(uint16_t beginX, uint16_t beginY, uint16_t endX, uint16_t endY, uint16_t line_size) :GRAPH(0)
{
	m_data.width = line_size;

	m_data.graphic_tpye = 0;
	m_data.start_x = beginX;
	m_data.start_y = beginY;
	m_data.end_x = endX;
	m_data.end_y = endY;
}
