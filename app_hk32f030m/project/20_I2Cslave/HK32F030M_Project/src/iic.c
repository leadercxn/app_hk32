#include "iic.h"
#include "hk32f030m_i2c.h"
#include <stdio.h>
#include "usart.h"
#define sEE_FLAG_TIMEOUT         ((uint32_t)0x1000)
#define sEE_LONG_TIMEOUT         ((uint32_t)(10 * sEE_FLAG_TIMEOUT))
__IO uint32_t  sEETimeout = sEE_LONG_TIMEOUT;
void HKIIC_Init(void)
{
	I2C_InitTypeDef		I2C_InitStructure;
	GPIO_InitTypeDef	GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	//I2C时钟使能
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1,ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;	       //复用模式
	GPIO_InitStructure.GPIO_PuPd =  GPIO_PuPd_UP;// GPIO_PuPd_NOPULL
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOC,GPIO_PinSource5,GPIO_AF_0);//SDA
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource6,GPIO_AF_0);//SCL
		
	NVIC_InitStructure.NVIC_IRQChannel = I2C1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd  = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	I2C_ITConfig(I2C1,I2C_IT_TXI|I2C_IT_ERRI|I2C_IT_TCI|I2C_IT_STOPI|I2C_IT_NACKI|I2C_IT_ADDRI|I2C_IT_RXI,ENABLE);
	
	//IIC配置
	I2C_InitStructure.I2C_Timing=0x00210507;//0x00201D2B;
	I2C_InitStructure.I2C_AnalogFilter=I2C_AnalogFilter_Enable;
	I2C_InitStructure.I2C_DigitalFilter=0;
	I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;		//I2C模式
	I2C_InitStructure.I2C_OwnAddress1 =0xB0; //指定自己的地址为七位地址,和从器件不同即可
	I2C_InitStructure.I2C_Ack = I2C_Ack_Enable ;//启用应答	 
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;//七位地址模式

	I2C_Init(I2C1, &I2C_InitStructure);
//	I2C_AutoEndCmd(I2C1, ENABLE);
	/* 使能 I2C */
	I2C_Cmd(I2C1, ENABLE);  	
	//I2C_ClockTimeoutCmd( I2C1, ENABLE );//启用时钟超时检测
}


//IIC读取数据函数
void HKIIC_Read(uint8_t SalveAddr,uint8_t startaddr,uint8_t *buffer,uint8_t Length)
{
	uint8_t i;

	while(I2C_GetFlagStatus(I2C1,I2C_FLAG_BUSY));//检查总线是否繁忙
	I2C_TransferHandling(I2C1,SalveAddr,1,I2C_SoftEnd_Mode,I2C_Generate_Start_Write);
	
	while(I2C_GetFlagStatus(I2C1,I2C_FLAG_TXIS)==RESET);//检查TXDR寄存器是否为空
	
	I2C_SendData(I2C1, startaddr);//向总线发送从器件地址
	while(I2C_GetFlagStatus(I2C1,I2C_FLAG_TC)==RESET);//检查发送是否完成
	
	I2C_TransferHandling(I2C1,SalveAddr,Length,I2C_AutoEnd_Mode, I2C_Generate_Start_Read);//产生一个读的起始信号
	for(i=0;i<Length;i++)
	{
		while(I2C_GetFlagStatus(I2C1,I2C_FLAG_RXNE)==RESET);//等待接收完成
		
		buffer[i]=I2C_ReceiveData(I2C1);	
	}
	
	while(I2C_GetFlagStatus(I2C1,I2C_FLAG_STOPF)==RESET);//作为主机检测由外设产生的停止信号	
	I2C_ClearFlag(I2C1,I2C_FLAG_STOPF);
}


void HKIIC_Write(uint8_t SalveAddr,uint8_t startaddr,uint8_t *buffer, uint8_t Length)
{
	uint8_t i;
	while(I2C_GetFlagStatus(I2C1,I2C_FLAG_BUSY));
	
	I2C_TransferHandling(I2C1,SalveAddr,1,I2C_Reload_Mode,I2C_Generate_Start_Write);
	while(I2C_GetFlagStatus(I2C1,I2C_FLAG_TXIS)==RESET);//检查TXDR寄存器是否为空
	
	I2C_SendData(I2C1,startaddr);
	while(I2C_GetFlagStatus(I2C1,I2C_FLAG_TCR)==RESET);//该位在Reload=1时NBYTES个数数据发送完成后被置1，向NBYTES写入非0数值时被清0
	
	I2C_TransferHandling(I2C1,SalveAddr,Length,I2C_AutoEnd_Mode,I2C_No_StartStop);
	
	for(i=0;i<Length;i++)
	{
		while(I2C_GetFlagStatus(I2C1,I2C_FLAG_TXIS)==RESET);//等待发送寄存器为空
		
		I2C_SendData(I2C1,buffer[i]);	
	}
	
	while(I2C_GetFlagStatus(I2C1,I2C_FLAG_STOPF)==RESET);//作为主机检测由外设产生的停止信号
	
	I2C_ClearFlag(I2C1,I2C_FLAG_STOPF);
}

//void I2C1_IRQHandler()
//{
//	printf(" IN TO TXIS\r\n");
//}


