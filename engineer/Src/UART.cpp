#include "UART.h"
USART_TypeDef* UART::get_UARTx()
{
    return m_uart;
}

void UART::transmit_data()
{
        for (int i = 0; i < m_transmit_length ; i++)
        {
            while (USART_GetFlagStatus(m_uart, USART_FLAG_TC) != SET);
            USART_SendData(m_uart, (uint16_t)m_trains_data[i]);
        }
}

void UART::receive()
{
    if (USART_GetITStatus(m_uart, USART_IT_RXNE) == SET)  
    {
        if (receive_count<m_length)
        {
            m_receive_date[receive_count] = USART_ReceiveData(m_uart);
            receive_count++;
        }
        else
        {
            receive_count %= m_length;
        }
        USART_ClearITPendingBit(m_uart, USART_FLAG_RXNE);
    }
    else if (USART_GetITStatus(m_uart, USART_IT_IDLE) == SET)
    {
        uint8_t temp;
        if (USART_GetITStatus(m_uart, USART_IT_IDLE) == SET)
        {
            temp = m_uart->SR;
            temp = m_uart->DR;	//读取SR DR数据可清除“空闲中断”标志
            m_length = MAXLEN - DMA_GetCurrDataCounter(m_stream);
            if (0 != m_length)
            {
                //Receive_DataPack();/*DMA接收模式时处理接收数据函数*/
            }
            
            DMA_Cmd(m_stream, DISABLE);							//暂停DMA传输 
            // 清除DMA中断标志位
            //DMA_ClearFlag(m_stream, DMA_FLAG_TCIF5 | DMA_FLAG_FEIF5 | DMA_FLAG_DMEIF5 | DMA_FLAG_TEIF5 | DMA_FLAG_HTIF5);//清除DMA2_Steam7传输完成标志
            switch ((uint32_t)m_stream)
            {
            case DMA2_Stream5_BASE:DMA_ClearFlag(m_stream, DMA_FLAG_TCIF5 | DMA_FLAG_FEIF5 | DMA_FLAG_DMEIF5 | DMA_FLAG_TEIF5 | DMA_FLAG_HTIF5); break;
            case DMA1_Stream5_BASE:DMA_ClearFlag(m_stream, DMA_FLAG_TCIF5 | DMA_FLAG_FEIF5 | DMA_FLAG_DMEIF5 | DMA_FLAG_TEIF5 | DMA_FLAG_HTIF5); break;
            case DMA1_Stream1_BASE:DMA_ClearFlag(m_stream, DMA_FLAG_TCIF1 | DMA_FLAG_FEIF1 | DMA_FLAG_DMEIF1 | DMA_FLAG_TEIF1 | DMA_FLAG_HTIF1); break;
            case DMA1_Stream2_BASE:DMA_ClearFlag(m_stream, DMA_FLAG_TCIF2 | DMA_FLAG_FEIF2 | DMA_FLAG_DMEIF2 | DMA_FLAG_TEIF2 | DMA_FLAG_HTIF2); break;
            case DMA1_Stream0_BASE:DMA_ClearFlag(m_stream, DMA_FLAG_TCIF0 | DMA_FLAG_FEIF0 | DMA_FLAG_DMEIF0 | DMA_FLAG_TEIF0 | DMA_FLAG_HTIF0); break;
            case DMA2_Stream1_BASE:DMA_ClearFlag(m_stream, DMA_FLAG_TCIF1 | DMA_FLAG_FEIF1 | DMA_FLAG_DMEIF1 | DMA_FLAG_TEIF1 | DMA_FLAG_HTIF1); break;
            default:break;
            }
            while (DMA_GetCmdStatus(m_stream) != DISABLE) {}		//确保DMA可以被设置  
            DMA_SetCurrDataCounter(m_stream, MAXLEN); 	//设置DMA数据传输量 
            DMA_Cmd(m_stream, ENABLE);                     		//开启DMA传输 
        }
    }
    
}
void UART::init(USART_TypeDef* UARTx, uint32_t BaudRate, std::vector<GPIO> UART_GPIO,uint32_t length,bool open_DMA)
{
    m_open_dma = open_DMA;
    m_uart = UARTx;
    m_length = length * 2* !open_DMA;
    if ((uint32_t)UARTx == USART1_BASE || (uint32_t)UARTx == USART6_BASE)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 << ((uint32_t)UARTx == USART6_BASE), ENABLE);
    }
    else if ((uint32_t)UARTx == UART7_BASE || (uint32_t)UARTx == UART8_BASE)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART7 << ((uint32_t)UARTx == UART8_BASE), ENABLE);
    }
    else
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2 << (((uint32_t)UARTx - USART2_BASE)>>10), ENABLE);
    }

    
    for (int i = 0; i < UART_GPIO.size(); i++)
    {
        GPIO_PinAFConfig(UART_GPIO[i].get_m_GPIOx(), GPIO::calculateGPIO_PinSourcex(&(UART_GPIO[i])), GPIO_AF_USART6-((uint32_t)UARTx== USART1_BASE|| (uint32_t)UARTx == USART2_BASE|| (uint32_t)UARTx == USART3_BASE));
    }

    USART_InitTypeDef UART_init;
    UART_init.USART_BaudRate = BaudRate;
    UART_init.USART_WordLength = USART_WordLength_8b;
    UART_init.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    UART_init.USART_Parity = USART_Parity_No;
    UART_init.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    UART_init.USART_StopBits = USART_StopBits_1;

    NVIC_InitTypeDef NVIC_InitStructure;
    IRQn_Type need_IRQn;
    switch ((uint32_t)UARTx)
    {
    case USART1_BASE:need_IRQn = USART1_IRQn; m_stream = DMA2_Stream5; break;
    case USART2_BASE:need_IRQn = USART2_IRQn; m_stream = DMA1_Stream5; break;
    case USART3_BASE:need_IRQn = USART3_IRQn; m_stream = DMA1_Stream1; break;
    case UART4_BASE:need_IRQn = UART4_IRQn; m_stream = DMA1_Stream2; break;
    case UART5_BASE:need_IRQn = UART5_IRQn; m_stream = DMA1_Stream0; break;
    case USART6_BASE:need_IRQn = USART6_IRQn; m_stream = DMA2_Stream1; break;
    default:break;
    }

    NVIC_InitStructure.NVIC_IRQChannel = need_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02; 
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
    NVIC_Init(&NVIC_InitStructure); 

    if(!open_DMA)
    USART_ITConfig(UARTx, USART_IT_RXNE, ENABLE);
    else
    {
        USART_ITConfig(UARTx, USART_IT_IDLE, ENABLE);;
        USART_DMACmd(UARTx, USART_DMAReq_Rx, ENABLE);
        if (UARTx == USART6) DMA_RX_Config(m_stream, DMA_Channel_5, (u32)&UARTx->DR, (u32)m_receive_date, MAXLEN);
        else  DMA_RX_Config(m_stream, DMA_Channel_4, (u32)&UARTx->DR, (u32)m_receive_date, MAXLEN);//其他都是通道4
    }
    
    USART_Init(UARTx, &UART_init);
    USART_Cmd(UARTx, ENABLE);
}

