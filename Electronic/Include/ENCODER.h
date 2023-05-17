#ifndef __ENCODER_H__
#define __ENCODER_H__

#include"TIMER.h"
#include"GPIO.h"
#include<vector>
#define ENCODER_GPIO_NUMBER 2
class ENCODER
{
	TIM_TypeDef* m_timex;
	uint32_t m_last_count, m_now_count;
	int32_t m_delta;
public:		
	ENCODER();
	ENCODER(TIM_TypeDef* timex,std:: vector<GPIO> gpio, std::vector< uint16_t> TIM_Channel_x);
	void init(TIM_TypeDef* timex, std::vector<GPIO> gpio, std::vector< uint16_t> TIM_Channel_x);
	void upDate();
	int32_t delta();
};
	
#endif
