/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  * 如果根据该工程作为参考改写的进入STOP模式的程序忘记添加唤醒后段导致下载程序后
	* 无法再次连接芯片,或以尝试按住复位键(维持芯片的第4个引脚为低),然后给芯片上电,
	* 再连接Debug点击下载开始后读到芯片ID后松开复位按键就可以实现芯片内固件的更新
	*
	* 正常的测试现象: 
	* 程序烧录并运行后,PC7引脚周期性翻转
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
	
	// borice配置ADC唤醒
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_BEEPER, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOD, ENABLE);   // 准备用PD6作为ADC采集引脚
	
	GPIOD->MODER |= GPIO_MODER_MODER6;       // PD6引脚配置为模拟模式 
	
	ADC1->CR2    |= ADC_CR2_WAKE_EN;
	ADC1->CHSELR = ADC_CHSELR_CHSEL1;        // AIN1 对应PD6引脚
	ADC1->CFGR1  |= ADC_CFGR1_AWDEN;         // 开启模拟看门狗
	ADC1->CCR    |= ADC_CCR_VREFEN;          // VREFINT通道开启
	ADC1->CFGR2  &= ~ADC_CFGR2_CKMODE;       // ADC采用异步时钟工作模式(要用于唤醒必须的操作)
	ADC1->CR     |= ADC_CR_ADEN;             // 使能ADC
	while((ADC1->ISR & ADC_ISR_ADRDY) == 0); // 等待ADC模块准备好
		
	// 打开LSI
	if((RCC->CSR & RCC_CSR_LSIRDY) != RCC_CSR_LSIRDY)
	{
		RCC_LSICmd(ENABLE); 
		while((RCC->CSR & RCC_CSR_LSIRDY) != RCC_CSR_LSIRDY);
	}
	
	// 配置BEEP 
	BEEP->CFGR = BEEP_CLOCK_LSI;                                          
	BEEP->CFGR |= BEEP_Prescaler_16 | BEEP_TRGO_Prescaler_64;
	while ((BEEP->CR & BEEP_BUSY_FLAG) == BEEP_BUSY_FLAG);      // 读忙标志(异步工作模式的外设操作)
	BEEP->CR |= BEEP_CR_EN | BEEP_CR_TRGO; 

	ADC1->TR = ((0x2f4 << 16) | 0x0100);                                // 配置LT(低压阀值)和HT(高压阀值)
	
	// 配置EXTI_Line8(连接ADC的AWD事件)
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


