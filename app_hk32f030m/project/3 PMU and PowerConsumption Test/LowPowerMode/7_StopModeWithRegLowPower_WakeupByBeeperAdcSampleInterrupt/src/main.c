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
	* ������¼�����к�,PC7���������Է�ת
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
#include "hk32f030m_beep.h"
#include "hk32f030m_adc.h"

uint32_t vbaten = 0 ;
uint32_t tsen   = 0 ;
uint32_t vrefen = 0 ;

static void ledGpioInit(void);
static void ledGpioToggle(void);

uint8_t sysTickIntFlag = 0;
char dataGet;

int main(void)
{
	EXTI_InitTypeDef m_exti1;
	
	// borice����ADC����
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_BEEPER, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOD, ENABLE);   // ׼����PD6��ΪADC�ɼ�����
	
	GPIOD->MODER |= GPIO_MODER_MODER6;       // PD6��������Ϊģ��ģʽ 
	
	ADC1->CR2    |= ADC_CR2_WAKE_EN;
	ADC1->CHSELR = ADC_CHSELR_CHSEL1;        // AIN1 ��ӦPD6����
	ADC1->CFGR1  |= ADC_CFGR1_AWDEN;         // ����ģ�⿴�Ź�
	ADC1->CCR    |= ADC_CCR_VREFEN;          // VREFINTͨ������
	ADC1->CFGR2  &= ~ADC_CFGR2_CKMODE;       // ADC�����첽ʱ�ӹ���ģʽ(Ҫ���ڻ��ѱ���Ĳ���)
	ADC1->CR     |= ADC_CR_ADEN;             // ʹ��ADC
	while((ADC1->ISR & ADC_ISR_ADRDY) == 0); // �ȴ�ADCģ��׼����
		
	// ��LSI
	if((RCC->CSR & RCC_CSR_LSIRDY) != RCC_CSR_LSIRDY)
	{
		RCC_LSICmd(ENABLE); 
		while((RCC->CSR & RCC_CSR_LSIRDY) != RCC_CSR_LSIRDY);
	}
	
	// ����BEEP 
	BEEP->CFGR = BEEP_CLOCK_LSI;                                          
	BEEP->CFGR |= BEEP_Prescaler_16 | BEEP_TRGO_Prescaler_64;
	while ((BEEP->CR & BEEP_BUSY_FLAG) == BEEP_BUSY_FLAG);      // ��æ��־(�첽����ģʽ���������)
	BEEP->CR |= BEEP_CR_EN | BEEP_CR_TRGO; 

	ADC1->TR = ((0x2f4 << 16) | 0x0100);                                // ����LT(��ѹ��ֵ)��HT(��ѹ��ֵ)
	
	// ����EXTI_Line8(����ADC��AWD�¼�)
	m_exti1.EXTI_Line = EXTI_Line8;                                
	m_exti1.EXTI_Mode = EXTI_Mode_Interrupt;      
	m_exti1.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	m_exti1.EXTI_LineCmd = ENABLE;  
	EXTI_Init(&m_exti1);
	EXTI_ClearITPendingBit(EXTI_Line8);
	NVIC_EnableIRQ(ADC1_IRQn);
	ledGpioInit();
	
	while (1)
	{	
		PWR_EnterStopMode(PWR_Regulator_LowPower, PWR_Entry_WFI);
		ledGpioToggle();
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


