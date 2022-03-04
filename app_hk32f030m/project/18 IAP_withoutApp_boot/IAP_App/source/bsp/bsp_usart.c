/*
********************************************************************************
** @file    : bsp_usart.c
** @author  : Frank.Z
** @version : v0.0.1
** @date    : 2020-02-04
** @brief   :
********************************************************************************
*/

/*==============================================================================
** Includes
==============================================================================*/
#include "bsp_usart.h"

/*==============================================================================
** Private typedef
==============================================================================*/

/*==============================================================================
** Private macro
==============================================================================*/
#define USART1_IRQ_ENABLE             0

/*==============================================================================
** Private define
==============================================================================*/

/*==============================================================================
** Private variables
==============================================================================*/
USART_TypeDef* COM_USART[COMn]        = {COM1_USART};
const uint32_t COM_USART_CLK[COMn]    = {COM1_CLK};

GPIO_TypeDef* COM_TX_PORT[COMn]       = {COM1_TX_GPIO_PORT};
const uint16_t COM_TX_PIN[COMn]       = {COM1_TX_PIN};
const uint32_t COM_TX_PORT_CLK[COMn]  = {COM1_TX_GPIO_CLK};
const uint8_t COM_TX_PIN_SOURCE[COMn] = {COM1_TX_SOURCE};
const uint8_t COM_TX_AF[COMn]         = {COM1_TX_AF};

GPIO_TypeDef* COM_RX_PORT[COMn]       = {COM1_RX_GPIO_PORT};
const uint16_t COM_RX_PIN[COMn]       = {COM1_RX_PIN}; 
const uint32_t COM_RX_PORT_CLK[COMn]  = {COM1_RX_GPIO_CLK};
const uint8_t COM_RX_PIN_SOURCE[COMn] = {COM1_RX_SOURCE}; 
const uint8_t COM_RX_AF[COMn]         = {COM1_RX_AF};

/*==============================================================================
** Private function prototypes
==============================================================================*/
static void BSP_USART_ComInit(Com_TypeDef Com, USART_InitTypeDef* USART_InitStruct);


/******************************************************************************/
/*                          Function Implementation                           */
/******************************************************************************/
/*******************************************************************************
** @function : BSP_USART_Config
** @brief    : Configures USART  
** @param    : Com - Specifies the COM port to be configured 
**             Baud - Specifies the baud rate to the USART
** @retval   : None
*******************************************************************************/
void BSP_USART_Config(Com_TypeDef Com, uint32_t Baud)
{ 
  USART_InitTypeDef USART_InitStructure;
  
  USART_InitStructure.USART_BaudRate = Baud;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  
  BSP_USART_ComInit(Com, &USART_InitStructure);
}


/*******************************************************************************
** @function : BSP_USART_ComInit
** @brief    : Configures COM port  
** @param    : Com - Specifies the COM port to be configured
**             USART_InitStruct - Pointer to a USART_InitTypeDef structure that
**                                contains the configuration information for  
**                                the specified USART peripheral
** @retval   : None
*******************************************************************************/
static void BSP_USART_ComInit(Com_TypeDef Com, USART_InitTypeDef* USART_InitStruct)
{
	GPIO_InitTypeDef GPIO_InitStructure;

  /* Enable GPIO clock */
  RCC_AHBPeriphClockCmd(COM_TX_PORT_CLK[Com] | COM_RX_PORT_CLK[Com], ENABLE);

  /* Enable USART clock */
  RCC_APB2PeriphClockCmd(COM_USART_CLK[Com], ENABLE); 
  
  /* Configure USART Tx as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = COM_TX_PIN[Com];
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(COM_TX_PORT[Com], &GPIO_InitStructure);
    
  /* Configure USART Rx as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = COM_RX_PIN[Com];
  GPIO_Init(COM_RX_PORT[Com], &GPIO_InitStructure);
	
	/* Connect PXx to USARTx_Tx */
  GPIO_PinAFConfig(COM_TX_PORT[Com], COM_TX_PIN_SOURCE[Com], COM_TX_AF[Com]);

  /* Connect PXx to USARTx_Rx */
  GPIO_PinAFConfig(COM_RX_PORT[Com], COM_RX_PIN_SOURCE[Com], COM_RX_AF[Com]);

  /* USART configuration */
  USART_Init(COM_USART[Com], USART_InitStruct);
	
	#if USART1_IRQ_ENABLE
	/* Enable USART receive interrupt */
	USART_ITConfig(COM_USART[Com], USART_IT_RXNE, ENABLE);
	
	/* Enable USART Idle interrupt */
	USART_ITConfig(COM_USART[Com], USART_IT_IDLE, ENABLE);
	
	/* Set USART1 Interrupt Priority */
	NVIC_SetPriority(COM1_IRQn, 3);
	
	/* Enable USART1 interrupt */
	NVIC_EnableIRQ(COM1_IRQn);
	#endif
    
  /* Enable USART */
  USART_Cmd(COM_USART[Com], ENABLE);
}


/*******************************************************************************
** @function : BSP_USART_SendByte
** @brief    : Send one byte data 
** @param    : USARTx - Specifies the USART port
**             data - Data to be sent
** @retval   : None
*******************************************************************************/
void BSP_USART_SendByte(USART_TypeDef* USARTx, uint8_t Data)
{
	/* Loop until transmit data register is empty */
  while (USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET)
  {}
		
	/* Transmit a byte data to to USART */
	USART_SendData(USARTx, Data);
}	


/*******************************************************************************
** @function : BSP_USART_SendString
** @brief    : Send string from USART 
** @param    : USARTx - Specifies the USART port
**             str - pointer string to be sent
** @retval   : None
*******************************************************************************/
void BSP_USART_SendString(USART_TypeDef* USARTx, char* Str)
{
	do
	{
		BSP_USART_SendByte(USARTx, *Str);
		Str++;
	} while (*(Str) != '\0');
	
	/* Loop until transmit completely */
	while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET)
	{}
}


/*******************************************************************************
** @function : fputc
** @brief    : Retargets the C library printf function to the USART  
** @param    : None
** @retval   : None
*******************************************************************************/ 
int fputc(int ch, FILE *f)
{
	/* Place your implementation of fputc here */
  /* e.g. write a character to the USART */
  USART_SendData(COM_USART[COM1], (uint8_t)ch);

  /* Loop until transmit data register is empty */
  while (USART_GetFlagStatus(COM_USART[COM1], USART_FLAG_TXE) == RESET)
  {}

  return ch;
}

/*******************************************************************************
** @function : fgetc
** @brief    : Retargets the C library scanf function to the USART  
** @param    : None
** @retval   : None
*******************************************************************************/ 
int fgetc(FILE *f)
{
	/* Place your implementation of fgetc here */
  /* Loop until receive data register is not empty */
  while (USART_GetFlagStatus(COM_USART[COM1], USART_FLAG_RXNE) == RESET)
  {}

  return (int)USART_ReceiveData(COM_USART[COM1]);
}


/*********************************** EOF **************************************/
