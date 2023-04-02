#include "CHASSIS.h"

void CHASSIS::setSpeed(int32_t x, int32_t y, int32_t z)
{
	m_setSpeedX = x;
	m_setSpeedY = -y;
	m_setSpeedZ = -z;
}

void CHASSIS::changeSpeed(int32_t x, int32_t y, int32_t z)
{
	m_setSpeedX += x;
	m_setSpeedY += y;
	m_setSpeedZ += z;
}

void CHASSIS::upDate()
{
	
	m_motor[LEFT_FRONT]->setSpeed(-1.0 * (-m_setSpeedX + m_setSpeedY + m_setSpeedZ));
	m_motor[RIGHT_FRONT]->setSpeed(+m_setSpeedX + m_setSpeedY - m_setSpeedZ);
	m_motor[RIGHT_BEHIND]->setSpeed(-m_setSpeedX + m_setSpeedY - m_setSpeedZ);
	m_motor[LEFT_BEHIND]->setSpeed(-1.0 * (+m_setSpeedX + m_setSpeedY + m_setSpeedZ));

	for (int i = 0; i <= max_id; i++)
	{
		if(m_motor[i])
		m_motor[i]->upData();
	}
}
CHASSIS::CHASSIS(std::vector<std::pair<MOTOR*, CHASSIS_MOTOR_POSETION>>motor) :m_motorNumber(motor.size())
{
	int num = 0;
	for (auto i : motor)
	{
		max_id = max_id > i.second ? max_id : i.second;
	}
	num = max_id + 1;
	m_motor = (MOTOR**)malloc(sizeof(MOTOR*) * num);
	memset(m_motor, 0, sizeof(MOTOR*) * num);
	for (auto i : motor)
	{
		m_motor[i.second] = i.first;
	}
}

CHASSIS::~CHASSIS()
{
	free(m_motor);
}

