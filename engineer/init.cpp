#include "init.h"
CAN can1, can2;
TIMER task , error_detect;
UART uart2,uart3,uart5;
RC rc;
JUDGEMENT judgement;
ROBOT robot;
MOTOR_3508 motor[11] = {
	{{ 0,0,0 },{ 10,0.0665,0 }, MOTOR_3508::ID::ID2, &can2},			//0
	{{ 0,0,0 },{ 10,0.0665,0 }, MOTOR_3508::ID::ID4, &can2},			//1
	{{ 0.1,0.05,0,10,-10 },{ 10,0.0665,0 }, MOTOR_3508::ID::ID1, &can2},//2
	{{ 0.1,0.05,0,10,-10 },{ 10,0.0665,0 }, MOTOR_3508::ID::ID3, &can2},//3
	{{ 0.1,0.05,0,10,-10 },{ 10,0.0665,0 }, MOTOR_3508::ID::ID6, &can2},//4
	{{ 0,0,0 },{ 10,0.0665,0 }, MOTOR_3508::ID::ID1, &can1},			//5
	{{ 0,0,0 },{ 10,0.0665,0 }, MOTOR_3508::ID::ID3, &can1},			//6
	{{ 0.1,0.05,0,10,-10 },{ 10,0.0665,0 }, MOTOR_3508::ID::ID2, &can1},//7
	{{ 0.1,0.05,0,10,-10 },{ 10,0.0665,0 }, MOTOR_3508::ID::ID5, &can1},//8
	{{ 0.1,0.05,0,10,-10 },{ 10,0.0665,0 }, MOTOR_3508::ID::ID4, &can1},//9
	{{ 0.1,0.05,0,10,-10 },{ 10,0.0665,0 }, MOTOR_3508::ID::ID7, &can2}	//10
	//{ { 0,0,0,10,-10 },{ 0,0,0 }, MOTOR_3508::ID::ID7,& can2}	//10

};
MOTOR_2006 motor_2006[3] = {
		{{ 0.1,0.05,0,10,-10 },{ 10,0.0665,0 }, MOTOR_2006::ID::ID7, &can1},
		//{{ 0,0,0,10,-10 },{ 0,0,0 }, MOTOR_2006::ID::ID7, &can1},

		{{ 0.1,0.05,0,10,-10 },{ 10,0.0665,0 }, MOTOR_2006::ID::ID6, &can1},
		{ { 0.1,0.05,0,10,-10 },{ 10,0.0665,0 }, MOTOR_2006::ID::ID5,& can2}

};
CLAW claw({
	{motor + 2 ,CLAW::PUSH_MOTOR_RIGHT},
	{motor + 7 ,CLAW::PUSH_MOTOR_LEFT},
	{motor + 9 ,CLAW::FIRST_LIFT_MOTOT_LEFT},
	{motor + 3 ,CLAW::FIRST_LIFT_MOTOT_RIGHT},
	{motor + 8 ,CLAW::SECOND_LIFT_MOTOT_LEFT},
	{motor + 4 ,CLAW::SECOND_LIFT_MOTOT_RIGHT},
	{motor + 10 ,CLAW::PITCH_MOTOR},
	{motor_2006 + 0 ,CLAW::ROLL_MOTOR},
	{motor_2006 + 1 ,CLAW::MINE_LIFT_MOTOR_LEFT},
	{motor_2006 + 2 ,CLAW::MINE_LIFT_MOTOR_RIGHT},

	});
CHASSIS chassis({
	{motor + 6 ,CHASSIS::LEFT_FRONT},
	{motor + 5 ,CHASSIS::LEFT_BEHIND},
	{motor + 1 ,CHASSIS::RIGHT_FRONT},
	{motor + 0 ,CHASSIS::RIGHT_BEHIND}
	});
void init()
{
	GPIO rx1, tx1, rx2, tx2;
	rx2.init(GPIOB, GPIO_Pin_12, GPIO_Mode_AF, GPIO_OType_PP, GPIO_PuPd_NOPULL);
	tx2.init(GPIOB, GPIO_Pin_13, GPIO_Mode_AF, GPIO_OType_PP, GPIO_PuPd_NOPULL);
	can2.init(rx2, tx2, CAN2).open_receive_interrput();
	rx1.init(GPIOA, GPIO_Pin_11, GPIO_Mode_AF, GPIO_OType_PP, GPIO_PuPd_NOPULL);
	tx1.init(GPIOA, GPIO_Pin_12, GPIO_Mode_AF, GPIO_OType_PP, GPIO_PuPd_NOPULL);
	can1.init(rx1, tx1, CAN1).open_receive_interrput();
	
	rx1.init(GPIOA, GPIO_Pin_2, GPIO_Mode_AF, GPIO_OType_PP, GPIO_PuPd_NOPULL);
	tx1.init(GPIOA, GPIO_Pin_3, GPIO_Mode_AF, GPIO_OType_PP, GPIO_PuPd_NOPULL);
	uart2.init(USART2, 100000, { rx1,tx1 }, 100, true);
	rc.init(&uart2);

	rx1.init(GPIOC, GPIO_Pin_10, GPIO_Mode_AF, GPIO_OType_PP, GPIO_PuPd_NOPULL);
	tx1.init(GPIOC, GPIO_Pin_11, GPIO_Mode_AF, GPIO_OType_PP, GPIO_PuPd_NOPULL);
	uart3.init(USART3, 115200, { rx1,tx1 }, 100, true);
	judgement.init(&uart3);

	rx1.init(GPIOD, GPIO_Pin_2, GPIO_Mode_AF, GPIO_OType_PP, GPIO_PuPd_NOPULL);
	tx1.init(GPIOC, GPIO_Pin_12, GPIO_Mode_AF, GPIO_OType_PP, GPIO_PuPd_NOPULL);
	uart5.init(UART5, 115200, { rx1,tx1 }, 100, true);

	robot.init(&rc, &chassis, &claw, nullptr);
	task.initBase(TIMER::BASE, TIM1, 500,true);
	task.m_TIMEx_IRQHandler = taskFunction;

	error_detect.initBase(TIMER::BASE, TIM2, 5, true);
	error_detect.m_TIMEx_IRQHandler = errorDetectFunction;
}
