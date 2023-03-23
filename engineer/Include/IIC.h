#ifndef __IIC_H__
#define __IIC_H__
#include"GPIO.h"
#include"delay.h"
class IIC
{
private:
	GPIO m_SDA, m_SCL;
	bool m_IIC_ACT;
public:
	void init(GPIO SDA, GPIO SCL);
	void send_data(uint8_t data);
	void send_byte(uint8_t data);
	void send_bytes(uint8_t* data, uint16_t length);
	bool I2C_Start(void);
	void I2C_Stop(void);
	bool I2C_WaitAck(void);
	void I2C_SendAck(bool ack);
	bool get_ACT();
	void receive_data(uint8_t* data);
};

#endif
