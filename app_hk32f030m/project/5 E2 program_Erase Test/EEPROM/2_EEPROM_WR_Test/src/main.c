/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  * EEPROM测试项记录:
	* 1. 反复对EEPROM进行擦除, 写, 读校验操作在高低温及不同电压下进行测试看串口打印输出
	* 2. 串口波特率:115200
	* 3. 串口引脚   PD6作为MCU_TX    PA3作为MCU_RX
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "hk32f030m.h"
#include "hk32f030m_gpio.h"
#include "usart.h"
#include "string.h"
#include "eeprom.h"

#define EEPROM_INIT_FLAG    0x3a

static void ledGpioInit(void);
static void ledGpioToggle(void);
static void softWareDelay(void);

uint32_t EraseCnt = 0;
uint8_t  errorFlag  = 0;
volatile const uint8_t  a[5] = {0xFF,0xFF,0xFF,0xFF,0xFF};
volatile const uint16_t  b[5] = {0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF};
volatile  const uint32_t  c[5] = {0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF};

int main(void)
  /* Infinite loop */
{
	uint16_t i;
	uint8_t  eeprom_init_flag;
	uint8_t  data_ee;
	uint8_t  read_data;
	
	ledGpioInit();
	USART_Configurature();
	printf("******************************\r\n");
	printf("**** this is a test for eeprom!\r\n");
	printf("**** author: veiko.c\r\n");
	printf("**** date: 20200204\r\n");
	printf("******************************\r\n\r\n");
	while((EraseCnt <= 0xfffffffeul) && (errorFlag == 0))
	{
		if((EraseCnt%2)!=0)
		{
      
			data_ee = 0x55;
		}
		else
		{
			data_ee = 0xFF;
		}
		printf("eeprom erase cnt = %u, and will write all-0x%02X to eeprom!\r\n",EraseCnt,data_ee);
		
		for(i=0;i<HK32F030M_EE_SIZE;i++)
		{
			if(1 != EEPROM_WriteByte(i,data_ee))
			{
				errorFlag = 1;
				printf("  write error and the offset address is: %d!\r\n",i);
				break;
			}
		}
		
		if(errorFlag == 0)
		{
			printf("  erase and write done!\r\n");
		}
		if(errorFlag == 0)
		{
			for(i=0;i<HK32F030M_EE_SIZE;i++)
			{
				if(1 != EEPROM_ReadByte(i,&read_data))
				{
					errorFlag = 1;
				}
				
				if(read_data != data_ee)
				{
					errorFlag = 1;
				}
				
				if(errorFlag == 1)
				{
					printf("  read check error and the offset address is: %d, the data is: %0x02x!\r\n",i,read_data);
					break;
				}
			}
		}
		
		if(errorFlag == 0)
		{
			printf("  read check pass!\r\n");
		}
		
		EraseCnt++;
		ledGpioToggle();
	}
	
	while(1);
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
	
	for(i=0;i<500;i++)
	{
		for(j=0;j<1000;j++)
		{
			__nop();
		}
	}
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


