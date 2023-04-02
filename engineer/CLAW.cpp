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
CLAW::~CLAW()
{
	free(m_motor);
}
void CLAW::setSwitch(bool status)
{
	m_status = status;

}
void CLAW::upDate()
{
	int32_t now_first_angle = 0, now_second_angle = 0;

	if (m_z <= m_max_first_lift_angle&&m_z>=0)
	{
		now_second_angle = 0;
		now_first_angle = m_z;
	}
	else if (m_z > m_max_first_lift_angle && m_z <= m_max_second_lift_angle)
	{
		now_first_angle = m_max_first_lift_angle;
		now_second_angle = m_z - now_first_angle;
	}
	if (m_set_z <= 0)
	{
		m_motor[SECOND_LIFT_MOTOT_LEFT]->changeAngle(0 - now_second_angle);
		m_motor[SECOND_LIFT_MOTOT_RIGHT]->changeAngle(0 - now_second_angle);
		m_motor[FIRST_LIFT_MOTOT_RIGHT]->changeAngle(-(0 - now_first_angle));
		m_motor[FIRST_LIFT_MOTOT_LEFT]->changeAngle(-(0 - now_first_angle));
		m_set_z = m_z = 0;
	}
	else if (m_set_z < m_max_first_lift_angle&& m_set_z >0)
	{
		m_motor[FIRST_LIFT_MOTOT_RIGHT]->changeAngle(-(m_set_z - now_first_angle));
		m_motor[FIRST_LIFT_MOTOT_LEFT]->changeAngle(-(m_set_z - now_first_angle));
		m_motor[SECOND_LIFT_MOTOT_LEFT]->changeAngle(0- now_second_angle);
		m_motor[SECOND_LIFT_MOTOT_RIGHT]->changeAngle(0- now_second_angle);
		m_z = m_set_z;
	}
	else if(m_set_z >= m_max_first_lift_angle&& m_set_z <m_max_second_lift_angle)
	{
		m_motor[FIRST_LIFT_MOTOT_RIGHT]->changeAngle(-(m_max_first_lift_angle - now_first_angle));
		m_motor[FIRST_LIFT_MOTOT_LEFT]->changeAngle(-(m_max_first_lift_angle - now_first_angle));
		m_motor[SECOND_LIFT_MOTOT_LEFT]->changeAngle(m_set_z - m_max_first_lift_angle - now_second_angle);
		m_motor[SECOND_LIFT_MOTOT_RIGHT]->changeAngle(m_set_z - m_max_first_lift_angle - now_second_angle);
		m_z = m_set_z;
	}
	else if (m_set_z >= m_max_second_lift_angle)
	{
		m_motor[FIRST_LIFT_MOTOT_RIGHT]->changeAngle(-(m_max_first_lift_angle - now_first_angle));
		m_motor[FIRST_LIFT_MOTOT_LEFT]->changeAngle(-(m_max_first_lift_angle - now_first_angle));
		m_motor[SECOND_LIFT_MOTOT_LEFT]->changeAngle(m_max_second_lift_angle- m_max_first_lift_angle - now_second_angle);
		m_motor[SECOND_LIFT_MOTOT_RIGHT]->changeAngle(m_max_second_lift_angle- m_max_first_lift_angle - now_second_angle);
		m_set_z = m_z = m_max_second_lift_angle;
	}

	if (m_set_y < m_max_push_angle && m_set_y > 0)
	{
		m_motor[PUSH_MOTOR_LEFT]->changeAngle(m_set_y - m_y);
		m_motor[PUSH_MOTOR_RIGHT]->changeAngle(-(m_set_y - m_y));
		m_y = m_set_y;
	}
	else if (m_set_y <= 0)
	{
		m_motor[PUSH_MOTOR_LEFT]->changeAngle(0 - m_y);
		m_motor[PUSH_MOTOR_RIGHT]->changeAngle(-(0 - m_y));
		m_set_y=m_y = 0;
	}
	else if(m_set_y >= m_max_push_angle)
	{
		m_motor[PUSH_MOTOR_LEFT]->changeAngle(m_max_push_angle - m_y);
		m_motor[PUSH_MOTOR_RIGHT]->changeAngle(-(m_max_push_angle - m_y));
		m_set_y = m_y = m_max_push_angle;
	}

	
	if (m_set_roll < m_max_roll_angle && m_set_roll > m_min_roll_angle)
	{
		m_motor[ROLL_MOTOR]->changeAngle(m_set_roll - m_roll);
		m_roll = m_set_roll;
	}
	else if (m_set_roll <= m_min_roll_angle)
	{
		m_motor[ROLL_MOTOR]->changeAngle(m_min_roll_angle - m_roll);
		m_roll = m_set_roll = m_min_roll_angle;
	}
	else if (m_set_roll >= m_max_roll_angle)
	{
		m_motor[ROLL_MOTOR]->changeAngle(m_max_roll_angle - m_roll);
		m_roll = m_set_roll = m_max_roll_angle;
	}

	if (m_set_pitch < m_max_pitch_angle && m_set_pitch > m_min_pitch_angle)
	{
		m_motor[PITCH_MOTOR]->changeAngle(-(m_set_pitch - m_pitch));
		m_pitch = m_set_pitch;
	}
	else if (m_set_pitch >= m_max_pitch_angle)
	{
		m_motor[PITCH_MOTOR]->changeAngle(-(m_max_pitch_angle - m_pitch));
		m_pitch = m_set_pitch= m_max_pitch_angle;
	}
	else if (m_set_pitch <= m_min_pitch_angle)
	{
		m_motor[PITCH_MOTOR]->changeAngle(-(m_min_pitch_angle - m_pitch));
		m_pitch = m_set_pitch= m_min_pitch_angle;
	}
	if (m_set_mine_lift <= m_max_mine_lift_angle && m_set_mine_lift >= 0)
	{
		m_motor[MINE_LIFT_MOTOR_LEFT]->changeAngle(-(m_set_mine_lift - m_mine_lift));
		m_motor[MINE_LIFT_MOTOR_RIGHT]->changeAngle(-(m_set_mine_lift - m_mine_lift));
		m_mine_lift = m_set_mine_lift;
	}
	/*m_motor[MINE_PITCH_MOTOR_ONE]->changeAngle(m_set_mine_pitch - m_mine_pitch);
	m_motor[MINE_PITCH_MOTOR_TWO]->changeAngle(m_set_mine_pitch - m_mine_pitch);
	*/
	for (int i = 0; i <= max_id; i++)
	{
		if(m_motor[i])
		m_motor[i]->upData();
	}
}
void CLAW::reset()
{

}
CLAW::CLAW(std::vector<std::pair<MOTOR*, CLAW_MOTOR_POSITION>>motor):m_motorNumbers(motor.size())
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
};
