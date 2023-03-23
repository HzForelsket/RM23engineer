#include "VIEW.h"

void VIEW::setPose(int16_t yaw, int16_t pitch)
{
}

void VIEW::changePose(int16_t yaw, int16_t pitch)
{
}

void VIEW::upDate()
{
	for (int i = 0; i < m_motorNumber; i++)
	{
		m_motor[i].upData();
	}
}

VIEW::VIEW(MOTOR* motor, uint8_t number):m_motor(motor),m_motorNumber(number)
{

}
