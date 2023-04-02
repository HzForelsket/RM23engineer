#include "JUDGEMENT.h"

void JUDGEMENT::JUDGEMENT_IRQHandler()
{
	uint8_t* dataFrame = m_uart->m_receive_date;
	uint32_t completedLength = 0;
	while (completedLength<=m_uart->m_length)
	{
		if (!CRC_CHECK::Verify_CRC8_Check_Sum(dataFrame, 5)) return;
		uint16_t data_length = (uint16_t)dataFrame[1] | ((uint16_t)dataFrame[2] << 8);
		if (!CRC_CHECK::Verify_CRC16_Check_Sum(dataFrame, 9 + data_length)) return;
		uint16_t cmd_id = (uint16_t)dataFrame[5] | ((uint16_t)dataFrame[6] << 8);
		uint8_t* data = dataFrame + 7;
		switch (cmd_id)
		{
			case 0x0001:
				memcpy(&game_status_t, data, sizeof(uint8_t) * 11);
				break;
			case 0x0002:
				memcpy(&game_result_t, data, sizeof(uint8_t) * 1);
				break;
			case 0x0003:
				memcpy(&game_robot_HP_t, data, sizeof(uint8_t) * 28);
				break;
			case 0x0004:
				break;
			case 0x0005:
				memcpy(&ICRA_buff_debuff_zone_and_lurk_status_t, data, sizeof(uint8_t) * 11);
				break;
			case 0x0101:
				memcpy(&ICRA_buff_debuff_zone_and_lurk_status_t, data, sizeof(uint8_t) * 4);
				break;
			case 0x0102:
				memcpy(&supply_projectile_action_t, data, sizeof(uint8_t) * 3);
				break;
			case 0x0103:
				break;
			case 0x0104:
				memcpy(&referee_warning_t, data, sizeof(uint8_t) * 2);
				break;
			case 0x0105:
				memcpy(&referee_warning_t, data, sizeof(uint8_t) * 1);
				break;
			case 0x0201:
				memcpy(&game_robot_status_t, data, sizeof(uint8_t) * 15);
				break;
			case 0x0202:
				memcpy(&power_heat_data_t, data, sizeof(uint8_t) * 14);
				break;
			case 0x0203:
				memcpy(&game_robot_pos_t, data, sizeof(uint8_t) * 16);
				break;
			case 0x0204:
				memcpy(&buff_t, data, sizeof(uint8_t) * 1);
				break;
			case 0x0205:
				memcpy(&m_aerial_robot_energy_t, data, sizeof(uint8_t) * 3);
				break;
			case 0x0206:
				memcpy(&robot_hurt_t, data, sizeof(uint8_t) * 1);
				break;
			case 0x0207:
				memcpy(&shoot_data_t, data, sizeof(uint8_t) * 6);
				break;
			case 0x0208:
				memcpy(&bullet_remaining_t, data, sizeof(uint8_t) * 2);
				break;
			case 0x0209:
				memcpy(&rfid_status_t, data, sizeof(uint8_t) * 4);
				break;
			case 0x020A:
				memcpy(&dart_client_cmd_t, data, sizeof(uint8_t) * 12);
				break;
			case 0x0301:
				break;
			case 0x0302:
				break;
			case 0x0303:
				memcpy(&robot_command_t, data, sizeof(uint8_t) * 15);
				break;
			case 0x0304:
				break;
			case 0x0305:
				memcpy(&client_map_command_t, data, sizeof(uint8_t) * 10);
				break;
			default:
				break;
		}
		dataFrame = dataFrame + 9 + data_length;
		completedLength += 9 + data_length;
	}
}

void JUDGEMENT::init(UART* uart)
{
	m_uart = uart;
	m_uart->p_use = this;
	void (JUDGEMENT:: * p)(void) = &JUDGEMENT::JUDGEMENT_IRQHandler;
	auto func = reinterpret_cast<void(**)(void(*))>(&p);
	m_uart->UART_IRQHandler = *func;
}

JUDGEMENT::JUDGEMENT()//:UI(this)
{

}

