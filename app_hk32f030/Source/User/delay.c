#include "delay.h"
#include "hk32f0xx.h"

static int8_t fac_us = 0;
static int16_t fac_ms = 0;

/*******************************************************************************
*                           @2017-12-16
* Function Name  : delay_init
* Description    : ��ʱ������ʼ��
* Input          : none
* Output         : none
* Return         : none
*                  SYSTICK��ʱ�ӹ̶�ΪHCLKʱ�ӵ�1/8
*                  SYSCLK:ϵͳʱ��
*******************************************************************************/
void delay_init(void)
{
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
    fac_us = SystemCoreClock/8000000;
    fac_ms = (unsigned int)fac_us*1000;
}

/*******************************************************************************
*                           @2017-12-16
* Function Name  : delay_us
* Description    : us��ʱ����
* Input          : num--��ʱʱ����ֵ
* Output         : none
* Return         : none
*******************************************************************************/
void delay_us(uint32_t nus)
{
	uint32_t temp;	    	 
	SysTick->LOAD=nus*fac_us; //ʱ�����	  		 
	SysTick->VAL=0x00;        //��ռ�����
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;          //��ʼ����	 
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));//�ȴ�ʱ�䵽��   
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;       //�رռ�����
	SysTick->VAL =0X00;       //��ռ�����	  
}

/*******************************************************************************
*                           @2017-12-16
* Function Name  : delay_ms
* Description    : ��ʱnms����ʱ��
                  ע��nms�ķ�Χ
                  SysTick->LOADΪ24λ�Ĵ���,����,�����ʱΪ:
                  nms<=0xffffff*8*1000/SYSCLK
                  SYSCLK��λΪHz,nms��λΪms
                  ��32M������,nms<=932 
* Input          : 
* Output         : 
* Return         : 
*******************************************************************************/
void delay_ms(uint16_t nms)
{	 		  	  
	uint32_t temp;		   
	SysTick->LOAD=(uint32_t)nms*fac_ms;//ʱ�����(SysTick->LOADΪ24bit)
	SysTick->VAL =0x00;           //��ռ�����
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;          //��ʼ����  
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));//�ȴ�ʱ�䵽��   
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;       //�رռ�����
	SysTick->VAL =0X00;       //��ռ�����	  	    
} 



























