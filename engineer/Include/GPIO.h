#ifndef __GPIO_H__
#define __GPIO_H__
#include"stm32f4xx_gpio.h"
#include <stm32f4xx_rcc.h>
#include<string.h>
class GPIO
{
private:
    uint16_t m_Pin{};
    GPIO_TypeDef* m_GPIOx{};
public:
  //  friend bool operator<(const GPIO& T, const GPIO& D);
    GPIO_TypeDef* get_m_GPIOx();
    uint16_t getPin() {
        return m_Pin;
    }
    void init(GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin, GPIOMode_TypeDef GPIO_Mode = GPIO_Mode_OUT,
        GPIOOType_TypeDef GPIO_OType = GPIO_OType_PP, GPIOPuPd_TypeDef PuPd = GPIO_PuPd_DOWN);
    static uint16_t calculateGPIO_PinSourcex(GPIO* GPIOx);
 //   GPIO();
 //   GPIO(GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin, GPIOMode_TypeDef GPIO_Mode = GPIO_Mode_OUT,
 //   GPIOOType_TypeDef GPIO_OType = GPIO_OType_PP, GPIOPuPd_TypeDef PuPd = GPIO_PuPd_DOWN);
};

#endif