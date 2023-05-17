#include "IIC.h"

bool IIC::I2C_Start(void)
{
	GPIO_SetBits(m_SDA.get_m_GPIOx(), m_SDA.getPin());
	GPIO_SetBits(m_SCL.get_m_GPIOx(), m_SCL.getPin());
	delay_us(4);
	if (!GPIO_ReadOutputDataBit(m_SDA.get_m_GPIOx(), m_SDA.getPin())) 
	{
		return 0;
	} 
	GPIO_ResetBits(m_SDA.get_m_GPIOx(), m_SDA.getPin());
	delay_us(4);
	GPIO_ResetBits(m_SCL.get_m_GPIOx(), m_SCL.getPin());
	delay_us(4);
	return 1;

}

void IIC::I2C_Stop(void)
{
	GPIO_ResetBits(m_SDA.get_m_GPIOx(), m_SDA.getPin());
	delay_us(4);
	GPIO_ResetBits(m_SCL.get_m_GPIOx(), m_SCL.getPin());
	delay_us(4);
	GPIO_SetBits(m_SCL.get_m_GPIOx(), m_SCL.getPin());
	delay_us(4);
	GPIO_SetBits(m_SDA.get_m_GPIOx(), m_SDA.getPin());
	delay_us(4);
}

bool IIC::I2C_WaitAck(void)
{

	uint16_t i = 0;
	GPIO_SetBits(m_SDA.get_m_GPIOx(), m_SDA.getPin());
	delay_us(1);
	GPIO_SetBits(m_SCL.get_m_GPIOx(), m_SCL.getPin());
	delay_us(1);
	while (GPIO_ReadOutputDataBit(m_SDA.get_m_GPIOx(), m_SDA.getPin()))
	{
		i++;      
		if (i == 50)
			break;
	}
	if (GPIO_ReadOutputDataBit(m_SDA.get_m_GPIOx(), m_SDA.getPin()))
	{
		GPIO_ResetBits(m_SCL.get_m_GPIOx(), m_SCL.getPin());
		return false;
	}
	GPIO_ResetBits(m_SCL.get_m_GPIOx(), m_SCL.getPin()); 
	return true;
}

void IIC::I2C_SendAck(bool ack)
{
	GPIO_ResetBits(m_SCL.get_m_GPIOx(), m_SCL.getPin());
	if (true == ack)
		GPIO_SetBits(m_SDA.get_m_GPIOx(), m_SDA.getPin());
	else
		GPIO_ResetBits(m_SDA.get_m_GPIOx(), m_SDA.getPin());
	delay_us(2);
	GPIO_SetBits(m_SCL.get_m_GPIOx(), m_SCL.getPin());
	delay_us(2);
	GPIO_ResetBits(m_SCL.get_m_GPIOx(), m_SCL.getPin());

}

bool IIC::get_ACT()
{
	return m_IIC_ACT;
}

void IIC::receive_data(uint8_t* data)
{
	u8 retc = 0;
	GPIO_SetBits(m_SDA.get_m_GPIOx(), m_SDA.getPin());
	for (uint16_t i = 0x01; i <= 0x80; i<<=1)
	{
		GPIO_ResetBits(m_SCL.get_m_GPIOx(), m_SCL.getPin());
		delay_us(2);
		GPIO_SetBits(m_SCL.get_m_GPIOx(), m_SCL.getPin());
		if (GPIO_ReadInputDataBit(m_SDA.get_m_GPIOx(), m_SDA.getPin()))
		{
			retc = retc | i;
		}
		delay_us(1);
	}
	GPIO_ResetBits(m_SCL.get_m_GPIOx(), m_SCL.getPin());
	delay_us(10);
	*data = retc;
}

void IIC::init(GPIO SDA, GPIO SCL)
{
	memcpy(&m_SCL, &SCL, sizeof(GPIO));
	memcpy(&m_SDA, &SDA, sizeof(GPIO));

}

void IIC::send_data(uint8_t data)
{
		GPIO_ResetBits(m_SCL.get_m_GPIOx(), m_SCL.getPin());
		for (int in = 0; in < 8; in++)         
		{
			if (data & 0x80)//将dat的8位从最高位依次写入
			{
				GPIO_SetBits(m_SDA.get_m_GPIOx(), m_SDA.getPin());
			}
			else
			{
				GPIO_ResetBits(m_SDA.get_m_GPIOx(), m_SDA.getPin());
			}
			delay_us(2);
			GPIO_SetBits(m_SCL.get_m_GPIOx(), m_SCL.getPin());  
			delay_us(2);        
			GPIO_ResetBits(m_SCL.get_m_GPIOx(), m_SCL.getPin());
			delay_us(2); 		
			data <<= 1;          
		}
}

void IIC::send_byte(uint8_t data)
{
	send_data(data);
	m_IIC_ACT=I2C_WaitAck();
}

void IIC::send_bytes(uint8_t* data, uint16_t length)
{
	for (int i = 0; i < length; i++)
	{
		send_byte(*(data+i));
	}
}
