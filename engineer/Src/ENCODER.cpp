#include "ENCODER.h"

ENCODER::ENCODER()
{
}

ENCODER::ENCODER(TIM_TypeDef* timex, std::vector<GPIO> gpio, std::vector< uint16_t> TIM_Channel_x)
{
    uint16_t need_TIM_IT_CCx;
    TIMER timer;
    timer.initBase(TIMER::ENCODER, timex, 16.6663);
    //16.6663 ÁîARRÎª 60000
    m_timex = timex;
    for (int i = 0; i < gpio.size(); i++)
    {
        GPIO_PinAFConfig(gpio[i].get_m_GPIOx(), calculateGPIO_PinSourcex(&(gpio[i])), calculateAF_TIMx(&timer));
    }
    TIM_ICInitTypeDef TIM_ICInitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    for (int i = 0; i < TIM_Channel_x.size(); i++)
    {
        TIM_ICInitStructure.TIM_Channel = TIM_Channel_x[i];
        TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
        TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
        TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
        TIM_ICInitStructure.TIM_ICFilter = 0x0A;

        TIM_EncoderInterfaceConfig(timex, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
        TIM_ICInit(timex, &TIM_ICInitStructure);

       
        TIM_ITConfig(timex, TIM_IT_Update, ENABLE);
        TIM_SetCounter(timex, 0);

        /*
        TIM_ClearFlag(timex, TIM_IT_Update);
        TIM_ITConfig(timex, TIM_IT_Update, ENABLE);
        NVIC_InitStructure.NVIC_IRQChannel = getTIMx_IRQn(timex);
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;
        NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;
        NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
        NVIC_Init(&NVIC_InitStructure);*/
    }
}

void ENCODER::init(TIM_TypeDef* timex, std::vector<GPIO> gpio, std::vector<uint16_t> TIM_Channel_x)
{
    uint16_t need_TIM_IT_CCx;
    TIMER timer;
    timer.initBase(TIMER::ENCODER, timex, 16.6663);
    //16.6663 ÁîARRÎª 60000
    m_timex = timex;
    for (int i = 0; i < gpio.size(); i++)
    {
        GPIO_PinAFConfig(gpio[i].get_m_GPIOx(), calculateGPIO_PinSourcex(&(gpio[i])), calculateAF_TIMx(&timer));
        // memcpy(m_gpio, &gpio[i], sizeof(GPIO));
    }
    TIM_ICInitTypeDef TIM_ICInitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    for (int i = 0; i < TIM_Channel_x.size(); i++)
    {
        TIM_ICInitStructure.TIM_Channel = TIM_Channel_x[i];
        TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
        TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
        TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
        TIM_ICInitStructure.TIM_ICFilter = 0x0A;

        TIM_EncoderInterfaceConfig(timex, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
        TIM_ICInit(timex, &TIM_ICInitStructure);


        TIM_ITConfig(timex, TIM_IT_Update, ENABLE);
        TIM_SetCounter(timex, 0);
    }
}

void ENCODER::upDate()
{
    m_last_count = m_now_count;
    m_now_count = m_timex->CNT;
}

int32_t ENCODER::delta()
{
    m_delta = m_now_count - m_last_count;
    if (m_delta >30000)
    {
        m_delta -= 60000;
    }
    else if(m_delta <-30000)
    {
        m_delta += 60000;
    }

    return m_delta;
}
