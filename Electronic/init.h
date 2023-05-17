#ifndef __INIT__
#define __INIT__
#include"GPIO.h"
#include"ENCODER.h"
#include"PID.h"
#include"BLUETOOTH.h"
class TCRT
{
public:
	GPIO left_most, left, mid, right, right_most;
	uint8_t  left_most_status, left_status, mid_status, right_status, right_most_status;
	uint8_t  pre_left_most_status, pre_left_status, pre_mid_status, pre_right_status, pre_right_most_status;
	uint8_t stop,begin_stop;
	TCRT()
	{

	}
	TCRT(const GPIO& left_most, const GPIO& left, const GPIO& mid, const GPIO& right,const GPIO& right_most)
	{
		this->left_most = left_most;
		this->left = left;
		this->mid = mid;
		this->right = right;
		this->right_most = right_most;
	}
	void upDate()
	{
		pre_left_most_status	= left_most_status		;
		pre_left_status			= left_status			;	
		pre_mid_status			= mid_status			;	
		pre_right_status		= right_status			;
		pre_right_most_status	= right_most_status		;

		left_most_status		= GPIO_ReadInputDataBit(left_most.get_m_GPIOx(), left_most.getPin());
		left_status				= GPIO_ReadInputDataBit(left.get_m_GPIOx(), left.getPin());
		mid_status				= GPIO_ReadInputDataBit(mid.get_m_GPIOx(), mid.getPin());
		right_status			= GPIO_ReadInputDataBit(right.get_m_GPIOx(), right.getPin());
		right_most_status		= GPIO_ReadInputDataBit(right_most.get_m_GPIOx(), right_most.getPin());
		
		if (left_most_status + left_status + mid_status + right_status + right_most_status>=3)
		{
			if (begin_stop >= 1)
			{
				stop = 1;
			}
			begin_stop = 1;
		}
	}
private:

};
class DISTANCE_DETECTOR
{
public:
	double m_distance;
	DISTANCE_DETECTOR()
	{

	}

private:

};


void taskFunction();
void task2Function();
void init();
#endif // !__INIT__
