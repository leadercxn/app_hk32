/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "usart.h"
#include <stdio.h>
#include "iic.h"
#include "hk32f030m.h"

void delay(uint32_t i)
{
		while(i--);
}
#define I2C_REG_TEST_SIZE                        10
extern uint8_t I2C_REG_SEND_TEST[I2C_REG_TEST_SIZE];
extern uint8_t I2C_REG_RECEIVE_TEST[I2C_REG_TEST_SIZE];
extern uint8_t receive_data_lens;
extern uint8_t send_data_lens;

int main(void)
{
	uint8_t EEPROMAddr = 0xA0;
	uint8_t i=0;
//	uint8_t sendbuf[]="hello";
	uint8_t receivebuf[10]={0};
	
	HKUsart_Init();
	HKIIC_Init();
	while(1)
	{
		if(send_data_lens>0)
		{
			printf("\r\nsend:");
			for(i=0; i<send_data_lens; i++)
			{
				printf("\t0x%x ", I2C_REG_SEND_TEST[i]);
			}
			send_data_lens=0;
		}

		if(receive_data_lens>0)
		{
			printf("\r\nreceive:");
			for(i=0; i<receive_data_lens; i++)
			{
				printf("\t0x%x ", I2C_REG_RECEIVE_TEST[i]);
			}
			receive_data_lens=0;
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


