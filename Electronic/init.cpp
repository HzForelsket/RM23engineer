#include "init.h"
extern TIMER task , task2;
extern TIMER pwm_left, pwm_right;
extern ENCODER encoder_left, encoder_right;
extern BLUETOOTH bluetooth;
UART bluetooth_uart;
void init()
{
	
	
	GPIO gpio1, gpio2;

	//BLUETOOTH
	{
		gpio1.init(GPIOA, GPIO_Pin_10, GPIO_Mode_AF, GPIO_OType_PP, GPIO_PuPd_UP);
		gpio2.init(GPIOA, GPIO_Pin_9, GPIO_Mode_AF, GPIO_OType_PP, GPIO_PuPd_UP);
		bluetooth_uart.init(USART1, 115200, { gpio1,gpio2 }, 20, false);
		bluetooth.init(&bluetooth_uart);
	}

	

	gpio1.init(GPIOA, GPIO_Pin_7, GPIO_Mode_AF, GPIO_OType_OD, GPIO_PuPd_UP);
	gpio2.init(GPIOA, GPIO_Pin_6, GPIO_Mode_AF, GPIO_OType_OD, GPIO_PuPd_UP);
	encoder_left.init(TIM3, { gpio1,gpio2 }, { TIM_Channel_2,TIM_Channel_1 });

	gpio1.init(GPIOC, GPIO_Pin_7, GPIO_Mode_AF, GPIO_OType_OD, GPIO_PuPd_UP);
	gpio2.init(GPIOC, GPIO_Pin_6, GPIO_Mode_AF, GPIO_OType_OD, GPIO_PuPd_UP);
	encoder_right.init(TIM8, { gpio1,gpio2 }, { TIM_Channel_2,TIM_Channel_1 });

	task.initBase(TIMER::BASE, TIM1, 1, true);
	task.m_TIMEx_IRQHandler = taskFunction;


	task2.initBase(TIMER::BASE, TIM2, 1000, true);
	task2.m_TIMEx_IRQHandler = task2Function;
}
