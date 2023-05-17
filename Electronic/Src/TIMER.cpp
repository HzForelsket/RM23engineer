#include"TIMER.h"
static TIM_X TIM_[15];
TIMER& TIMER::initBase(TIMER_MODE mode, TIM_TypeDef* TIMERx, double frequency, uint8_t openInterrupt, double prescaler)
{
    uint32_t APB2_multiply = 0, APB1_multiply = 0;
    APB2_multiply = ((RCC->CFGR) & 0x8000) ;
    APB1_multiply = ((RCC->CFGR) & 0x1000);//APBx时钟分频数不为1时，得到时钟为两倍

    RCC_ClocksTypeDef rcc_clock;
    RCC_GetClocksFreq(&rcc_clock);//获取总线时钟

    uint32_t APB1_clock = rcc_clock.PCLK1_Frequency * (APB1_multiply > 0 ? 2 : 1);
    uint32_t APB2_clock = rcc_clock.PCLK2_Frequency * (APB2_multiply > 0 ? 2 : 1);

    uint32_t RCC_APBxPeriph_TIMx_need;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    //memset(&TIM_TimeBaseInitStructure, 0, sizeof(TIM_TimeBaseInitTypeDef));
    if (TIMERx == TIM1 || TIMERx == TIM8)
    {
        int count = 0;
        if (frequency > 15 && frequency < 1e6)
        {
            prescaler = 168 ;
        }
        else if (frequency <= 15)
        {
            prescaler = 168000 ;
        }
        count = (double)APB2_clock / prescaler / (double)frequency ;
        RCC_APBxPeriph_TIMx_need = RCC_APB2Periph_TIM1 << (bool)(TIMERx == TIM8);
        RCC_APB2PeriphClockCmd(RCC_APBxPeriph_TIMx_need, ENABLE);
        TIM_TimeBaseInitStructure.TIM_Period = count - 1;
        TIM_TimeBaseInitStructure.TIM_Prescaler = prescaler - 1;
        TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
    }
    else if (TIMERx != TIM9 && TIMERx != TIM10 && TIMERx != TIM11)
    {
        int count = 0;
        if (frequency > 15 && frequency < 1e6)
        {
            prescaler = 84;
        }
        else if (frequency <= 15)
        {
            prescaler = 84000;
        }
        count = (double)APB1_clock / prescaler / (double)frequency ;
        RCC_APBxPeriph_TIMx_need = RCC_APB1Periph_TIM2 << (((uint32_t)TIMERx - (uint32_t)TIM2) >> 0x0A);
        RCC_APB1PeriphClockCmd(RCC_APBxPeriph_TIMx_need, ENABLE);
        TIM_TimeBaseInitStructure.TIM_Period = count-1;
        TIM_TimeBaseInitStructure.TIM_Prescaler = prescaler-1;
    }
    else if (TIMERx == TIM9 || TIMERx == TIM10 || TIMERx == TIM11)
    {
        int count = 0;
        if (frequency > 15 && frequency < 1e6)
        {
            prescaler = 168 ;
        }
        else if (frequency <= 15)
        {
            prescaler = 168000 ;
        }
        count = (double)APB2_clock / prescaler / (double)frequency ;
        RCC_APBxPeriph_TIMx_need = RCC_APB2Periph_TIM9 << (((uint32_t)TIMERx - (uint32_t)TIM9) >> 0x0A);
        RCC_APB2PeriphClockCmd(RCC_APBxPeriph_TIMx_need, ENABLE);
        TIM_TimeBaseInitStructure.TIM_Period = count-1;
        TIM_TimeBaseInitStructure.TIM_Prescaler = prescaler-1;
    }
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    if (mode == ENCODER)
        TIM_TimeBaseInitStructure.TIM_Prescaler = 0;

    TIM_TimeBaseInit(TIMERx, &TIM_TimeBaseInitStructure);
    TIM_Cmd(TIMERx, ENABLE);
    m_mode = mode;
    m_timx = TIMERx;
    if (m_mode == BASE && openInterrupt)
    {
        openBaseInterrupt();
    }
    return (*this);
}
TIMER& TIMER::pwmInit(double duty, GPIO* GPIOx, uint32_t TIM_Channel_x)
{
    memcpy(&(m_GPIOx), GPIOx,sizeof(GPIO));
    m_TIM_Channel = TIM_Channel_x;
    uint32_t RCC_AHB1Periph_GPIOx_need;
    RCC_AHB1Periph_GPIOx_need = RCC_AHB1Periph_GPIOA << (((uint32_t)m_GPIOx.get_m_GPIOx() - (uint32_t)GPIOA) >> 10u);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOx_need, ENABLE);

    GPIO_PinAFConfig(m_GPIOx.get_m_GPIOx(), GPIO::calculateGPIO_PinSourcex(&m_GPIOx), calculateAF_TIMx(this));

    TIM_OCInitTypeDef TIM_OCInitStructure;
    //memset(&TIM_OCInitStructure, 0, sizeof(TIM_OCInitTypeDef));
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;

    switch (TIM_Channel_x)
    {
    case TIM_Channel_1:
        TIM_OC1Init(m_timx, &TIM_OCInitStructure);
        TIM_OC1PreloadConfig(m_timx, TIM_OCPreload_Enable);
        break;
    case TIM_Channel_2:
        TIM_OC2Init(m_timx, &TIM_OCInitStructure);
        TIM_OC2PreloadConfig(m_timx, TIM_OCPreload_Enable);
        break;
    case TIM_Channel_3:
        TIM_OC3Init(m_timx, &TIM_OCInitStructure);
        TIM_OC3PreloadConfig(m_timx, TIM_OCPreload_Enable);
        break;
    case TIM_Channel_4:
        TIM_OC4Init(m_timx, &TIM_OCInitStructure);
        TIM_OC4PreloadConfig(m_timx, TIM_OCPreload_Enable);
        break;
    default:
        break;
    }
    //need change
    TIM_ARRPreloadConfig(m_timx, ENABLE);

    setPwmDuty(TIM_Channel_x, duty);
    return (*this);
}
void TIMER::openBaseInterrupt()
{
    uint32_t timx;
    NVIC_InitTypeDef NVIC_InitStructure;
    //memset(&NVIC_InitStructure, 0, sizeof(NVIC_InitTypeDef));
    TIM_ClearITPendingBit(m_timx, TIM_IT_Update);
    TIM_ITConfig(m_timx, TIM_IT_Update, ENABLE);
    switch ((uint32_t)m_timx)
    {
    case TIM1_BASE:
        timx = 1;
        break;
    case TIM2_BASE:
        timx = 2;
        break;

    case TIM3_BASE:
        timx = 3;
        break;
    case TIM4_BASE:
        timx = 4;
        break;
    case TIM5_BASE:
        timx = 5;
        break;
    case TIM6_BASE:
        timx = 6;
        break;
    case TIM7_BASE:
        timx = 7;
        break;
    case TIM8_BASE:
        timx = 8;
        break;
    case TIM9_BASE:
        timx = 9;
        break;
    case TIM10_BASE:
        timx = 10;
        break;
    case TIM11_BASE:
        timx = 11;
        break;
    case TIM12_BASE:
        timx = 12;
        break;
    case TIM13_BASE:
        timx = 13;
        break;
    case TIM14_BASE:
        timx = 14;
        break;

    default:
        break;
    }
    TIM_[timx].m_timx = m_timx;
    TIM_[timx].p = (void*)(this);
    void (TIMER:: * p)(void) = &TIMER::On_IQRHander;
    auto func = reinterpret_cast<void(**)(void*)>(&p);
    TIM_[timx].On_IQRHandler = *func;
    NVIC_InitStructure.NVIC_IRQChannel = getTIMx_IRQn(m_timx);
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x03;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    //return (*this);
}
uint32_t TIMER::getChannel()
{
    return m_TIM_Channel;
}
void TIMER::setPwmDuty(uint16_t TIM_Channel_x, double duty)
{
    uint8_t CCRx_offset;
    CCRx_offset = ((TIM_Channel_x - TIM_Channel_1) >> 2u);
    *(&(m_timx->CCR1) + CCRx_offset) = duty*(double)(m_timx->ARR);
    m_now_duty = duty;
}

