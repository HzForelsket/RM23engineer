#pragma once
#include"CLAW.h"
#include"CHASSIS.h"
#include"RC.h"
#include"VIEW.h"
#include"JUDGEMENT.h"
class ROBOT
{
	static const int32_t CHASSIS_MAX_SPEED = 2000;
	static const int32_t MAX_ROTATE_MINE_SPEED = 200;
	static const int32_t MAX_LIFT_MINE_SPEED = 200;
	static const int32_t MAX_PUSH_SPEED = 200;
	static const int32_t MAX_LIFT_SPEED = 200;
					
	static const int32_t CHASSIS_SPEED_SENSITIVITY = 1;
	static const int32_t ROTATE_MINE_SPEED_SENSITIVITY = 200;
	static const int32_t LIFT_MINE_SPEED_SENSITIVITY = 200;
	static const int32_t PUSH_SPEED_SENSITIVITY = 200;
	static const int32_t LIFT_SPEED_SENSITIVITY = 200;

	
public:
	void upDate();
	void init(RC* rc, CHASSIS* chassis, CLAW* claw,VIEW* view,JUDGEMENT* judgement);
	RC* m_rc = nullptr;
	JUDGEMENT* m_judgement = nullptr;
	CHASSIS* m_chassis = nullptr;
	CLAW* m_claw = nullptr;
	VIEW* m_view = nullptr;
	bool open_pump = false;
};

