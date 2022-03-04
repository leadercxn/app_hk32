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
	
	//I2Cʱ��ʹ��
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1,ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;	       //����ģʽ
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
	
	//IIC����
	I2C_InitStructure.I2C_Timing=0x00210507;//0x00201D2B;
	I2C_InitStructure.I2C_AnalogFilter=I2C_AnalogFilter_Enable;
	I2C_InitStructure.I2C_DigitalFilter=0;
	I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;		//I2Cģʽ
	I2C_InitStructure.I2C_OwnAddress1 =0xB0; //ָ���Լ��ĵ�ַΪ��λ��ַ,�ʹ�������ͬ����
	I2C_InitStructure.I2C_Ack = I2C_Ack_Enable ;//����Ӧ��	 
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;//��λ��ַģʽ

	I2C_Init(I2C1, &I2C_InitStructure);
//	I2C_AutoEndCmd(I2C1, ENABLE);
	/* ʹ�� I2C */
	I2C_Cmd(I2C1, ENABLE);  	
	//I2C_ClockTimeoutCmd( I2C1, ENABLE );//����ʱ�ӳ�ʱ���
}


//IIC��ȡ���ݺ���
void HKIIC_Read(uint8_t SalveAddr,uint8_t startaddr,uint8_t *buffer,uint8_t Length)
{
	uint8_t i;

	while(I2C_GetFlagStatus(I2C1,I2C_FLAG_BUSY));//��������Ƿ�æ
	I2C_TransferHandling(I2C1,SalveAddr,1,I2C_SoftEnd_Mode,I2C_Generate_Start_Write);
	
	while(I2C_GetFlagStatus(I2C1,I2C_FLAG_TXIS)==RESET);//���TXDR�Ĵ����Ƿ�Ϊ��
	
	I2C_SendData(I2C1, startaddr);//�����߷��ʹ�������ַ
	while(I2C_GetFlagStatus(I2C1,I2C_FLAG_TC)==RESET);//��鷢���Ƿ����
	
	I2C_TransferHandling(I2C1,SalveAddr,Length,I2C_AutoEnd_Mode, I2C_Generate_Start_Read);//����һ��������ʼ�ź�
	for(i=0;i<Length;i++)
	{
		while(I2C_GetFlagStatus(I2C1,I2C_FLAG_RXNE)==RESET);//�ȴ��������
		
		buffer[i]=I2C_ReceiveData(I2C1);	
	}
	
	while(I2C_GetFlagStatus(I2C1,I2C_FLAG_STOPF)==RESET);//��Ϊ������������������ֹͣ�ź�	
	I2C_ClearFlag(I2C1,I2C_FLAG_STOPF);
}


void HKIIC_Write(uint8_t SalveAddr,uint8_t startaddr,uint8_t *buffer, uint8_t Length)
{
	uint8_t i;
	while(I2C_GetFlagStatus(I2C1,I2C_FLAG_BUSY));
	
	I2C_TransferHandling(I2C1,SalveAddr,1,I2C_Reload_Mode,I2C_Generate_Start_Write);
	while(I2C_GetFlagStatus(I2C1,I2C_FLAG_TXIS)==RESET);//���TXDR�Ĵ����Ƿ�Ϊ��
	
	I2C_SendData(I2C1,startaddr);
	while(I2C_GetFlagStatus(I2C1,I2C_FLAG_TCR)==RESET);//��λ��Reload=1ʱNBYTES�������ݷ�����ɺ���1����NBYTESд���0��ֵʱ����0
	
	I2C_TransferHandling(I2C1,SalveAddr,Length,I2C_AutoEnd_Mode,I2C_No_StartStop);
	
	for(i=0;i<Length;i++)
	{
		while(I2C_GetFlagStatus(I2C1,I2C_FLAG_TXIS)==RESET);//�ȴ����ͼĴ���Ϊ��
		
		I2C_SendData(I2C1,buffer[i]);	
	}
	
	while(I2C_GetFlagStatus(I2C1,I2C_FLAG_STOPF)==RESET);//��Ϊ������������������ֹͣ�ź�
	
	I2C_ClearFlag(I2C1,I2C_FLAG_STOPF);
}

//void I2C1_IRQHandler()
//{
//	printf(" IN TO TXIS\r\n");
//}


