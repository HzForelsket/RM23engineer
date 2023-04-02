#pragma once
#include"MOTOR_3508.h"
#include<vector>
class CHASSIS
{
public:
	enum CHASSIS_MOTOR_POSETION
	{
		NONE=-1,LEFT_FRONT,LEFT_BEHIND,RIGHT_FRONT,RIGHT_BEHIND
	};
private:
	CHASSIS_MOTOR_POSETION max_id = NONE;
	int32_t m_setSpeedX = 0, m_setSpeedY = 0, m_setSpeedZ = 0;
	MOTOR**  m_motor=nullptr;
	const uint8_t m_motorNumber = 0;
public:
	void setSpeed(int32_t x,int32_t y,int32_t z);
	void changeSpeed(int32_t x, int32_t y, int32_t z);
	void upDate();
	CHASSIS(std::vector<std::pair<MOTOR*, CHASSIS_MOTOR_POSETION>>motor);
	~CHASSIS();
};

