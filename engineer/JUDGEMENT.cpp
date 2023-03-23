#include "JUDGEMENT.h"

void JUDGEMENT::JUDGEMENT_IRQHandler()
{
	if (!CRC_CHECK::Verify_CRC8_Check_Sum(m_uart->m_receive_date, 5)) return;
	uint16_t data_length = (uint16_t)m_uart->m_receive_date[1] | ((uint16_t)m_uart->m_receive_date[2] << 8);
	if (!CRC_CHECK::Verify_CRC16_Check_Sum(m_uart->m_receive_date, 9 + data_length)) return;
	uint16_t cmd_id = (uint16_t)m_uart->m_receive_date[5] | ((uint16_t)m_uart->m_receive_date[6] << 8);
	uint8_t* data = m_uart->m_receive_date + 7;
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
}

void JUDGEMENT::init(UART* uart)
{
	m_uart = uart;
	m_uart->p_use = this;
	void (JUDGEMENT:: * p)(void) = &JUDGEMENT::JUDGEMENT_IRQHandler;
	auto func = reinterpret_cast<void(**)(void(*))>(&p);
	m_uart->UART_IRQHandler = *func;
}

void JUDGEMENT::draw_line(int16_t begin_x, int16_t begin_y, int16_t end_x, int16_t end_y)
{
}

void JUDGEMENT::draw_rectangle(int16_t begin_x, int16_t begin_y, int16_t end_x, int16_t end_y)
{
}

void JUDGEMENT::draw_circle(int16_t r, int16_t center_x, int16_t center_y)
{
}

void JUDGEMENT::draw_ellipse(int16_t a, int16_t b, int16_t center_x, int16_t center_y)
{
}

void JUDGEMENT::draw_arc()
{
}

void JUDGEMENT::draw_double(int16_t decimal_digits, int16_t x, int16_t y, float data)
{
}

void JUDGEMENT::draw_int(int16_t x, int16_t y, int32_t data)
{
}

void JUDGEMENT::draw_char(int16_t x, int16_t y, uint8_t* data, int16_t length)
{
}

void JUDGEMENT::set_line_width()
{
}

void JUDGEMENT::set_color()
{
}

void JUDGEMENT::set_text_style()
{
}

void JUDGEMENT::set_layer(int8_t layer)
{
}

void JUDGEMENT::clear_layer(int8_t layer)
{
}

JUDGEMENT::JUDGEMENT()
{
	m_layer = (uint8_t**)malloc(sizeof(uint8_t*) * 10);
	for (int8_t i = 0; i < 10; i++)
	{
		m_layer[i] = (uint8_t*)malloc(sizeof(uint8_t) * 15);
	}
}
