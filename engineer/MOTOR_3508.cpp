#include "MOTOR_3508.h"

void MOTOR_3508::setSpeed(int32_t speed)
{
	m_set_speed = setInRange<int32_t>( speed,MAX_SPEED,-MAX_SPEED);
}

void MOTOR_3508::setAngle(int32_t angle)
{
	m_change_angle = getAngleDelta<int16_t>(angle, getAngle(),0);
}

void MOTOR_3508::changeAngle(int32_t angle)
{
	m_change_angle += angle;
}

void MOTOR_3508::changeSpeed(int32_t speed)
{
	m_set_speed = getSpeed() + speed;
}

int MOTOR_3508::getAngle()
{
	return m_now_angle;
}

int MOTOR_3508::getSpeed()
{
	return m_now_speed;
}

void MOTOR_3508::upData()
{
	static uint32_t sum = 0;
	sum++;
	int16_t pre_angle, set_electricity;
	static int16_t test_change_angle;
	uint8_t* data = m_can->read_data((uint16_t)m_id)->second.m_receive_data;
	pre_angle = m_now_angle;
	m_now_angle = (((uint16_t)data[0]) << 8) | (uint16_t)data[1];
	m_now_speed = (((uint16_t)data[2]) << 8) | (uint16_t)data[3];
	m_now_electricity = (((uint16_t)data[4]) << 8) | (uint16_t)data[5];
	m_now_temperature = (uint8_t)data[6];
	uint8_t need_electricity[2] = { 0,0 };
	test_change_angle = getAngleDelta<int32_t>(m_now_angle, pre_angle, m_now_speed);
	if (m_change_angle)
	{
		m_change_angle -= getAngleDelta(m_now_angle,pre_angle,m_now_speed);
		setSpeed(m_pid_angle_to_speed.Position((int32_t)m_change_angle));
		if (!m_change_angle)setSpeed(0);
		else
		{
			//if(!getSpeed())
			//setSpeed(1);
		}
	}
	m_set_electricity += m_pid_speed_to_electricity.Delta((int32_t)m_set_speed - (int32_t)m_now_speed);
	m_set_electricity = setInRange<double>(m_set_electricity, MAX_ELECTRICITY, -MAX_ELECTRICITY);
	set_electricity = m_set_electricity;
	need_electricity[0] = set_electricity >> 8;
	need_electricity[1] = set_electricity & 0x00ff;

	if (m_id <= ID::ID4 && m_id >= ID::ID1)
	{
		m_can->set_transmit_data(need_electricity, 2, m_id - (int16_t)ID::ID1, 0x200);
	}
	else if (m_id > ID::ID4 && m_id <= ID::ID8)
	{
		m_can->set_transmit_data(need_electricity, 2, m_id - (int16_t)ID::ID5, 0x1ff);
	}
}

void MOTOR_3508::init(PID angle_to_speed, PID speed_to_electricity, ID id, CAN* can)
{
	m_can = can;
	m_id = id;
	memcpy(&m_pid_angle_to_speed, &angle_to_speed, sizeof(PID));
	memcpy(&m_pid_speed_to_electricity, &speed_to_electricity, sizeof(PID));
}

MOTOR_3508::MOTOR_3508(PID angle_to_speed, PID speed_to_electricity, ID id, CAN* can, int16_t angleMax, int16_t angleMin, int16_t electricityMax,int16_t speedMAX)
	:MAX_ANGLE(angleMax), MIN_ANGLE(angleMin), MAX_ELECTRICITY(electricityMax),MAX_SPEED(speedMAX)
{
	m_can = can;
	m_id = id;
	memcpy(&m_pid_angle_to_speed, &angle_to_speed, sizeof(PID));
	memcpy(&m_pid_speed_to_electricity, &speed_to_electricity, sizeof(PID));
}


