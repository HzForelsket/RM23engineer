#pragma once
#include "MOTOR.h"
#include"PID.h"
#include"CAN.h"
#include"SELF_CHECK.h"

class MOTOR_3508 :
    public MOTOR,
    public SELF_CHECK
{
public:
    enum ID:uint16_t
    {
        ID1=0x201, ID2, ID3, ID4, ID5, ID6, ID7, ID8
    };
    const int16_t MAX_ELECTRICITY = 0, MAX_SPEED = 0;
    const int16_t MAX_ANGLE = 0, MIN_ANGLE = 0;
private :
    int8_t m_now_temperature=0;
    int16_t m_now_speed=0;
    int16_t m_now_angle=0;
    int32_t m_change_angle=0;
    int32_t m_set_speed=0;
    int16_t m_now_electricity=0;
    double m_set_electricity=0;
    CAN* m_can=0;
    ID m_id{};
    PID m_pid_angle_to_speed{};
    PID m_pid_speed_to_electricity{};
    template<typename T>
    T getAngleDelta(T now, T pre, T direct);
    template<typename T>
    T setInRange(T data,T max,T min);//设置数据范围
public:
    void setSpeed(int32_t speed);
    void setAngle(int32_t angle);
    void changeAngle(int32_t angle);
    void changeSpeed(int32_t speed);
    int getAngle();
    int getSpeed();
    void upData();
    void init(PID angle_to_speed, PID speed_to_electricity, ID id, CAN* can);
    MOTOR_3508(PID angle_to_speed, PID speed_to_electricity, ID id, CAN* can,
        int16_t angleMax = 8192, int16_t angleMin = 0, int16_t electricityMax = 16384,
        int16_t speedMAx=2000);
};

template<typename T>
T MOTOR_3508::setInRange(T data, T max, T min)
{
    if (data > max)return max;
    if (data < min)return min;
    return data;
}
template<typename T>
T MOTOR_3508::getAngleDelta(T now, T pre, T direct)
{
    T temp = now - pre;
    if (temp <= -4096)
    {
        return temp + 8192;
    }
    else if (temp >= 4096)
    {
        return temp - 8192;
    }
}
