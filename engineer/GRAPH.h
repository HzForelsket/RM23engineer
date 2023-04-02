#pragma once
#include"JUDGEMENT.h"
#include"JUDGEMENT_DATA_PACKAGE.h"
#include<queue>
class GRAPH
{
	
public:
	virtual void destroy() = 0;
	virtual void create() = 0;
	virtual void change_sylte(uint8_t color,uint8_t width);
	void upData();
	GRAPH(uint16_t line_width = 1, uint8_t color = 0, uint8_t layer = 1);

protected:
	static std::queue<GRAPH*> m_graphs;
	static uint32_t id;
	uint8_t m_layer : 4;
	uint8_t m_color : 4;
	uint16_t m_width : 10;
	uint32_t m_id : 24;

	/*void draw_line(int16_t begin_x, int16_t begin_y, int16_t end_x, int16_t end_y);
	void draw_rectangle(int16_t begin_x, int16_t begin_y, int16_t end_x, int16_t end_y);
	void draw_circle(int16_t r, int16_t center_x, int16_t center_y);
	void draw_ellipse(int16_t a, int16_t b, int16_t center_x, int16_t center_y);
	void draw_arc();
	void draw_double(int16_t decimal_digits, int16_t x, int16_t y, float data);
	void draw_int(int16_t x, int16_t y, int32_t data);
	void draw_char(int16_t x, int16_t y, uint8_t* data, int16_t length);
	void set_line_width();
	void set_color();
	void set_text_style();
	void set_layer(int8_t layer);
	void clear_layer(int8_t layer);*/
};

class RECTENGLE:public GRAPH
{
public:
	RECTENGLE(uint16_t beginX, uint16_t beginY, uint16_t endX, uint16_t endY);
	void destory();
	void create();
private:
	uint16_t m_beginX : 11;
	uint16_t m_beginY : 11;
	uint16_t m_endX : 11;
	uint16_t m_endY : 11;
};
class CIRCLE:public GRAPH
{
public:
	CIRCLE(uint16_t focusX,uint16_t focusY,uint16_t r);
	void destory();
	void create();
private:
	uint16_t m_focusX : 11;
	uint16_t m_focusY : 11;
	uint16_t m_r : 10;
};
class ELLIPSE :public GRAPH
{
public:
	ELLIPSE(uint16_t focusX, uint16_t focusY, uint16_t a,uint16_t b);
	void destory();
	void create();
private:
	uint16_t m_focusX : 11;
	uint16_t m_focusY : 11;
	uint16_t m_a : 11;
	uint16_t m_b : 11;

};
class ARC :public GRAPH
{
public:
	ARC(uint16_t focusX, uint16_t focusY, uint16_t beginAngle, uint16_t endAngle,uint16_t a,uint16_t b);
	void destory();
	void create();
private:
	uint16_t m_focusX : 11;
	uint16_t m_focusY : 11;
	uint16_t m_beginAngle : 11;
	uint16_t m_endAngle : 11;
	uint16_t m_a : 11;
	uint16_t m_b : 11;
};
class INTGER :public GRAPH
{
public:
	INTGER(uint16_t beginX, uint16_t beginY, uint16_t font , uint32_t num);
	void destory();
	void create();
private:
	uint16_t m_beginX : 11;
	uint16_t m_beginY : 11;
	uint16_t m_font : 9;
	uint32_t m_num;
};
class CHARACTER :public GRAPH
{
public:
	CHARACTER(uint16_t beginX, uint16_t beginY, uint16_t font, uint32_t length);
	void destory();
	void create();
private:
	uint16_t m_beginX : 11;
	uint16_t m_beginY : 11;
	uint16_t m_font : 9;
	uint16_t m_length:9;
};
class FLOAT :public GRAPH
{
public:
	FLOAT(uint16_t beginX, uint16_t beginY, uint16_t font, uint32_t num,uint16_t dot);
	void destory();
	void create();
private:
	uint16_t m_beginX : 11;
	uint16_t m_beginY : 11;
	uint16_t m_font : 9;
	uint16_t m_dot : 9;
	uint32_t m_num;
};
ext_student_interactive_header_data_t		student_interactive_header_data_t;
robot_interactive_data_t					m_robot_interactive_data_t;
ext_client_custom_graphic_delete_t			client_custom_graphic_delete_t;
graphic_data_struct_t						m_graphic_data_struct_t;
