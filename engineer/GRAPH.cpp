#include "GRAPH.h"
//void GRAPH::draw_line(int16_t begin_x, int16_t begin_y, int16_t end_x, int16_t end_y)
//{
//	static uint8_t test_name[3];
//	m_graphic_data_struct_t.graphic_name[0] = test_name[0];
//	m_graphic_data_struct_t.graphic_name[1] = test_name[1];
//	m_graphic_data_struct_t.graphic_name[2] = test_name[2];
//
//	m_graphic_data_struct_t.operate_tpye = 1;
//	static uint32_t test_type,test_layer,test_width, test_color;
//	m_graphic_data_struct_t.graphic_tpye = test_type;
//	m_graphic_data_struct_t.layer = test_layer;
//	m_graphic_data_struct_t.color = test_color;
//	m_graphic_data_struct_t.width = test_width;
//	m_graphic_data_struct_t.start_x = begin_x;
//	m_graphic_data_struct_t.start_y = begin_y;
//	m_graphic_data_struct_t.end_x = end_x;
//	m_graphic_data_struct_t.end_y = end_y;
//}
//
//void GRAPH::draw_rectangle(int16_t begin_x, int16_t begin_y, int16_t end_x, int16_t end_y)
//{
//}
//
//void GRAPH::draw_circle(int16_t r, int16_t center_x, int16_t center_y)
//{
//}
//
//void GRAPH::draw_ellipse(int16_t a, int16_t b, int16_t center_x, int16_t center_y)
//{
//}
//
//void GRAPH::draw_arc()
//{
//	/*int i;
//
//	for (i = 0; i < 3 && imagename[i] != 0; i++)
//		image->graphic_name[2 - i] = imagename[i];
//	image->graphic_tpye = UI_Graph_Arc;
//	image->operate_tpye = Graph_Operate;
//	image->layer = Graph_Layer;
//	image->color = Graph_Color;
//	image->width = Graph_Width;
//	image->start_x = Start_x;
//	image->start_y = Start_y;
//	image->start_angle = Graph_StartAngle;
//	image->end_angle = Graph_EndAngle;
//	image->end_x = x_Length;
//	image->end_y = y_Length;*/
//}
//
//void GRAPH::draw_double(int16_t decimal_digits, int16_t x, int16_t y, float data)
//{
//	/*int i;
//
//	for (i = 0; i < 3 && imagename[i] != 0; i++)
//		image->graphic_name[2 - i] = imagename[i];
//	image->graphic_tpye = UI_Graph_Float;
//	image->operate_tpye = Graph_Operate;
//	image->layer = Graph_Layer;
//	image->color = Graph_Color;
//	image->width = Graph_Width;
//	image->start_x = Start_x;
//	image->start_y = Start_y;
//	image->start_angle = Graph_Size;
//	image->end_angle = Graph_Digit;
//	image->graph_Float = Graph_Float;*/
//}
//
//void GRAPH::draw_int(int16_t x, int16_t y, int32_t data)
//{
//}
//
//void GRAPH::draw_char(int16_t x, int16_t y, uint8_t* data, int16_t length)
//{
//}
//
//void GRAPH::set_line_width()
//{
//}
//
//void GRAPH::set_color()
//{
//}
//
//void GRAPH::set_text_style()
//{
//}
//
//void GRAPH::set_layer(int8_t layer)
//{
//}
//
//void GRAPH::clear_layer(int8_t layer)
//{
//}

uint32_t GRAPH::id = 0;
std::queue<GRAPH*> m_graphs;

void GRAPH::change_sylte(uint8_t color, uint8_t width)
{
	m_color = color;
	m_width = width;
}
void GRAPH::upData()
{
	uint32_t num = m_graphs.size();
	if (num == 1)
	{
		graphic_data_struct_t data;
		auto i = m_graphs.front();

	}
	else if (num <= 3)
	{
		
	}
	else if (num <= 5)
	{

	}
	else
	{

	}
}
GRAPH::GRAPH(uint16_t line_width, uint8_t color, uint8_t layer): m_width(line_width), m_layer(layer), m_color(color)
{
	m_id = id++;
}

RECTENGLE::RECTENGLE(uint16_t beginX, uint16_t beginY, uint16_t endX, uint16_t endY)
{
	m_beginX = beginX;
	m_beginY = beginY;
	m_endX = endX;
	m_endY = endY;
}

void RECTENGLE::destory()
{

}

void RECTENGLE::create()
{
	m_graphs.push(this);
}

CIRCLE::CIRCLE(uint16_t focusX, uint16_t focusY, uint16_t r)
{
}
void CIRCLE::destory()
{
}

void CIRCLE::create()
{
	m_graphs.push(this);

}

CHARACTER::CHARACTER(uint16_t beginX, uint16_t beginY, uint16_t font, uint32_t length)
{

}

void CHARACTER::create()
{
	m_graphs.push(this);

}
void CHARACTER::destory()
{
}

ELLIPSE::ELLIPSE(uint16_t focusX, uint16_t focusY, uint16_t a, uint16_t b)
{
	m_focusX = focusX;
	m_focusY = focusY;
	m_a = a;
	m_b = b;
}
void ELLIPSE::destory()
{

}

void ELLIPSE::create()
{
	m_graphs.push(this);

}

INTGER::INTGER(uint16_t beginX, uint16_t beginY, uint16_t font, uint32_t num)
{
	m_beginX = beginX;
	m_beginY = beginY;
	m_num = num;
	m_font = font;
}
void INTGER::destory()
{

}

void INTGER::create()
{
	m_graphs.push(this);

}

ARC::ARC(uint16_t focusX, uint16_t focusY, uint16_t beginAngle, uint16_t endAngle, uint16_t a, uint16_t b)
{
	m_focusX = focusX;
	m_focusY = focusY;
	m_beginAngle = beginAngle;
	m_endAngle = endAngle;
	m_a = a;
	m_b = b;
}
void ARC::destory()
{
}

void ARC::create()
{
	m_graphs.push(this);

}

FLOAT::FLOAT(uint16_t beginX, uint16_t beginY, uint16_t font, uint32_t num, uint16_t dot)
{
	m_beginX = beginX;
	m_beginY = beginY;
	m_font = font;
	m_num = num;
	m_dot = dot;
}
void FLOAT::destory()
{

}

void FLOAT::create()
{
	m_graphs.push(this);

}
