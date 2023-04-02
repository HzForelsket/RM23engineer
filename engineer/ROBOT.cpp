#include "ROBOT.h"
/*
* WASD 最速底盘前后左右
* QE 最速底盘左旋右旋
* G单击开启负压，再次点击关闭
*
* CTRL+WASD 基于当前速度增速底盘前后左右
* CTRL+QR 基于当前速度增速底盘左旋右旋
* Z 自动伸展空接一
*
* 最速鼠标左键推出，右键收入
* 最速鼠标滚轮抬升下降
* RF 最速抬升降低矿石架
* XC 最速顺逆旋矿石
* 
* SHIFT+鼠标左键推出，右键 基于当前速度增速鼠标左键推出，右键收入
* SHIFT+鼠标滚轮 基于当前速度增速鼠标滚轮 抬升下降
* SHIFT+RF 基于当前速度增速抬升降低矿石架
* SHIFT+XC 基于当前速度增速顺逆旋矿石
* 
* 
* 鼠标x,y 视野左右上下
* SHIFT+鼠标x,y 爪子roll，pitch
*
* CTRL+Z所有电机释力
*/
void ROBOT::upDate()
{
	if (m_rc->left_rod == RC::ROD_POSITION::MID)
	{
		switch (m_rc->right_rod)
		{
		case RC::ROD_POSITION::DOWN:
		{
			m_chassis->setSpeed(m_rc->right_horizontal, m_rc->right_vertical, m_rc->left_horizontal);
		}
			break;
		case RC::ROD_POSITION::MID:
		{
			m_claw->changClawPose(m_rc->right_vertical, m_rc->left_vertical, m_rc->left_horizontal, m_rc->right_horizontal);
		}
			break;
		case RC::ROD_POSITION::UP:
		{
			m_claw->changeMinePose(m_rc->right_horizontal, m_rc->left_vertical);
		}
			break;
		default:
			break;
		}
	}
	else if (m_rc->left_rod == RC::ROD_POSITION::DOWN)
	{
		switch (m_rc->right_rod)
		{
		case RC::ROD_POSITION::DOWN:
			break;
		case RC::ROD_POSITION::MID:
			break;
		case RC::ROD_POSITION::UP:
			break;
		default:
			break;
		}
	}
	else if (m_rc->left_rod == RC::ROD_POSITION::UP)
	{
		switch (m_rc->right_rod)
		{
		case RC::ROD_POSITION::DOWN:
			break;
		case RC::ROD_POSITION::MID:
			break;
		case RC::ROD_POSITION::UP://PC controller
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
				int16_t x = CHASSIS_MAX_SPEED, y = CHASSIS_MAX_SPEED, z = CHASSIS_MAX_SPEED;
				y *= m_rc->S * -1 + m_rc->W;
				x *= m_rc->A * -1 + m_rc->D;
				z *= m_rc->Q * -1 + m_rc->R;

				m_chassis->setSpeed(x, y, z);
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
					claw_push = MAX_PUSH_SPEED, claw_z = MAX_LIFT_SPEED;

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

			if (m_rc->G && !open_pump)
			{
				open_pump = true;
			}
			else if (m_rc->G && open_pump)
			{
				open_pump = false;
			}

			if (m_rc->Z)
			{

			}
		}
			break;
		default:
			break;
		}
	}
}

void ROBOT::init(RC* rc, CHASSIS* chassis, CLAW* claw,VIEW* view, JUDGEMENT* judgement)
{
	m_rc = rc;
	m_chassis = chassis;
	m_claw = claw;
	m_view = view;
	m_judgement = judgement;
}
