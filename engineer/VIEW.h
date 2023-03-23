#pragma once
#include"MOTOR_3508.h"
#include"MOTOR_2006.h"
class VIEW
{
	MOTOR* const m_motor = nullptr;
	const uint8_t m_motorNumber=0;
public:
	void setPose(int16_t yaw, int16_t pitch);
	void changePose(int16_t yaw, int16_t pitch);
	void upDate();
	VIEW(MOTOR* motor, uint8_t number);
};