uint8_t TIMER:: calculateAF_TIMx(TIMER* TIMERx)
{
    switch ((uint32_t)TIMERx->get_m_timx())
    {
    case TIM1_BASE:
        return 0x01;
        break;
    case TIM2_BASE:
        return 0x01;
        break;
    case TIM3_BASE:
        return 0x02;
        break;
    case TIM4_BASE:
        return 0x02;
        break;
    case TIM5_BASE:
        return 0x02;
        break;
    case TIM8_BASE:
        return 0x03;
        break;
    case TIM9_BASE:
        return 0x03;
        break;
    case TIM10_BASE:
        return 0x03;
        break;
    case TIM11_BASE:
        return 0x03;
        break;
    case TIM12_BASE:
        return 0x09;
        break;
    case TIM13_BASE:
        return 0x09;
        break;
    case TIM14_BASE:
        return 0x09;
        break;
    default:
        break;
    }
}

uint16_t TIMER::getTIMx_IRQn(TIM_TypeDef* TIMEx)
{
    switch ((uint32_t)TIMEx)
    {
    case TIM1_BASE:
        return TIM1_UP_TIM10_IRQn;
        break;
    case TIM2_BASE:
        return TIM2_IRQn;
        break;
    case TIM3_BASE:
        return TIM3_IRQn;
        break;
    case TIM4_BASE:
        return TIM4_IRQn;
        break;
    case TIM5_BASE:
        return TIM5_IRQn;
        break;
    case TIM6_BASE:
        return TIM6_DAC_IRQn;
        break;
    case TIM7_BASE:
        return TIM7_IRQn;
        break;
    case TIM8_BASE:
        return TIM8_UP_TIM13_IRQn;
        break;
    case TIM9_BASE:
        return TIM1_BRK_TIM9_IRQn;
        break;
    case TIM10_BASE:
        return TIM1_UP_TIM10_IRQn;
        break;
    case TIM11_BASE:
        return TIM1_TRG_COM_TIM11_IRQn;
        break;
    case TIM12_BASE:
        return TIM8_BRK_TIM12_IRQn;
        break;
    case TIM13_BASE:
        return TIM8_UP_TIM13_IRQn;
        break;
    case TIM14_BASE:
        return TIM8_TRG_COM_TIM14_IRQn;
        break;
    default:
        break;
    }
}

