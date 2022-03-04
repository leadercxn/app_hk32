/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  * 2_EEPROM_WR_Test里面的工程是用于高低温测试EEPROM擦除,读写的,会不断地
	擦除EEPROM然后再写入值,并读出校验,每次擦除前串口打印当前是第几次进行
	擦除操作,写入并读出校验后输出结果,有错误发生时停止继续擦除,读写操作,
	串口打印输出提示当前总共操作的次数和发生错误的第一个地址。
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "hk32f030m.h"
#include "hk32f030m_gpio.h"
#include "usart.h"
#include "string.h"
#include "eeprom.h"

#define EEPROM_INIT_FLAG    0x19

static void ledGpioInit(void);
static void ledGpioToggle(void);
static void softWareDelay(void);

int main(void)
  /* Infinite loop */
{
	uint16_t i;
	uint8_t  eeprom_init_flag;
	
	ledGpioInit();
	USART_Configurature();
	USART_SendStringLen((uint8_t *)"this is a Test!\r\n",strlen("this is a Test!\r\n"));
		
//	FLASH_Unlock();
//	EEPROM_EraseByte(HK32F0301M_EE_BEGIN +1);
//	FLASH_Lock();
	
	if(1 == EEPROM_ReadByte(0,&eeprom_init_flag))
	{
		if(EEPROM_INIT_FLAG == eeprom_init_flag)
		{
			printf("EEPROM init flag check: PASS!\r\n");
			printf("Data in EEPROM:\r\n");
			for(i=0;i<30;i++)
			{
				if(1 == EEPROM_ReadByte(i,&eeprom_init_flag))
				{
					printf("offset_address: %d, data: %d\r\n",i,eeprom_init_flag);
				}
			}
			for(i=0;i<30;i++)
			{
				if(1 == EEPROM_ReadByte(HK32F030M_EE_SIZE-i,&eeprom_init_flag))
				{
					printf("offset_address: %d, data: %d\r\n",HK32F030M_EE_SIZE-i,eeprom_init_flag);
				}
			}
		}
		else
		{
			printf("EEPROM need init...\r\n");
			if( 1== EEPROM_WriteByte(0,EEPROM_INIT_FLAG))
			{
				printf("EEPROM init flag write success!\r\n");
				
				for(i=0;i<30;i++)
				{
					if(0 == EEPROM_WriteByte(i,i))
					{
						printf("EEPROM data write fail!\r\n");
						break;
					}
				}
				if(i == 0)
				{
					for(i=0;i<30;i++)
					{
						if(0 == EEPROM_WriteByte(HK32F030M_EE_SIZE-i,i))
						{
							printf("EEPROM data write fail!\r\n");
						}
					}
				}
				if(i == 30)
				{
					printf("EEPROM data write success, please reset mcu to check!\r\n");
				}
				
			}
			else
			{
				printf("EEPROM init flag write fail!\r\n");
			}
		}
	}
	
  while (1)
  {
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
	
	for(i=0;i<500;i++)
	{
		for(j=0;j<1000;j++)
		{
			__NOP();
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


