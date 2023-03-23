#ifndef __MOTOR__
#define __MOTOR__
#include<cstdint>
class MOTOR
{
public:
	virtual void upData()=0;
	virtual void setSpeed(int32_t speed) = 0;
	virtual void changeAngle(int32_t angle) = 0;
	virtual int getAngle() = 0;
	virtual int getSpeed() = 0;
};

#endif // !__MOTOR__