TIM_TypeDef* TIMER::get_m_timx()
{
    return m_timx;
}

double TIMER::get_m_duty()
{
    return m_now_duty;
}

void TIMER::On_IQRHander()
{
    this->m_TIMEx_IRQHandler();
}


extern "C" void TIM2_IRQHandler(void)
   {
   if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
   {
       if (TIM_[2].m_timx)
       {
           TIM_[2].On_IQRHandler(TIM_[2].p);
       }
       /*if (((TIMER*)(memory_TIMx_and_TIMERx.find((uint32_t)TIM2)->second))->m_TIMEx_IRQHandler)
       {
           ((TIMER*)(memory_TIMx_and_TIMERx.find((uint32_t)TIM2)->second))->m_TIMEx_IRQHandler();
       }*/
   } 
   TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
   }
extern "C" void TIM3_IRQHandler(void)
   {

       if (TIM_GetITStatus(TIM3, TIM_IT_Update) == SET) 
       {
           if (TIM_[3].m_timx)
           {
               TIM_[3].On_IQRHandler(TIM_[3].p);
           }
           /*if (((TIMER*)(memory_TIMx_and_TIMERx.find((uint32_t)TIM3)->second))->m_TIMEx_IRQHandler)
           {
               ((TIMER*)(memory_TIMx_and_TIMERx.find((uint32_t)TIM3)->second))->m_TIMEx_IRQHandler();
           }*/
       }
       TIM_ClearITPendingBit(TIM3, TIM_IT_Update); 
   }
