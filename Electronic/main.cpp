#include"init.h"
//8Mhz
TIMER task, task2;
TIMER pwm_left, pwm_right;
ENCODER encoder_left, encoder_right;
PID pid_left{ 0,0,0 }, pid_right{ 0,0,0 };
DISTANCE_DETECTOR distance;
TCRT tcrt;
BLUETOOTH bluetooth;

double speed = 0.3;
double speed_left, speed_right;
double set_speed_left = 0.3, set_speed_right = 0.3;
double keep_distance = 20;
double max_speed = speed + 0.2, min_speed = speed - 0.2;

void taskFunction()//巡线，距离判断
{
	static uint32_t js = 0;
	js++;
	tcrt.upDate();

	if (tcrt.left_status)
	{
		set_speed_right = max_speed;
		set_speed_left = speed;
	}
	else if(tcrt.right_status)
	{
		set_speed_right = speed;
		set_speed_left = max_speed;
	}
	else if (tcrt.left_most_status)
	{
		set_speed_right = max_speed;
		set_speed_left = speed;
	}
	else if (tcrt.right_most_status)
	{
		set_speed_right = speed;
		set_speed_left = max_speed;
	}
	else if(tcrt.mid_status)
	{
		set_speed_right = speed;
		set_speed_left = speed;
	}
	

	if (keep_distance > distance.m_distance)
	{
		if (set_speed_left * 1.1 < max_speed && set_speed_right * 1.1 < max_speed)
		{
			set_speed_left *= 1.1;
			set_speed_right *= 1.1;
		}
	}
	else if (keep_distance < distance.m_distance)
	{
		if (set_speed_left * 0.9 > min_speed && set_speed_right * 0.9 > min_speed)
		{
			set_speed_left *= 0.9;
			set_speed_right *= 0.9;
		}
	}


	if (tcrt.stop)
	{
		set_speed_left = set_speed_right = 0;
	}
}
void task2Function()//速度更新
{
	static uint32_t js2 = 0;
	js2++;

	encoder_left.upDate();
	encoder_right.upDate();

	speed_left = encoder_left.delta() * 1000.0;
	speed_right = encoder_right.delta() * 1000.0;

	static double set_duty_left, set_duty_right;
	/*set_duty_left = pid_left.Delta(set_speed_left - speed_left);
	set_duty_right = pid_left.Delta(set_speed_right - speed_right);*/

	pwm_left.setPwmDuty(TIM_Channel_2,set_duty_left);
	pwm_right.setPwmDuty(TIM_Channel_1,set_duty_right);

}
int main()
{
	init();
	GPIO speed_3, speed_5, speed_10, begin;
	speed_3.init(GPIOA, GPIO_Pin_0, GPIO_Mode_IN, GPIO_OType_PP, GPIO_PuPd_UP);
	speed_5.init(GPIOA, GPIO_Pin_1, GPIO_Mode_IN, GPIO_OType_PP, GPIO_PuPd_UP);
	speed_10.init(GPIOA, GPIO_Pin_2, GPIO_Mode_IN, GPIO_OType_PP, GPIO_PuPd_UP);
	begin.init(GPIOA, GPIO_Pin_3, GPIO_Mode_IN, GPIO_OType_PP, GPIO_PuPd_UP);

	/*while (GPIO_ReadInputDataBit(begin.get_m_GPIOx(),begin.getPin()))
	{
		if (GPIO_ReadInputDataBit(speed_3.get_m_GPIOx(), speed_3.getPin()))
		{
			speed = 0.3;
		}
		else if(GPIO_ReadInputDataBit(speed_5.get_m_GPIOx(), speed_5.getPin()))
		{
			speed = 0.5;
		}
		else if (GPIO_ReadInputDataBit(speed_10.get_m_GPIOx(), speed_10.getPin()))
		{
			speed = 1.0;
		}
	}
	uint8_t data[10] = { 1,1,1,1,1,1,1,1,1,1 };
	bluetooth.transmit(data, 10);*/
	GPIO PB15, PF6;

	PB15.init(GPIOB, GPIO_Pin_15, GPIO_Mode_AF);

	pwm_left.initBase(TIMER::PWM, TIM12, 0.5).pwmInit(0, &PB15, TIM_Channel_2);

	PF6.init(GPIOF, GPIO_Pin_6, GPIO_Mode_AF);
	pwm_right.initBase(TIMER::PWM, TIM10, 0.5).pwmInit(0, &PF6, TIM_Channel_1);
	while (true)
	{
		static uint8_t pb15, pf6;
		pb15 = GPIO_ReadInputDataBit(PB15.get_m_GPIOx(), PB15.getPin());
		pf6 = GPIO_ReadInputDataBit(PF6.get_m_GPIOx(), PF6.getPin());
	}
}
