#pragma once
#include "GRAPH.h"
#include <map>
#include <vector>
#include<map>
#include"CRC_CHECK.h"
//#include"JUDGEMENT.h"
#define MAX_LENGTH  200
class UI
{
	//JUDGEMENT* m_judgment = nullptr;
public:	
	//std::map<uint32_t, GRAPH> m_graphs;
	uint8_t m_layers_graph_num[10];
	//std::vector<GRAPH*> m_graphs[10];
	GRAPH* m_graphs[10][7];

	RECTENGLE m_LIFT_frame{8,720,70,800};
	NUMBER_FLOAT test_UI0{ 10, 800, 0x135 };
	LINE test_UI1{ 0, 0, 960, 540 };
	CHARACTER test_chars{ 0,720,10,(uint8_t*)&"ABCDEFGHIJ" };
	uint8_t m_UI_frame[MAX_LENGTH];
	//UI(JUDGEMENT* judgement);
	virtual void init_UI() = 0;
	virtual void create_UI();
	virtual void add_graph( GRAPH* graph);
	virtual void delete_graph( GRAPH* graph);
	virtual void upDateUI() = 0;
};

