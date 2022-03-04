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

#define USER_TIMEOUT 0xffff
int exit_interrupt_cnt = 0;

uint8_t TxBuffer[10] = {0x15,0xa1,0x88,0xff};
uint8_t RxBuffer[10];

static void softWareDelay(void);
static void MCO_Configurature(void);
static void SPI_Config(void);
__IO uint8_t Rx_Idx = 0x00;
__IO uint8_t Tx_Idx = 0x00;

__IO uint8_t CmdTransmitted = 0x00;
__IO uint8_t CmdReceived = 0x00;
__IO uint8_t CmdStatus = 0x00;
__IO uint32_t TimeOut = 0x0;


int main(void)
  /* Infinite loop */
{
	uint32_t k=0;
	Tx_Idx = 0x00;

	SPI_Config();
	while(1)
	{	
		Tx_Idx = 0x00;
		CmdReceived = 0x00;
		CmdStatus=0x0;
		
		SPI_SendData8(SPI1, 0x00);
		SPI_I2S_ITConfig(SPI1, SPI_I2S_IT_RXNE, ENABLE);
		SPI_I2S_ITConfig(SPI1, SPI_I2S_IT_TXE, ENABLE);
		while(Tx_Idx<SPI_DATA_LENS){}	
		SPI_I2S_ITConfig(SPI1, SPI_I2S_IT_TXE, DISABLE);
		for(k=0;k<100000;k++);
		SPI_Config();

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
	SPI_InitStructure.SPI_Mode = SPI_Mode_Slave;
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
	
	/* Enable the Rx buffer not empty interrupt */
//	SPI_I2S_ITConfig(SPI1, SPI_I2S_IT_RXNE, ENABLE);

	/* Enable the SPI Error interrupt */
//	SPI_I2S_ITConfig(SPI1, SPI_I2S_IT_ERR, ENABLE);	
	/* Enable the SPI peripheral */
	SPI_Cmd(SPI1, ENABLE);
	
	/* Configure the SPI interrupt priority */
	NVIC_InitStructure.NVIC_IRQChannel = SPI1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

static void MCO_Configurature(void)
{
	GPIO_InitTypeDef m_gpio; 
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);

	m_gpio.GPIO_Mode = GPIO_Mode_AF;
	m_gpio.GPIO_OType =  GPIO_OType_PP;
	m_gpio.GPIO_Pin = GPIO_Pin_7;
	m_gpio.GPIO_PuPd = GPIO_PuPd_NOPULL;
	m_gpio.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOC, &m_gpio);
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource7,GPIO_AF_5);
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_SPI1, ENABLE);
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_SPI1, DISABLE);	
	RCC_MCOConfig(RCC_MCOSource_SYSCLK, RCC_MCOPrescaler_1);
}

static void softWareDelay(void)
{
	uint16_t i;
	uint16_t j;
	
	for(i=0;i<800;i++)
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