void UART::set_transmit_data(uint8_t* data, uint32_t length)
{
    memcpy(m_trains_data, data, length * sizeof(uint8_t));
    m_transmit_length = length;
}

void UART::DMA_RX_Config(DMA_Stream_TypeDef* DMA_Streamx, u32 chx, u32 par, u32 mar, u16 ndtr)
{
    DMA_InitTypeDef  DMA_InitStructure;
    if ((u32)DMA_Streamx > (u32)DMA2)//得到当前stream是属于DMA2还是DMA1
    {
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);	//DMA2时钟使能 
    }
    else
    {
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);	//DMA1时钟使能 
    }
    DMA_DeInit(DMA_Streamx);
    while (DMA_GetCmdStatus(DMA_Streamx) != DISABLE) {}		//等待DMA可配置 

    /*配置 DMA Stream*/
    DMA_InitStructure.DMA_Channel = chx;  							//通道选择
    DMA_InitStructure.DMA_PeripheralBaseAddr = par;					//DMA外设地址
    DMA_InitStructure.DMA_Memory0BaseAddr = mar;					//DMA存储器0地址
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;			//外设到存储器
    DMA_InitStructure.DMA_BufferSize = ndtr;						//数据传输量 
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//外设非增量模式
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;			//存储器增量模式
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;//外设数据长度:8位
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;	//存储器数据长度:8位
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal; 					//正常模式，即满了就不在接收了，而不是循环存储
    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;			//高优先级
    DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
    DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
    DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;		//存储器突发单次传输？？？
    DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;//外设突发单次传输？？？
    DMA_Init(DMA_Streamx, &DMA_InitStructure);						//初始化DMA Stream
    switch ((uint32_t)DMA_Streamx)
    {
    case DMA2_Stream5_BASE:DMA_ClearFlag(DMA_Streamx, DMA_FLAG_TCIF5);	 break;
    case DMA1_Stream5_BASE:DMA_ClearFlag(DMA_Streamx, DMA_FLAG_TCIF5);	 break;
    case DMA1_Stream1_BASE:DMA_ClearFlag(DMA_Streamx, DMA_FLAG_TCIF1);	 break;
    case DMA1_Stream2_BASE:DMA_ClearFlag(DMA_Streamx, DMA_FLAG_TCIF2);	 break;
    case DMA1_Stream0_BASE:DMA_ClearFlag(DMA_Streamx, DMA_FLAG_TCIF0);	 break;
    case DMA2_Stream1_BASE:DMA_ClearFlag(DMA_Streamx, DMA_FLAG_TCIF1);	 break;
    default:break;
    }
    //DMA_ClearFlag(DMA_Streamx, DMA_FLAG_TCIF5);						//清除传输完成中断
    //开启DMA错误和接收完成中断 +（使能接收完成中断是为了防止一次性接收过长数据）
    DMA_ITConfig(DMA_Streamx, DMA_IT_TE | DMA_IT_TC, ENABLE);
    //NVIC_Configuration(2, 2);										//NVIC 配置

    DMA_Cmd(DMA_Streamx, ENABLE);									//使能DMA
}

