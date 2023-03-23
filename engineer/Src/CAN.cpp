#include "CAN.h"

 class CAN_X
{
public:
    CAN_TypeDef* m_can;
    void (*On_IQRHandler)(void*);
    void* p;
private:
};
 static CAN_X can_x[2];
 void CAN::On_IQRHander()
 {
     if (CAN_MessagePending(m_can, CAN_FIFO0) == 0)return;		//没有接收到数据,直接退出 
     CAN_Receive(m_can, CAN_FIFO0, &m_receive);//读取数据	
     RECEIVE_TEMP temp(m_receive.Data);
     m_receive_data[m_receive.StdId]= temp;
     /*
     if(m_CANx_IRQHandler)
     this->m_CANx_IRQHandler();*/
 }

 void CAN::open_receive_interrput()
 {
    can_x[m_can==CAN2].m_can = m_can;
    can_x[m_can == CAN2].p = (void*)(this);
    void (CAN:: * p)(void) = &CAN::On_IQRHander;
    auto func = reinterpret_cast<void(**)(void*)>(&p);
    can_x[m_can == CAN2].On_IQRHandler = *func;
    NVIC_InitTypeDef  NVIC_InitStructure;

    CAN_ITConfig(m_can, CAN_IT_FMP0, ENABLE);//FIFO0消息挂号中断允许.		    

    NVIC_InitStructure.NVIC_IRQChannel = CAN1_RX0_IRQn + (m_can == CAN2) * 44;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;     // 主优先级为1
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;            // 次优先级为0
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
 }
 std::map<uint32_t, RECEIVE_TEMP>::iterator CAN::read_data(uint32_t stdId)
{
     std::map<uint32_t, RECEIVE_TEMP>::iterator test;
     test=m_receive_data.find(stdId);
     uint8_t* data = test->second.m_receive_data;
     return m_receive_data.find(stdId);
}

uint8_t CAN::transmit_data()
{
    uint8_t mbox, status = CAN_TxStatus_Failed;
    for (auto i : m_transmit_data)
    {
        uint8_t ii = 1;
        m_transmit.StdId = i.first;	 // 标准标识符为0
        m_transmit.ExtId = i.first;	 // 设置扩展标示符（29位）
        m_transmit.IDE = 0;		  // 使用扩展标识符
        m_transmit.RTR = 0;		  // 消息类型为数据帧，一帧8位
        m_transmit.DLC = 8;							 // 发送信息
        memcpy(m_transmit.Data, i.second.m_transmit_data, sizeof(uint8_t) * 8);
        mbox = CAN_Transmit(m_can, &m_transmit);
        while (status == CAN_TxStatus_Failed && ii++)//等待发送结束
        {
            status = CAN_TransmitStatus(m_can, mbox);
        }
    }
    return status;

}

void CAN::set_transmit_data(uint8_t* data, uint8_t length, uint8_t offset,uint32_t stdId)
{
    if (m_transmit_data.find(stdId) == m_transmit_data.end())
    {
        TRANSMIT_TEMP temp;
        m_transmit_data[stdId] = temp;
    }
    
;    for (uint8_t i = offset * 2, l = i + 1; i < l; i++)
    {
        m_transmit_data[stdId].m_transmit_data[i] = *(data++);
    }
}

CAN& CAN::init(GPIO& rx, GPIO& tx, CAN_TypeDef* can, uint8_t tsjw, uint8_t tbs2, uint8_t tbs1, uint16_t brp, uint8_t mode)
{


    m_can = can;
    memcpy(&m_rx, &rx, sizeof(GPIO));
    memcpy(&m_tx, &tx, sizeof(GPIO));

    CAN_InitTypeDef        CAN_InitStructure;
    CAN_FilterInitTypeDef  CAN_FilterInitStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1 << (can == CAN2) | RCC_APB1Periph_CAN1, ENABLE);//使能CAN时钟	

    //引脚复用映射配置
    GPIO_PinAFConfig(rx.get_m_GPIOx(), GPIO::calculateGPIO_PinSourcex(&rx), (uint8_t)0x09); //CAN1 CAN2 复用都是0x09  GPIO_AF_CAN1 GPIO_AF_CAN2
    GPIO_PinAFConfig(tx.get_m_GPIOx(), GPIO::calculateGPIO_PinSourcex(&tx), (uint8_t)0x09);

    //CAN单元设置
    CAN_InitStructure.CAN_TTCM = DISABLE;	//非时间触发通信模式   
    CAN_InitStructure.CAN_ABOM = DISABLE;	//软件自动离线管理	  
    CAN_InitStructure.CAN_AWUM = DISABLE;//睡眠模式通过软件唤醒(清除CAN->MCR的SLEEP位)
    CAN_InitStructure.CAN_NART = ENABLE;	//禁止报文自动传送 
    CAN_InitStructure.CAN_RFLM = DISABLE;	//报文不锁定,新的覆盖旧的  
    CAN_InitStructure.CAN_TXFP = DISABLE;	//优先级由报文标识符决定 
    CAN_InitStructure.CAN_Mode = mode;	 //模式设置 
    CAN_InitStructure.CAN_SJW = tsjw;	//重新同步跳跃宽度(Tsjw)为tsjw+1个时间单位 CAN_SJW_1tq~CAN_SJW_4tq
    CAN_InitStructure.CAN_BS1 = tbs1; //Tbs1范围CAN_BS1_1tq ~CAN_BS1_16tq
    CAN_InitStructure.CAN_BS2 = tbs2;//Tbs2范围CAN_BS2_1tq ~	CAN_BS2_8tq
    CAN_InitStructure.CAN_Prescaler = brp;  //分频系数(Fdiv)为brp+1	
    CAN_Init(can, &CAN_InitStructure);   // 初始化CAN1 

    //配置过滤器
    CAN_FilterInitStructure.CAN_FilterNumber = 0 + (can == CAN2) * 14;	  //过滤器
    CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;
    CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit; //32位 
    CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000;////32位ID
    CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;
    CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;//32位MASK
    CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;
    CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_Filter_FIFO0;//过滤器0关联到FIFO0
    CAN_FilterInitStructure.CAN_FilterActivation = ENABLE; //激活过滤器0
    CAN_FilterInit(&CAN_FilterInitStructure);//滤波器初始化
    return (*this);
}

extern "C" void CAN1_RX0_IRQHandler(void)
{
    can_x[0].On_IQRHandler(can_x[0].p);
}
extern "C" void CAN2_RX0_IRQHandler(void)
{
    can_x[1].On_IQRHandler(can_x[1].p);

}

