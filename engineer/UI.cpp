#include "UI.h"

void UI::create_UI()
{
	add_graph(&test_UI0);
	add_graph(&test_UI1);
	add_graph(&m_LIFT_frame);
	add_graph(&test_chars);
}
void UI::add_graph(GRAPH* graph)
{
	for (uint8_t i = 0; i < 10; i++)
	{
		if (!graph->is_char&&m_layers_graph_num[i] < 7)
		{
			m_graphs[i][m_layers_graph_num[i]++] = graph;
			break;
		}
		else if(graph->is_char)
		{
			i = i + !!m_layers_graph_num[i];
			m_graphs[i][m_layers_graph_num[i]++] = graph;
			break;
		}
	}
}
void UI::delete_graph(GRAPH* graph)
{

}
//UI::UI(JUDGEMENT* judgement)
//{
//	m_judgment = judgement;
//}
//void UI::init_UI()
//{
//	m_UI_frame[0] = 0xa5;
//	//m_UI_frame[1] = 21;
//
//	m_UI_frame[5] = 0x01;
//	m_UI_frame[6] = 0x03;
//
//	/*m_UI_frame[7] = 0x01;
//	m_UI_frame[8] = 0x01;*/
//
//	m_UI_frame[9] = m_judgment->game_robot_status_t.robot_id;
//	m_UI_frame[10] = 0x00;
//	m_UI_frame[11] = m_judgment->game_robot_status_t.robot_id;
//	m_UI_frame[12] = 0x01;
//	/*test_data[37] = { 0xA5,21,0x00,0x00,0x00,
//						 0x01,0x03,
//						 0x01,0x01,0x03,0x00,0x03,0x01 };*/
//
//	static uint8_t layer_index = 0;
//	layer_index %= 10;
//	if (m_layers_graph_num[layer_index] == 0)
//	{
//		layer_index++;
//		return;
//	}
//	if (m_graphs[layer_index][0]->is_char)
//	{
//		m_UI_frame[7] = 0x10;
//		m_UI_frame[8] = 0x01;
//		m_UI_frame[1] = 6 + 15 + 30;
//		m_graphs[layer_index][0]->m_data.layer = layer_index;
//		m_graphs[layer_index][0]->m_data.operate_tpye = 1;
//
//		memcpy(m_UI_frame + 5 + 2 + 6, &m_graphs[layer_index][0]->m_data, sizeof(graphic_data_struct_t));
//		memcpy(m_UI_frame + 5 + 2 + 6 + 15, &m_graphs[layer_index][0]->m_char_data, sizeof(uint8_t) * 30);
//
//		CRC_CHECK::Append_CRC8_Check_Sum(m_UI_frame, 5);
//		CRC_CHECK::Append_CRC16_Check_Sum(m_UI_frame, 5 + 2 + 6 + 15 + 30 + 2);
//		m_judgment->m_uart->set_transmit_data(m_UI_frame, 5 + 2 + 6 + 15 + 30 + 2);
//		m_judgment->m_uart->transmit_data();
//		layer_index++;
//		return;
//	}
//	else
//	{
//		uint8_t step = 7;
//		m_UI_frame[7] = 0x04;
//		m_UI_frame[8] = 0x01;
//		m_UI_frame[1] = 6 + 15 * step;
//
//		for (int i = 0; i < step; i++)
//		{
//			if (m_graphs[layer_index][i])
//			{
//				m_graphs[layer_index][i]->m_data.layer = layer_index;
//				m_graphs[layer_index][i]->m_data.layer = 1;
//				memcpy(m_UI_frame + 13 + 15 * i, &m_graphs[layer_index][i]->m_data, sizeof(graphic_data_struct_t));
//
//			}
//		}
//
//		CRC_CHECK::Append_CRC8_Check_Sum(m_UI_frame, 5);
//		CRC_CHECK::Append_CRC16_Check_Sum(m_UI_frame, 15 + 15 * step);
//		m_judgment->m_uart->set_transmit_data(m_UI_frame, 15 + 15 * step);
//		m_judgment->m_uart->transmit_data();
//		layer_index++;
//		return;
//	}
//	layer_index++;
//
//}
//
//void  UI::upDateUI()
//{
//	static uint8_t layer_index = 0;
//	layer_index %= 10;
//	if (m_layers_graph_num[layer_index] == 0)
//	{
//		layer_index++;
//		return;
//	}
//	if (m_graphs[layer_index][0]->is_char)
//	{
//		m_UI_frame[7] = 0x10;
//		m_UI_frame[8] = 0x01;
//		m_UI_frame[1] = 6 + 15 + 30;
//		m_graphs[layer_index][0]->m_data.layer = layer_index;
//		m_graphs[layer_index][0]->m_data.operate_tpye = 2;
//		memcpy(m_UI_frame + 5 + 2 + 6, &m_graphs[layer_index][0]->m_data, sizeof(graphic_data_struct_t));
//		memcpy(m_UI_frame + 5 + 2 + 6 + 15, &m_graphs[layer_index][0]->m_char_data, sizeof(uint8_t) * 30);
//
//		CRC_CHECK::Append_CRC8_Check_Sum(m_UI_frame, 5);
//		CRC_CHECK::Append_CRC16_Check_Sum(m_UI_frame, 5 + 2 + 6 + 15 + 30 + 2);
//		m_judgment->m_uart->set_transmit_data(m_UI_frame, 5 + 2 + 6 + 15 + 30 + 2);
//		m_judgment->m_uart->transmit_data();
//		layer_index++;
//		return;
//	}
//	else
//	{
//		uint8_t step = 7;
//		m_UI_frame[7] = 0x04;
//		m_UI_frame[8] = 0x01;
//		m_UI_frame[1] = 6 + 15 * step;
//
//		for (int i = 0; i < step; i++)
//		{
//			if (m_graphs[layer_index][i])
//			{
//				m_graphs[layer_index][i]->m_data.layer = layer_index;
//				m_graphs[layer_index][0]->m_data.operate_tpye = 2;
//
//				memcpy(m_UI_frame + 13 + 15 * i, &m_graphs[layer_index][i]->m_data, sizeof(graphic_data_struct_t));
//
//			}
//		}
//
//		CRC_CHECK::Append_CRC8_Check_Sum(m_UI_frame, 5);
//		CRC_CHECK::Append_CRC16_Check_Sum(m_UI_frame, 15 + 15 * step);
//		m_judgment->m_uart->set_transmit_data(m_UI_frame, 15 + 15 * step);
//		m_judgment->m_uart->transmit_data();
//		layer_index++;
//		return;
//	}
//	layer_index++;
//}