extern "C" void TIM4_IRQHandler(void)
   {
   if (TIM_GetITStatus(TIM4, TIM_IT_Update) == SET)
   {
       if (TIM_[4].m_timx)
       {
           TIM_[4].On_IQRHandler(TIM_[4].p);
       }
       /*if (((TIMER*)(memory_TIMx_and_TIMERx.find((uint32_t)TIM4)->second))->m_TIMEx_IRQHandler)
       {
           ((TIMER*)(memory_TIMx_and_TIMERx.find((uint32_t)TIM4)->second))->m_TIMEx_IRQHandler();
       }*/
   }
       TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
   }
extern "C" void TIM5_IRQHandler(void)
   {
   if (TIM_GetITStatus(TIM5, TIM_IT_Update) == SET)
   {
       if (TIM_[5].m_timx)
       {
           TIM_[5].On_IQRHandler(TIM_[5].p);
       }
       /*if (((TIMER*)(memory_TIMx_and_TIMERx.find((uint32_t)TIM5)->second))->m_TIMEx_IRQHandler)
       {
           ((TIMER*)(memory_TIMx_and_TIMERx.find((uint32_t)TIM5)->second))->m_TIMEx_IRQHandler();
       }*/
   }
       TIM_ClearITPendingBit(TIM5, TIM_IT_Update);
   }
extern "C" void TIM7_IRQHandler(void)
   {
   if (TIM_GetITStatus(TIM7, TIM_IT_Update) == SET)
   {
       if (TIM_[7].m_timx)
       {
           TIM_[7].On_IQRHandler(TIM_[7].p);
       }
       /*if (((TIMER*)(memory_TIMx_and_TIMERx.find((uint32_t)TIM7)->second))->m_TIMEx_IRQHandler)
       {
           ((TIMER*)(memory_TIMx_and_TIMERx.find((uint32_t)TIM7)->second))->m_TIMEx_IRQHandler();
       }*/
   }
       TIM_ClearITPendingBit(TIM7, TIM_IT_Update);
   }
