#include "GPIO.h"

GPIO_TypeDef* GPIO::get_m_GPIOx()
{
    return m_GPIOx;
}

void GPIO::init(GPIO_TypeDef* GPIOx, uint32_t Pin, GPIOMode_TypeDef Mode, GPIOOType_TypeDef OType, GPIOPuPd_TypeDef PuPd)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    m_GPIOx = GPIOx;
    m_Pin = Pin;
    uint32_t AHB1_need;
    AHB1_need = RCC_AHB1Periph_GPIOA << (((uint32_t)GPIOx - (uint32_t)GPIOA) / 0x400);
    RCC_AHB1PeriphClockCmd(AHB1_need, ENABLE);
    GPIO_InitStructure.GPIO_Pin = Pin;
    GPIO_InitStructure.GPIO_Mode = Mode;
    GPIO_InitStructure.GPIO_OType = OType;
    GPIO_InitStructure.GPIO_Speed = GPIO_Fast_Speed;
    GPIO_InitStructure.GPIO_PuPd = PuPd;
    GPIO_Init(GPIOx, &GPIO_InitStructure);
}
uint16_t GPIO:: calculateGPIO_PinSourcex(GPIO* GPIOx)
{
    uint16_t GPIO_Pin_x;
    GPIO_Pin_x = GPIOx->getPin();
    uint8_t GPIO_PinSourcex = 0;
    while (GPIO_Pin_x != GPIO_Pin_0)
    {
        GPIO_Pin_x = (GPIO_Pin_x >> 1u);
        GPIO_PinSourcex++;
    }
    return GPIO_PinSourcex;
}
/*
GPIO::GPIO()
{
}

GPIO::GPIO(GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin, GPIOMode_TypeDef GPIO_Mode, GPIOOType_TypeDef GPIO_OType, GPIOPuPd_TypeDef PuPd)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    m_GPIOx = GPIOx;
    m_Pin = GPIO_Pin;
    uint32_t AHB1_need;
    AHB1_need = RCC_AHB1Periph_GPIOA << (((uint32_t)GPIOx - (uint32_t)GPIOA) / 0x400);
    RCC_AHB1PeriphClockCmd(AHB1_need, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode;
    GPIO_InitStructure.GPIO_OType = GPIO_OType;
    GPIO_InitStructure.GPIO_Speed = GPIO_Fast_Speed;
    GPIO_InitStructure.GPIO_PuPd = PuPd;
    GPIO_Init(GPIOx, &GPIO_InitStructure);
}
*/
