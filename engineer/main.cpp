#include"init.h"
#include"CRC_CHECK.h"
extern ROBOT robot;
//extern CLAW claw;
//extern CHASSIS chassis;
//extern	CAN can1, can2;
//extern UART judgement_uart3, judgement_uart5;
//SELF_CHECK test(0, 0, 0);
uint8_t test_data[37] = {0xA5,21,0x00,0x00,0x00,
						 0x01,0x03,
						 0x01,0x01,0x03,0x00,0x03,0x01};
void taskFunction()
{
	robot.upDate();
	claw.upDate();
	chassis.upDate();
	can1.transmit_data();
	can2.transmit_data();
	
//	robot.upDate();
//	claw.upDate();
//	chassis.upDate();
//	can1.transmit_data();
//	can2.transmit_data();
}
void errorDetectFunction()
{
	static uint32_t js = 0;
	js++;
	robot.m_judgement->init_UI();
	//robot.m_judgement->upDateUI();
}
int main()
{
	init();
	robot.m_judgement->create_UI();
	while (true)
	{

	}
}