extern "C" void TIM8_UP_TIM13_IRQHandler(void)
{
   if (TIM_GetITStatus(TIM8, TIM_IT_Update) == SET)
   {
       if (TIM_[8].m_timx)
       {
           TIM_[8].On_IQRHandler(TIM_[8].p);
       }
       /*if (((TIMER*)(memory_TIMx_and_TIMERx.find((uint32_t)TIM8)->second))->m_TIMEx_IRQHandler)
       {
           ((TIMER*)(memory_TIMx_and_TIMERx.find((uint32_t)TIM8)->second))->m_TIMEx_IRQHandler();
       }*/
   }
   if (TIM_GetITStatus(TIM13, TIM_IT_Update) == SET)
   {
       if (TIM_[13].m_timx)
       {
           TIM_[13].On_IQRHandler(TIM_[13].p);
       }
       /*if (((TIMER*)(memory_TIMx_and_TIMERx.find((uint32_t)TIM13)->second))->m_TIMEx_IRQHandler)
       {
           ((TIMER*)(memory_TIMx_and_TIMERx.find((uint32_t)TIM13)->second))->m_TIMEx_IRQHandler();
       }*/
   }
   TIM_ClearITPendingBit(TIM8, TIM_IT_Update);
   TIM_ClearITPendingBit(TIM13, TIM_IT_Update);

}
extern "C" void TIM1_BRK_TIM9_IRQHandler(void)
{
   if (TIM_GetITStatus(TIM9, TIM_IT_Update) == SET)
   {
       if (TIM_[9].m_timx)
       {
           TIM_[9].On_IQRHandler(TIM_[9].p);
       }
       /*if (((TIMER*)(memory_TIMx_and_TIMERx.find((uint32_t)TIM9)->second))->m_TIMEx_IRQHandler)
       {
           ((TIMER*)(memory_TIMx_and_TIMERx.find((uint32_t)TIM9)->second))->m_TIMEx_IRQHandler();
       }*/
   }
   TIM_ClearITPendingBit(TIM9, TIM_IT_Update);
}
extern "C" void TIM1_UP_TIM10_IRQHandler(void)
{
   if (TIM_GetITStatus(TIM10, TIM_IT_Update) == SET)
   {
       if (TIM_[10].m_timx)
       {
           TIM_[10].On_IQRHandler(TIM_[10].p);
       }
       /*if (((TIMER*)(memory_TIMx_and_TIMERx.find((uint32_t)TIM10)->second))->m_TIMEx_IRQHandler)
       {
           ((TIMER*)(memory_TIMx_and_TIMERx.find((uint32_t)TIM10)->second))->m_TIMEx_IRQHandler();
       }*/
   }
   if (TIM_GetITStatus(TIM1, TIM_IT_Update) == SET)
   {
       if (TIM_[1].m_timx)
       {
           TIM_[1].On_IQRHandler(TIM_[1].p);
       }
       /*if (((TIMER*)(memory_TIMx_and_TIMERx.find((uint32_t)TIM1)->second))->m_TIMEx_IRQHandler)
       {
           ((TIMER*)(memory_TIMx_and_TIMERx.find((uint32_t)TIM1)->second))->m_TIMEx_IRQHandler();
       }*/
   }
   TIM_ClearITPendingBit(TIM10, TIM_IT_Update);
   TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
}
extern "C" void TIM1_TRG_COM_TIM11_IRQHandler(void)
{
   if (TIM_GetITStatus(TIM11, TIM_IT_Update) == SET)
   {
       if (TIM_[11].m_timx)
       {
           TIM_[11].On_IQRHandler(TIM_[11].p);
       }
       /*if (((TIMER*)(memory_TIMx_and_TIMERx.find((uint32_t)TIM11)->second))->m_TIMEx_IRQHandler)
       {
           ((TIMER*)(memory_TIMx_and_TIMERx.find((uint32_t)TIM11)->second))->m_TIMEx_IRQHandler();
       }*/
   }
   TIM_ClearITPendingBit(TIM11, TIM_IT_Update);
}
extern "C" void TIM8_BRK_TIM12_IRQHandler(void)
{
   if (TIM_GetITStatus(TIM12, TIM_IT_Update) == SET)
   {
       if (TIM_[12].m_timx)
       {
           TIM_[12].On_IQRHandler(TIM_[12].p);
       }
       /*if (((TIMER*)(memory_TIMx_and_TIMERx.find((uint32_t)TIM12)->second))->m_TIMEx_IRQHandler)
       {
           ((TIMER*)(memory_TIMx_and_TIMERx.find((uint32_t)TIM12)->second))->m_TIMEx_IRQHandler();
       }*/
   }
   TIM_ClearITPendingBit(TIM12, TIM_IT_Update);
}
extern "C" void TIM8_TRG_COM_TIM14_IRQHandler(void)
{
   if (TIM_GetITStatus(TIM14, TIM_IT_Update) == SET)
   {
       if (TIM_[14].m_timx)
       {
           TIM_[14].On_IQRHandler(TIM_[14].p);
       }
       /*if (((TIMER*)(memory_TIMx_and_TIMERx.find((uint32_t)TIM14)->second))->m_TIMEx_IRQHandler)
       {
           ((TIMER*)(memory_TIMx_and_TIMERx.find((uint32_t)TIM14)->second))->m_TIMEx_IRQHandler();
       }*/
   }
   TIM_ClearITPendingBit(TIM14, TIM_IT_Update);
}
