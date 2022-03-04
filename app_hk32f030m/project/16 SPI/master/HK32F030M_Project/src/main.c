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
#include "hk32f030m.h"
#include "usart.h"
#include "hk32f030m_gpio.h"
 
 
uint8_t dataE2_tx[10]={0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,0xa};
uint8_t dataE2_rx[10];
static void SPI_Config(void);
static uint16_t SPI_WR_Buffer(uint8_t *wBuffer, uint8_t *rBuffer, uint16_t len)
{
	uint16_t timeOutCnt = 0;
	uint16_t i = 0;
	
	while(1)
	{
		if(i == len)
		{
			return i;
		}
		
		timeOutCnt = 0xffff;
		while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE ) == RESET)
		{
			timeOutCnt--;
			if(timeOutCnt == 0)
			{
				return 0;
			}
		}
		
		if(wBuffer != 0)
		{
			SPI_SendData8(SPI1, *(wBuffer+(i)));
		}
		else
		{
			SPI_SendData8(SPI1, 0x00);
		}
		
		timeOutCnt = 0xffff;
		while( SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE ) == RESET )
		{
			timeOutCnt--;
			if( timeOutCnt == 0 )
			{
				return 0;
			}
		}
		
		if(rBuffer != 0)
		{
			*(rBuffer + i) = SPI_ReceiveData8(SPI1);
		}
		else
		{
			SPI_ReceiveData8(SPI1);
		}
		i++;		
	}
}

uint8_t SPI_ReadID(uint8_t *IDBuff)
{
	uint8_t cmd_data[1] = {0x9F};

//	SPI_CS_Ctr(0);	
	if(1 != SPI_WR_Buffer(cmd_data,0,1))
	{
//		SPI_CS_Ctr(1);
		return 0;
	}
	if(3 == SPI_WR_Buffer(0,IDBuff,3))
	{
//		SPI_CS_Ctr(1);
		return 1;
	}
	
//	SPI_CS_Ctr(1);
	return 0;
}

int main(void)
  /* Infinite loop */
{
	uint32_t k = 0;
	USART_Configurature();
	SPI_Config();
	
	while (1)
	{	
		if( 1 == SPI_ReadID(dataE2_rx))
		{
			printf("dev ID: %02X-%02X-%02X\r\n", dataE2_rx[0], dataE2_rx[1], dataE2_rx[2]);
		}
		else
		{
			printf("dev IDªÒ»° ß∞‹!\r\n");
		}	
		/* Waiting until TX FIFO is empty */
		while (SPI_GetTransmissionFIFOStatus(SPI1) != SPI_TransmissionFIFOStatus_Empty)
		{}    

		/* Wait busy flag */
		while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET)
		{}

//		/* Disable the Tx buffer empty interrupt */
//		SPI_I2S_ITConfig(SPI1, SPI_I2S_IT_TXE, DISABLE);

		/* Waiting until RX FIFO is empty */
		while (SPI_GetReceptionFIFOStatus(SPI1) != SPI_ReceptionFIFOStatus_Empty)
		{} 
		for(k=0;k<1000000;k++);
	}
}

static void SPI_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
  	SPI_InitTypeDef SPI_InitStructure;
	/* Enable the SPI periph */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
  
	/* Enable SCK, MOSI, MISO and NSS GPIO clocks */
	SPI_CS_CLK_EN();
	SPI_MISO_CLK_EN();
	SPI_MOSI_CLK_EN();
	SPI_CLK_CLK_EN();
	/* config the CS PIN */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_Pin = SPI_CS_Pin;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(SPI_CS_PORT, &GPIO_InitStructure);
	GPIO_PinAFConfig(SPI_CS_PORT, SPI_CS_PinSource, GPIO_AF_2);
	
	/* config the MOSI PIN */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Pin = SPI_MOSI_Pin;
	GPIO_Init(SPI_MOSI_PORT, &GPIO_InitStructure);
	GPIO_PinAFConfig(SPI_MOSI_PORT, SPI_MOSI_PinSource, GPIO_AF_2);
  	/* config the CLK PIN */
	GPIO_InitStructure.GPIO_Pin = SPI_CLK_Pin;
	GPIO_Init(SPI_CLK_PORT, &GPIO_InitStructure);
	GPIO_PinAFConfig(SPI_CLK_PORT, SPI_CLK_PinSource, GPIO_AF_2);
	
	/* config the MISO PIN */
	GPIO_InitStructure.GPIO_Pin = SPI_MISO_Pin;
	GPIO_Init(SPI_MISO_PORT, &GPIO_InitStructure);
	GPIO_PinAFConfig(SPI_MISO_PORT, SPI_MISO_PinSource, GPIO_AF_2);
  
  /* SPI configuration -------------------------------------------------------*/
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Hard;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	SPI_Init(SPI1, &SPI_InitStructure);
	/* Initialize the FIFO threshold */
	SPI_RxFIFOThresholdConfig(SPI1, SPI_RxFIFOThreshold_QF);
	SPI_NSSPulseModeCmd(SPI1, ENABLE);
	SPI_SSOutputCmd(SPI1, ENABLE);
	/* Enable the SPI peripheral */
	SPI_Cmd(SPI1, ENABLE);
	
//	/* Configure the SPI interrupt priority */
//	NVIC_InitStructure.NVIC_IRQChannel = SPI1_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPriority = 1;
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_InitStructure);
}


#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(char* file , uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */	
       /* Infinite loop */
	
	while (1)
  {		
  }
}
#endif /* USE_FULL_ASSERT */


