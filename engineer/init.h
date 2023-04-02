#ifndef __INIT__
#define __INIT__
#include"GPIO.h"
#include"MOTOR_3508.h"
#include"CAN.h"
#include"UART.h"
#include"CLAW.h"
#include"CHASSIS.h"
#include"UART.h"
#include"RC.h"
#include"ROBOT.h"
#include"JUDGEMENT.h"
#include"GRAPH.h"
void taskFunction();
void errorDetectFunction();
void init();
#endif // !__INIT__
