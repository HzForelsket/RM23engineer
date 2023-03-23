#ifndef __TIMER_H__
#define __TIMER_H__

#include"GPIO.h"
#include <misc.h>
#include <stm32f4xx_rcc.h>
#include <stm32f4xx_tim.h>
class TIM_X
{
public:
    TIM_TypeDef* m_timx;
    void (*On_IQRHandler)(void*);
    void* p;
private:
};
class TIMER
{
public:
    enum TIMER_MODE { BASE, PWM, ENCODER};
private:
    GPIO m_GPIOx;
    TIMER_MODE m_mode;
    TIM_TypeDef* m_timx;
    uint32_t m_TIM_Channel;
    double m_now_duty;
    void openBaseInterrupt();
public:
    //16hz<frequency<5e5hz  if you change prescaler, the frequency will be not accurate
    TIMER& initBase(TIMER_MODE mode, TIM_TypeDef* timx, double frequency, uint8_t openInterrupt = 0, double prescaler = 0);
    void (*m_TIMEx_IRQHandler)(void);
    TIMER& pwmInit(double duty, GPIO* GPIOx, uint32_t TIM_Channel_x);
    uint32_t getChannel();
    TIM_TypeDef* get_m_timx();
    double get_m_duty();
    void On_IQRHander();
    void setPwmDuty(uint16_t TIM_Channel_x, double duty);
    static uint8_t calculateAF_TIMx(TIMER* TIMERx);
    static uint16_t getTIMx_IRQn(TIM_TypeDef* TIMEx);
};


#endif // !__TIMER_H__

