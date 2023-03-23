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
     if (CAN_MessagePending(m_can, CAN_FIFO0) == 0)return;		//û�н��յ�����,ֱ���˳� 
     CAN_Receive(m_can, CAN_FIFO0, &m_receive);//��ȡ����	
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

    CAN_ITConfig(m_can, CAN_IT_FMP0, ENABLE);//FIFO0��Ϣ�Һ��ж�����.		    

    NVIC_InitStructure.NVIC_IRQChannel = CAN1_RX0_IRQn + (m_can == CAN2) * 44;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;     // �����ȼ�Ϊ1
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;            // �����ȼ�Ϊ0
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
        m_transmit.StdId = i.first;	 // ��׼��ʶ��Ϊ0
        m_transmit.ExtId = i.first;	 // ������չ��ʾ����29λ��
        m_transmit.IDE = 0;		  // ʹ����չ��ʶ��
        m_transmit.RTR = 0;		  // ��Ϣ����Ϊ����֡��һ֡8λ
        m_transmit.DLC = 8;							 // ������Ϣ
        memcpy(m_transmit.Data, i.second.m_transmit_data, sizeof(uint8_t) * 8);
        mbox = CAN_Transmit(m_can, &m_transmit);
        while (status == CAN_TxStatus_Failed && ii++)//�ȴ����ͽ���
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
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1 << (can == CAN2) | RCC_APB1Periph_CAN1, ENABLE);//ʹ��CANʱ��	

    //���Ÿ���ӳ������
    GPIO_PinAFConfig(rx.get_m_GPIOx(), GPIO::calculateGPIO_PinSourcex(&rx), (uint8_t)0x09); //CAN1 CAN2 ���ö���0x09  GPIO_AF_CAN1 GPIO_AF_CAN2
    GPIO_PinAFConfig(tx.get_m_GPIOx(), GPIO::calculateGPIO_PinSourcex(&tx), (uint8_t)0x09);

    //CAN��Ԫ����
    CAN_InitStructure.CAN_TTCM = DISABLE;	//��ʱ�䴥��ͨ��ģʽ   
    CAN_InitStructure.CAN_ABOM = DISABLE;	//����Զ����߹���	  
    CAN_InitStructure.CAN_AWUM = DISABLE;//˯��ģʽͨ���������(���CAN->MCR��SLEEPλ)
    CAN_InitStructure.CAN_NART = ENABLE;	//��ֹ�����Զ����� 
    CAN_InitStructure.CAN_RFLM = DISABLE;	//���Ĳ�����,�µĸ��Ǿɵ�  
    CAN_InitStructure.CAN_TXFP = DISABLE;	//���ȼ��ɱ��ı�ʶ������ 
    CAN_InitStructure.CAN_Mode = mode;	 //ģʽ���� 
    CAN_InitStructure.CAN_SJW = tsjw;	//����ͬ����Ծ���(Tsjw)Ϊtsjw+1��ʱ�䵥λ CAN_SJW_1tq~CAN_SJW_4tq
    CAN_InitStructure.CAN_BS1 = tbs1; //Tbs1��ΧCAN_BS1_1tq ~CAN_BS1_16tq
    CAN_InitStructure.CAN_BS2 = tbs2;//Tbs2��ΧCAN_BS2_1tq ~	CAN_BS2_8tq
    CAN_InitStructure.CAN_Prescaler = brp;  //��Ƶϵ��(Fdiv)Ϊbrp+1	
    CAN_Init(can, &CAN_InitStructure);   // ��ʼ��CAN1 

    //���ù�����
    CAN_FilterInitStructure.CAN_FilterNumber = 0 + (can == CAN2) * 14;	  //������
    CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;
    CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit; //32λ 
    CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000;////32λID
    CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;
    CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;//32λMASK
    CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;
    CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_Filter_FIFO0;//������0������FIFO0
    CAN_FilterInitStructure.CAN_FilterActivation = ENABLE; //���������0
    CAN_FilterInit(&CAN_FilterInitStructure);//�˲�����ʼ��
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

