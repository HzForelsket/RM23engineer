#include "init.h"
#include"CLAW.h"
CAN can1, can2;
TIMER task;
UART uart1, uart2, uart3, uart4, uart5, uart6;
MOTOR_3508 motor[8] = {
	{{ 0.1,0.05,0,10,-10 },{ 10,0.0665,0 }, MOTOR_3508::ID::ID2, &can1},
	{{ 0.1,0.05,0,10,-10 },{ 10,0.0665,0 }, MOTOR_3508::ID::ID1, &can1},
	{{ 0.1,0.05,0,10,-10 },{ 10,0.0665,0 }, MOTOR_3508::ID::ID3, &can1},
	{{ 0.1,0.05,0,10,-10 },{ 10,0.0665,0 }, MOTOR_3508::ID::ID4, &can1},
	{{ 0.1,0.05,0,10,-10 },{ 10,0.0665,0 }, MOTOR_3508::ID::ID5, &can1},
	{{ 0.1,0.05,0,10,-10 },{ 10,0.0665,0 }, MOTOR_3508::ID::ID6, &can1},
	{{ 0,0,0 },{ 0,0,0 }, MOTOR_3508::ID::ID7, &can1},
	{{ 0,0,0 },{ 0,0,0 }, MOTOR_3508::ID::ID8, &can1}
};

CLAW claw({
	{motor+0 ,CLAW::PUSH_MOTOR_RIGHT},
	{motor+1 ,CLAW:: PUSH_MOTOR_LEFT},
	{motor + 2 ,CLAW::FIRST_LIFT_MOTOT_LEFT},
	{motor + 3 ,CLAW::FIRST_LIFT_MOTOT_RIGHT},
	{motor + 4 ,CLAW::SECOND_LIFT_MOTOT_LEFT},
	{motor + 5 ,CLAW::SECOND_LIFT_MOTOT_RIGHT}
	});

void taskFunction()
{
	static uint32_t js = 0;
	js++;
	claw.upDate();
	can1.transmit_data();
}
void init()
{
	GPIO rx1, tx1, rx2, tx2;
	rx2.init(GPIOB, GPIO_Pin_12, GPIO_Mode_AF, GPIO_OType_PP, GPIO_PuPd_NOPULL);
	tx2.init(GPIOB, GPIO_Pin_13, GPIO_Mode_AF, GPIO_OType_PP, GPIO_PuPd_NOPULL);
	can2.init(rx2, tx2, CAN2);
	rx1.init(GPIOA, GPIO_Pin_11, GPIO_Mode_AF, GPIO_OType_PP, GPIO_PuPd_NOPULL);
	tx1.init(GPIOA, GPIO_Pin_12, GPIO_Mode_AF, GPIO_OType_PP, GPIO_PuPd_NOPULL);
	can1.init(rx1, tx1, CAN1).open_receive_interrput();
	
	task.initBase(TIMER::BASE, TIM1, 800,true);
	task.m_TIMEx_IRQHandler = taskFunction;
	

}
