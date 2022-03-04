/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
	* @author         : veiko.c
  ******************************************************************************
  * @attention
  * EXTI����STOP����˵��:
	* 1. PC7���Ž�ʾ����,����MCU_TX=>PD6   MCU_RX_PA3 ������115200
	* 2. ��¼�����Ĭ�ϳ�������������״̬,ͨ��������MCU����'E'ʹMCU����STOPģʽ,PC7
	*    ֹͣ��ת,����Ϊ�ߵ�ƽ
	* 3. ������PB4���ڻ���(�����ӵ�����������,���°������ŵ�ƽ�ɵͱ��)
	* 4. ������ѳɹ�,PC7��ָ���ת,�ȴ���һ�δ��ڽ��յ�'E'�ٽ���STOPģʽ
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "hk32f030m.h"
#include "hk32f030m_gpio.h"
#include "usart.h"
#include "string.h"
#include "mcu.h"
#include "hk32f030m_exti.h"

static void ledGpioInit(void);
static void ledGpioToggle(void);
static void led_off(void);
static void led_on(void);
static void softWareDelay(void);
static void ExtiConfigurature(void);

uint8_t sysTickIntFlag = 0;
char dataGet;

int main(void)
{
	ledGpioInit();
	USART_Configurature();
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
	Systick_Init();
	printf("this is a test!\r\n"); 
	MCO_Configurature();
	ExtiConfigurature();

	led_off();

  while (1)
  {		
		if(dataGet == 'E')
		{
			dataGet = 0;
			led_off();
			PWR_EnterStopMode(PWR_Regulator_LowPower, PWR_Entry_WFE);
		}
		else
		{
			ledGpioToggle();
		}
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
static void led_off(void)
{
	GPIO_SetBits(GPIOC, GPIO_Pin_7);
}
static void led_on(void)
{
	GPIO_ResetBits(GPIOC, GPIO_Pin_7);
}
static void softWareDelay(void)
{
	uint16_t i;
	uint16_t j;
	
	for(i=0;i<500;i++)
	{
		for(j=0;j<1000;j++)
		{
			__nop();
		}
	}
}
static void ExtiConfigurature(void)
{
	GPIO_InitTypeDef m_gpio;
	EXTI_InitTypeDef m_exti;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	
	m_gpio.GPIO_Mode = GPIO_Mode_IN;
	m_gpio.GPIO_OType = GPIO_OType_PP;
	m_gpio.GPIO_Pin = GPIO_Pin_4;
	m_gpio.GPIO_PuPd = GPIO_PuPd_NOPULL;
	m_gpio.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOB, &m_gpio);
	
  m_exti.EXTI_Line = EXTI_Line4;              
	m_exti.EXTI_Mode = EXTI_Mode_Event;      
	m_exti.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	m_exti.EXTI_LineCmd = ENABLE;
	EXTI_Init(&m_exti);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB,EXTI_PinSource4);
	EXTI_ClearITPendingBit(EXTI_Line4);
	
//	NVIC_SetPriority(EXTI4_IRQn,0);
//	NVIC_EnableIRQ(EXTI4_IRQn);
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


