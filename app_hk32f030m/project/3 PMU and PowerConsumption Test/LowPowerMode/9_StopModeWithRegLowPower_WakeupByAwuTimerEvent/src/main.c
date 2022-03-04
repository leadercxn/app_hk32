/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  * ������ݸù�����Ϊ�ο���д�Ľ���STOPģʽ�ĳ���������ӻ��Ѻ�ε������س����
	* �޷��ٴ�����оƬ,���Գ��԰�ס��λ��(ά��оƬ�ĵ�4������Ϊ��),Ȼ���оƬ�ϵ�,
	* ������Debug������ؿ�ʼ�����оƬID���ɿ���λ�����Ϳ���ʵ��оƬ�ڹ̼��ĸ���
	*
	* �����Ĳ�������: 
	* ������¼�����к�,PC7���������Է�ת,�Ҹߵ�ƽʱ��ԶС�ڵ͵�ƽά��ʱ��
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "hk32f030m.h"
#include "hk32f030m_gpio.h"
#include "usart.h"
#include "string.h"
#include "mcu.h"
#include "hk32f030m_exti.h"
#include "hk32f030m_tim.h"
#include "hk32f030m_awu.h"

static void ledGpioInit(void);
static void ledGpioToggle(void);
static void softWareDelay(void);
static void AWU_Exti_Nvic_Configurature(void);
static void AWU_TimerConfigurature(void);

uint8_t sysTickIntFlag = 0;
char dataGet;

int main(void)
{
	AWU_TimerConfigurature();
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR,ENABLE);
	ledGpioInit();
  while (1)
  {		
		PWR_EnterStopMode(PWR_Regulator_LowPower, PWR_Entry_WFE);
		ledGpioToggle();
		softWareDelay();
  }
}

static void ledGpioInit(void)
{
	GPIO_InitTypeDef m_gpio;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
	
	m_gpio.GPIO_Mode = GPIO_Mode_OUT;
	m_gpio.GPIO_OType = GPIO_OType_PP;
	m_gpio.GPIO_Pin = GPIO_Pin_7;
	m_gpio.GPIO_PuPd = GPIO_PuPd_NOPULL;
	m_gpio.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOC, &m_gpio);
}

static void ledGpioToggle(void)
{
	GPIOC->ODR ^= GPIO_Pin_7;
}
static void softWareDelay(void)
{
	uint16_t i;
	uint16_t j;
	
	for(i=0;i<100;i++)
	{
		for(j=0;j<50;j++)
		{
			__NOP();
		}
	}
}
static void AWU_Exti_Nvic_Configurature(void)
{
	EXTI_InitTypeDef m_exti;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	
  m_exti.EXTI_Line = EXTI_Line11;              
	m_exti.EXTI_Mode = EXTI_Mode_Event;      
	m_exti.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	m_exti.EXTI_LineCmd = ENABLE;
	EXTI_Init(&m_exti);
	EXTI_ClearITPendingBit(EXTI_Line11);
	
//	NVIC_SetPriority(EXTI11_IRQn,0);
//	NVIC_EnableIRQ(EXTI11_IRQn);
}
static void AWU_TimerConfigurature(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_AWU, ENABLE);
	
	if(RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == 0)
	{
		RCC_LSICmd(ENABLE);
		while(RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == 0);
	}
	AWU_CLKConfig(AWU_CLK_LSI128);
	
	AWU_Exti_Nvic_Configurature();
	
	while(0 == AWU_TimerCounterAndStart(0xff));
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
}
#endif /* USE_FULL_ASSERT */