void JUDGEMENT::init_UI()
{
	m_UI_frame[0] = 0xa5;
	//m_UI_frame[1] = 21;

	m_UI_frame[5] = 0x01;
	m_UI_frame[6] = 0x03;

	/*m_UI_frame[7] = 0x01;
	m_UI_frame[8] = 0x01;*/

	m_UI_frame[9] = game_robot_status_t.robot_id;
	m_UI_frame[10] = 0x00;
	m_UI_frame[11] = game_robot_status_t.robot_id;
	m_UI_frame[12] = 0x01;
	/*test_data[37] = { 0xA5,21,0x00,0x00,0x00,
						 0x01,0x03,
						 0x01,0x01,0x03,0x00,0x03,0x01 };*/

	static uint8_t layer_index = 0;
	layer_index %= 10; 
	if (m_layers_graph_num[layer_index] == 0)
	{
		layer_index++;
		return;
	}
	if (m_graphs[layer_index][0]->is_char)
		{
			m_UI_frame[7] = 0x10;
			m_UI_frame[8] = 0x01;
			m_UI_frame[1] = 6 + 15 + 30;
			m_graphs[layer_index][0]->m_data.layer = layer_index;
			m_graphs[layer_index][0]->m_data.operate_tpye = 1;

			memcpy(m_UI_frame + 5 + 2 + 6, &m_graphs[layer_index][0]->m_data, sizeof(graphic_data_struct_t));
			memcpy(m_UI_frame + 5 + 2 + 6 + 15, &m_graphs[layer_index][0]->m_char_data, sizeof(uint8_t) * 30);

			CRC_CHECK::Append_CRC8_Check_Sum(m_UI_frame, 5);
			CRC_CHECK::Append_CRC16_Check_Sum(m_UI_frame, 5 + 2 + 6 + 15 + 30 + 2);
			m_uart->set_transmit_data(m_UI_frame, 5 + 2 + 6 + 15 + 30 + 2);
			m_uart->transmit_data();
			layer_index++;
			return;
		}
	else
		{
		uint8_t step = 7;
		m_UI_frame[7] = 0x04;
		m_UI_frame[8] = 0x01;
		m_UI_frame[1] = 6 + 15 * step;

		for (int i = 0; i < step; i++)
		{
			if (m_graphs[layer_index][i])
			{
				m_graphs[layer_index][i]->m_data.layer = layer_index;
				m_graphs[layer_index][i]->m_data.layer = 1;
				memcpy(m_UI_frame + 13 + 15 * i, &m_graphs[layer_index][i]->m_data, sizeof(graphic_data_struct_t));

			}
		}

		CRC_CHECK::Append_CRC8_Check_Sum(m_UI_frame, 5);
		CRC_CHECK::Append_CRC16_Check_Sum(m_UI_frame, 15 + 15 * step);
		m_uart->set_transmit_data(m_UI_frame, 15 + 15 * step);
		m_uart->transmit_data();
		layer_index++;
		return;
	}
	layer_index++;

}

void  JUDGEMENT::upDateUI()
{
	static uint8_t layer_index = 0;
	layer_index %= 10;
	if (m_layers_graph_num[layer_index] == 0)
	{
		layer_index++;
		return;
	}
	if (m_graphs[layer_index][0]->is_char)
	{
		m_UI_frame[7] = 0x10;
		m_UI_frame[8] = 0x01;
		m_UI_frame[1] = 6 + 15 + 30;
		m_graphs[layer_index][0]->m_data.layer = layer_index;
		m_graphs[layer_index][0]->m_data.operate_tpye = 2;
		memcpy(m_UI_frame + 5 + 2 + 6, &m_graphs[layer_index][0]->m_data, sizeof(graphic_data_struct_t));
		memcpy(m_UI_frame + 5 + 2 + 6 + 15, &m_graphs[layer_index][0]->m_char_data, sizeof(uint8_t) * 30);

		CRC_CHECK::Append_CRC8_Check_Sum(m_UI_frame, 5);
		CRC_CHECK::Append_CRC16_Check_Sum(m_UI_frame, 5 + 2 + 6 + 15 + 30 + 2);
		m_uart->set_transmit_data(m_UI_frame, 5 + 2 + 6 + 15 + 30 + 2);
		m_uart->transmit_data();
		layer_index++;
		return;
	}
	else
	{
		uint8_t step = 7;
		m_UI_frame[7] = 0x04;
		m_UI_frame[8] = 0x01;
		m_UI_frame[1] = 6 + 15 * step;

		for (int i = 0; i < step; i++)
		{
			if (m_graphs[layer_index][i])
			{
				m_graphs[layer_index][i]->m_data.layer = layer_index;
				m_graphs[layer_index][0]->m_data.operate_tpye = 2;

				memcpy(m_UI_frame + 13 + 15 * i, &m_graphs[layer_index][i]->m_data, sizeof(graphic_data_struct_t));

			}
		}

		CRC_CHECK::Append_CRC8_Check_Sum(m_UI_frame, 5);
		CRC_CHECK::Append_CRC16_Check_Sum(m_UI_frame, 15 + 15 * step);
		m_uart->set_transmit_data(m_UI_frame, 15 + 15 * step);
		m_uart->transmit_data();
		layer_index++;
		return;
	}
	layer_index++;
}



void JUDGEMENT::add_graph(GRAPH* graph)
{
	for (uint8_t i = 0; i < 10; i++)
	{
		if (!graph->is_char && m_layers_graph_num[i] < 7)
		{
			m_graphs[i][m_layers_graph_num[i]++] = graph;
			break;
		}
		else if (graph->is_char)
		{
			i = i + !!m_layers_graph_num[i];
			m_graphs[i][m_layers_graph_num[i]++] = graph;
			break;
		}
	}
}
void JUDGEMENT::delete_graph(GRAPH* graph)
{
	
}