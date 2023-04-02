#include"init.h"
#include"CRC_CHECK.h"
extern ROBOT robot;
extern CLAW claw;
extern CHASSIS chassis;
extern	CAN can1, can2;
extern UART uart3;
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
	
}
void errorDetectFunction()
{
	//SELF_CHECK::run_detect(node_list);
	//static uint16_t line_test[4];
	//test_graph.draw_line(line_test[0], line_test[1], line_test[2], line_test[3]);
	//static uint16_t test_size;
	//test_size = sizeof(graphic_data_struct_t);
	//memcpy(test_data + 13, &test_graph.m_graphic_data_struct_t, sizeof(graphic_data_struct_t));
	//CRC_CHECK::Append_CRC8_Check_Sum(test_data, 5);
	//CRC_CHECK::Append_CRC16_Check_Sum(test_data, 30);

	////test_data[36] = '\n';
	//uart3.set_transmit_data(test_data, 30);
	//uart3.transmit_data();
}
int main()
{
	init();
	while (true)
	{

	}
}
