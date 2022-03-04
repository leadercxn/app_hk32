/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  * 程序功能为 对自定义地址进行字节读写
  ******************************************************************************

 Includes ------------------------------------------------------------------*/
#include "main.h"
#include "hk32f030m.h"
#include "hk32f030m_gpio.h"
#include "usart.h"
#include "string.h"

static void ledGpioInit(void);
static void ledGpioToggle(void);
static void softWareDelay(void);

#define FLASH_ADDRESS            						0x08001200
#define FLASH_SIZE										0xE00
#define PAGE_SIZE                      					0x00000080

#define FLASH_OP_ADDR									0x08001200 
typedef union
{
	uint32_t u32Data;
	uint8_t u8Data[4];
}DATABUF;

DATABUF DataBuf;
uint16_t Flash_addr = 0;

extern void FLASH_PageErase(uint32_t PageAddress);

void Erase_Flash(uint32_t FlashAddress)
{
	uint8_t status = 0;
	if((FlashAddress % PAGE_SIZE) == 0x00)
	{
		FLASH_Unlock();
		status = FLASH_ErasePage(FlashAddress);
		CLEAR_BIT(FLASH->CR, FLASH_CR_PER);
		FLASH_Lock();

		if(status == FLASH_COMPLETE )
		{
			printf("Flash_Erase ok ");
		}
		else
		{
			printf("Flash_Erase Fail ");
		}	
	}
}

void Write_Flash(uint32_t FlashAddress,uint8_t *WriteBuff,uint16_t Size)
{
	FLASH_Unlock();

	for(uint8_t j =0 ; j<Size ; j+=1)
	{
		FLASH_ProgramByte(FlashAddress + j, WriteBuff[j]);
	}

	FLASH_Lock();
}


uint32_t FlashRead(uint32_t Addr)
{
	 uint32_t Data;
	// uint16_t TempData[2];
	// TempData[0] = *(__IO uint16_t*)(Addr);
	// TempData[1] = *(__IO uint16_t*)(Addr+2);
	//Data = TempData[0] + (TempData[1]<<16);
	Data = *(__IO uint32_t*)(Addr);
	return Data;		
}

void Flash_WriteData(void)
{

	printf("Flash_offset:%03x ",Flash_addr);
	printf(",Flash_Erase:%08x ",FLASH_OP_ADDR + Flash_addr);
	Erase_Flash(FLASH_OP_ADDR+Flash_addr);

	printf(",Write Data:%d ",DataBuf.u32Data);
	Write_Flash(FLASH_OP_ADDR+Flash_addr,&DataBuf.u8Data[0],4);	
}

void Flash_ReadData(void)
{
	printf(",Read Flash Addr:%08x,Data:%d\r\n\r\n",FLASH_OP_ADDR+Flash_addr, FlashRead(FLASH_OP_ADDR+Flash_addr));
	Flash_addr += 0x04;//0x80 
	if(Flash_addr >= FLASH_SIZE)
	{
		Flash_addr = 0; 
	}
}


int main(void)
  /* Infinite loop */
{

	ledGpioInit();
	USART_Configurature();
	printf("Flash Program / Erase by Byte test\r\n");
	printf("Flash_addr:%08x\r\n",FLASH_OP_ADDR);
  while (1)
  {
		ledGpioToggle();
		softWareDelay();

		DataBuf.u32Data ++;
		Flash_WriteData();
		Flash_ReadData();
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


