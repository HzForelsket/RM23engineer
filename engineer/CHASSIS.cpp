#include "CHASSIS.h"

void CHASSIS::setSpeed(int32_t x, int32_t y, int32_t z)
{
	m_setSpeedX = x;
	m_setSpeedY = y;
	m_setSpeedZ = z;
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
}
CHASSIS::CHASSIS(std::vector<std::pair<MOTOR*, CHASSIS_MOTOR_POSETION>>motor) :m_motorNumber(motor.size())
{
	m_motor = (MOTOR**)malloc(sizeof(MOTOR*) * m_motorNumber);
	memset(m_motor, 0, sizeof(MOTOR*) * m_motorNumber);
	for (auto i : motor)
	{
		m_motor[i.second] = i.first;
	}
}

