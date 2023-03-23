#include "CONTROL.h"
/*
* WASD ���ٵ���ǰ������
* QE ���ٵ�����������
* G����������ѹ���ٴε���ر�
*
* CTRL+WASD ���ڵ�ǰ�ٶ����ٵ���ǰ������
* CTRL+QR ���ڵ�ǰ�ٶ����ٵ�����������
* Z �Զ���չ�ս�һ
*
* �����������Ƴ����Ҽ�����
* ����������̧���½�
* RF ����̧�����Ϳ�ʯ��
* XC ����˳������ʯ
* 
* SHIFT+�������Ƴ����Ҽ� ���ڵ�ǰ�ٶ������������Ƴ����Ҽ�����
* SHIFT+������ ���ڵ�ǰ�ٶ����������� ̧���½�
* SHIFT+RF ���ڵ�ǰ�ٶ�����̧�����Ϳ�ʯ��
* SHIFT+XC ���ڵ�ǰ�ٶ�����˳������ʯ
* 
* 
* ���x,y ��Ұ��������
* SHIFT+���x,y צ��roll��pitch
*
* CTRL+Z���е������
*/
void CONTROL::upDate()
{
	if (m_rc->CTRL && m_rc->Z)
	{
		m_claw->reset();
		return;
	}


	if (m_rc->CTRL)
	{
		int16_t xChange = 0, yChange = 0, zChange = 0;
		yChange = (m_rc->S * -1 + m_rc->W) * CHASSIS_SPEED_SENSITIVITY;
		xChange = (m_rc->A * -1 + m_rc->D) * CHASSIS_SPEED_SENSITIVITY;
		zChange = (m_rc->Q * -1 + m_rc->R) * CHASSIS_SPEED_SENSITIVITY;
		m_chassis->changeSpeed(xChange, yChange, zChange);
	}
	else
	{
		int16_t x = CHASSIS_MAX_SPEED, y = CHASSIS_MAX_SPEED, z= CHASSIS_MAX_SPEED;
		y *= m_rc->S * -1 + m_rc->W;
		x *= m_rc->A * -1 + m_rc->D;
		z *= m_rc->Q * -1 + m_rc->R;

		m_chassis->setSpeed(x, y, z);
	}

	if (m_rc->m_mouse.left)
	{

	}
	else
	{

	}

	if (m_rc->m_mouse.right)
	{

	}
	else
	{

	}

	if (m_rc->SHIFT)
	{
		int32_t claw_roll = 0, claw_pitch = 0,
			mine_z = LIFT_MINE_SPEED_SENSITIVITY, mine_pitch = ROTATE_MINE_SPEED_SENSITIVITY,
			claw_push = PUSH_SPEED_SENSITIVITY, claw_z = LIFT_SPEED_SENSITIVITY;

		claw_roll = m_rc->m_mouse.x;
		claw_pitch = m_rc->m_mouse.y;

		claw_push *= m_rc->m_mouse.left * -1 + m_rc->m_mouse.right;
		claw_z *= m_rc->m_mouse.z > 0 ? 0 : -1;

		mine_z *= m_rc->R * -1 + m_rc->F;
		mine_pitch *= m_rc->X * -1 + m_rc->C;

		m_claw->changeMinePose(mine_pitch, mine_z);
		m_claw->changClawPose(claw_push, claw_z, claw_pitch, claw_roll);
	}
	else
	{
		int32_t view_yaw = 0, view_pitch = 0, 
			mine_z = MAX_LIFT_MINE_SPEED, mine_pitch = MAX_ROTATE_MINE_SPEED,
			claw_push=MAX_PUSH_SPEED,claw_z=MAX_LIFT_SPEED;

		view_yaw = m_rc->m_mouse.x;
		view_pitch = m_rc->m_mouse.y;

		claw_push *= m_rc->m_mouse.left * -1 + m_rc->m_mouse.right;
		claw_z *= m_rc->m_mouse.z > 0 ? 0 : -1;

		mine_z *= m_rc->R * -1 + m_rc->F;
		mine_pitch *= m_rc->X * -1 + m_rc->C;

		m_view->changePose(view_yaw, view_pitch);
		m_claw->changeMinePose(mine_pitch, mine_z);
		m_claw->changClawPose(claw_push, claw_z, 0, 0);
	}

	if (m_rc->G&&!open_pump)
	{
		open_pump = true;
	}
	else if(m_rc->G && open_pump)
	{
		open_pump = false;
	}

}

void CONTROL::init(RC* rc, CHASSIS* chassis, CLAW* claw,VIEW* view)
{
	m_rc = rc;
	m_chassis = chassis;
	m_claw = claw;
	m_view = view;
}
