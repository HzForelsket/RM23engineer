#include "CLAW.h"
void CLAW::setClawPose(int32_t y, int32_t z, int32_t pitch, int32_t roll)
{
	m_set_y = y;
	m_set_z = z;
	m_set_pitch = pitch;
	m_set_roll = roll;
}
void CLAW::changClawPose(int32_t y, int32_t z, int32_t pitch, int32_t roll)
{
	m_set_y += y;
	m_set_z += z;
	m_set_pitch += pitch;
	m_set_roll += roll;
}
void CLAW::setMinePose(int32_t pitch, int32_t lift)
{
	m_set_mine_lift = lift;
	m_set_mine_pitch = pitch;
}
void CLAW::changeMinePose(int32_t pitch, int32_t lift)
{
	m_set_mine_lift += lift;
	m_set_mine_pitch += pitch;
}
void CLAW::setSwitch(bool status)
{
	m_status = status;

}
void CLAW::upDate()
{
	
	if (m_set_z <= m_max_first_lift_angle&& m_set_z >=0)
	{
		m_motor[FIRST_LIFT_MOTOT_RIGHT]->changeAngle(-(m_set_z - m_z));
		m_motor[FIRST_LIFT_MOTOT_LEFT]->changeAngle(-(m_set_z - m_z));
		m_z = m_set_z;
	}
	else if(m_set_z >= m_max_first_lift_angle&& m_set_z <=m_max_second_lift_angle)
	{
		m_motor[SECOND_LIFT_MOTOT_LEFT]->changeAngle(m_set_z - m_z);
		m_motor[SECOND_LIFT_MOTOT_RIGHT]->changeAngle(m_set_z - m_z);
		m_z = m_set_z;
	}

	if (m_set_y <= m_max_push_angle && m_set_y >= 0)
	{
		m_motor[PUSH_MOTOR_LEFT]->changeAngle(-(m_set_y - m_y));
		m_motor[PUSH_MOTOR_RIGHT]->changeAngle(m_set_y - m_y);
		m_y = m_set_y;
	}

	/*
	if (m_roll <= m_max_roll_angle && m_roll >= m_min_roll_angle)
	{
		m_motor[ROLL_MOTOR]->changeAngle(m_set_roll - m_roll);
		m_roll = m_set_roll;
	}
	if (m_pitch <= m_max_pitch_angle && m_pitch >= m_min_pitch_angle)
	{
		m_motor[PITCH_MOTOR]->changeAngle(m_set_pitch - m_pitch);
		m_pitch = m_set_pitch;
	}
	if (m_mine_lift <= m_max_mine_lift_angle && m_mine_lift >= 0)
	{
		m_motor[MINE_LIFT_MOTOR]->changeAngle(m_set_mine_lift - m_mine_lift);
		m_mine_lift = m_set_mine_lift;
	}
	m_motor[MINE_PITCH_MOTOR_ONE]->changeAngle(m_set_mine_pitch - m_mine_pitch);
	m_motor[MINE_PITCH_MOTOR_TWO]->changeAngle(m_set_mine_pitch - m_mine_pitch);
	*/
	for (int i = 0; i < m_motorNumbers; i++)
	{
		m_motor[i]->upData();
	}
}
void CLAW::reset()
{

}
CLAW::CLAW(std::vector<std::pair<MOTOR*, CLAW_MOTOR_POSITION>>motor):m_motorNumbers(motor.size())
{
	m_motor = (MOTOR**)malloc(sizeof(MOTOR*) * m_motorNumbers);
	memset(m_motor, 0, sizeof(MOTOR*) * m_motorNumbers);
	for (auto i : motor)
	{
		m_motor[i.second] = i.first;
	}
};