void UART::DMA_TX_Config(DMA_Stream_TypeDef* DMA_Streamx, u32 chx, u32 par, u32 mar, u16 ndtr)
{
    //没写
}

extern "C" void USART1_IRQHandler(void)
{
    if (uart1.UART_IRQHandler)
    {
        uart1.receive();
        uart1.UART_IRQHandler(uart1.p_use);
    }
}
extern "C" void USART2_IRQHandler(void)
{
    if (uart2.UART_IRQHandler)
    {
        uart2.receive();
        uart2.UART_IRQHandler(uart2.p_use);
    }
}
extern "C" void USART3_IRQHandler(void)
{
    if (uart3.UART_IRQHandler)
    {
        uart3.receive();
        uart3.UART_IRQHandler(uart3.p_use);
    }
}
extern "C" void UART4_IRQHandler(void)
{
    if (uart4.UART_IRQHandler)
    {
        uart4.receive();
        uart4.UART_IRQHandler(uart4.p_use);

    }
}
extern "C" void UART5_IRQHandler(void)
{
    if (uart5.UART_IRQHandler)
    {
        uart5.receive();
        uart5.UART_IRQHandler(uart5.p_use);
    }
}
extern "C" void USART6_IRQHandler(void)
{
    if (uart6.UART_IRQHandler)
    {
        uart6.receive();
        uart6.UART_IRQHandler(uart6.p_use);
    }
}
