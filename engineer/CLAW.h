#pragma once
#include"MOTOR_3508.h"
#include"MOTOR_2006.h"
#include<vector>
class CLAW
{
public:
	enum CLAW_MOTOR_POSITION
	{
		FIRST_LIFT_MOTOT_LEFT=3, SECOND_LIFT_MOTOT_LEFT=4, FIRST_LIFT_MOTOT_RIGHT=2, SECOND_LIFT_MOTOT_RIGHT=5, PUSH_MOTOR_LEFT=1, PUSH_MOTOR_RIGHT=0,
		PITCH_MOTOR, MINE_PITCH_MOTOR_ONE, MINE_PITCH_MOTOR_TWO,ROLL_MOTOR,MINE_LIFT_MOTOR
	};
private:
	MOTOR ** m_motor=nullptr;
	const uint8_t m_motorNumbers;
	bool m_status = false;
	int32_t m_z = 0, m_y = 0, m_pitch = 0, m_roll = 0, m_set_z = 0, m_set_y = 0, m_set_pitch = 0, //”“«∞…œ,xyz’˝
		m_set_roll = 0;
	int32_t m_mine_pitch = 0, m_set_mine_lift = 0, m_set_mine_pitch = 0, m_mine_lift = 0;
	int32_t m_max_first_lift_angle = 450000, m_max_second_lift_angle = m_max_first_lift_angle+260000, m_max_push_angle = 820000, m_max_pitch_angle = 0, m_min_pitch_angle = 0,
		m_max_roll_angle = 0, m_min_roll_angle = 0,m_max_mine_lift_angle=0;
public:
	void setClawPose(int32_t y, int32_t z, int32_t pitch, int32_t roll);
	void changClawPose(int32_t y, int32_t z, int32_t pitch, int32_t roll);
	void setMinePose(int32_t pitch, int32_t lift);
	void changeMinePose(int32_t pitch, int32_t lift);
	void setSwitch(bool status);
	void upDate();
	void reset();
	CLAW(std::vector<std::pair<MOTOR*,CLAW_MOTOR_POSITION>>motor);

};

