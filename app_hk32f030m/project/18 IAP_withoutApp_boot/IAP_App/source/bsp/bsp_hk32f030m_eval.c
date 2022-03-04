/*
********************************************************************************
** @file    : hk32s003_eval.c
** @author  : 
** @version : v0.0.1
** @date    : 2020-02-04
** @brief   : This file provides firmware functions to manage Leds, push-buttons, 
**            COM ports, sFLASH(on SPI), and eeprom(on IIC)  hardware resources
********************************************************************************
*/
  
/*==============================================================================
** Includes
==============================================================================*/
#include "hk32f030m.h"
#include "bsp_hk32f030m_eval.h"

/*==============================================================================
** Private typedef
==============================================================================*/

/*==============================================================================
** Private macro
==============================================================================*/

/*==============================================================================
** Private define
==============================================================================*/

/*==============================================================================
** Private variables
==============================================================================*/
/* GPIO configurations */
GPIO_TypeDef* GPIO_PORT[GPIOn]              = {GPIO_LED1_PORT, 
                                               GPIO_LED2_PORT, 
                                               GPIO_LED3_PORT,
								                               GPIO_LED4_PORT};
								 
const uint16_t GPIO_PIN[GPIOn]              = {GPIO_LED1_PIN, 
                                               GPIO_LED2_PIN,
								                               GPIO_LED3_PIN,
								                               GPIO_LED4_PIN};
								 
const uint32_t GPIO_CLK[GPIOn]              = {GPIO_LED1_CLK, 
                                               GPIO_LED2_CLK,
								                               GPIO_LED3_CLK,
								                               GPIO_LED4_CLK};

const GPIOMode_TypeDef GPIO_MODE[GPIOn]     = {GPIO_LED1_MODE,
																	             GPIO_LED2_MODE,
                                               GPIO_LED3_MODE,
                                               GPIO_LED4_MODE};

const GPIOSpeed_TypeDef GPIO_SPEED[GPIOn]   = {GPIO_LED1_SPEED,
								                               GPIO_LED2_SPEED,
                                               GPIO_LED3_SPEED,
                                               GPIO_LED4_SPEED};
								   
const GPIOOType_TypeDef GPIO_OTYPE[GPIOn]   = {GPIO_LED1_OTYPE,
								                               GPIO_LED2_OTYPE,
                                               GPIO_LED3_OTYPE,
                                               GPIO_LED4_OTYPE};

const GPIOPuPd_TypeDef GPIO_PUPD[GPIOn]     = {GPIO_LED1_PUPD,
								                               GPIO_LED2_PUPD,
                                               GPIO_LED3_PUPD,
                                               GPIO_LED4_PUPD};													 

const GPIOSchmit_TypeDef GPIO_SCHMIT[GPIOn] = {GPIO_LED1_SCHMIT,
								                               GPIO_LED2_SCHMIT,
                                               GPIO_LED3_SCHMIT,
                                               GPIO_LED4_SCHMIT};	

const Gpio_State GPIO_STATE[GPIOn]          = {GPIO_LED1_INITSTATE,
								                               GPIO_LED2_INITSTATE,
                                               GPIO_LED3_INITSTATE,
                                               GPIO_LED4_INITSTATE};

/* KEY configurations */
GPIO_TypeDef* KEY_PORT[KEYn]                = {KEY1UP_GPIO_PORT, 
									                             KEY2DOWN_GPIO_PORT, 
                                               KEY3WKUP_GPIO_PORT}; 

const uint16_t KEY_PIN[KEYn]                = {KEY1UP_PIN, 
									                             KEY2DOWN_PIN, 
                                               KEY3WKUP_PIN}; 

const uint32_t KEY_CLK[KEYn]                = {KEY1UP_GPIO_CLK,
									                             KEY2DOWN_GPIO_CLK, 
                                               KEY3WKUP_GPIO_CLK};

const uint16_t KEY_EXTI_LINE[KEYn]          = {KEY1UP_EXTI_LINE, 
                                               KEY2DOWN_EXTI_LINE,
                                               KEY3WKUP_EXTI_LINE};

const uint8_t KEY_PORT_SOURCE[KEYn]         = {KEY1UP_EXTI_PORT_SOURCE, 
                                               KEY2DOWN_EXTI_PORT_SOURCE,
                                               KEY3WKUP_EXTI_PORT_SOURCE};
								 
const uint8_t KEY_PIN_SOURCE[KEYn]          = {KEY1UP_EXTI_PIN_SOURCE, 
                                               KEY2DOWN_EXTI_PIN_SOURCE,
                                               KEY3WKUP_EXTI_PIN_SOURCE}; 

const uint8_t KEY_IRQn[KEYn]                = {KEY1UP_EXTI_IRQn,
									                             KEY2DOWN_EXTI_IRQn, 
                                               KEY3WKUP_EXTI_IRQn};																							 
																

/*==============================================================================
** Private function prototypes
==============================================================================*/


/******************************************************************************/
/*                          Function Implementation                           */
/******************************************************************************/
/*******************************************************************************
** @function : BSP_GPIO_Init
** @brief    : Initializes GPIO 
** @param    : Gpio - Specifies the GPIO to be initialized																
** @retval   : None
*******************************************************************************/
void BSP_GPIO_Init(Gpio_TypeDef Gpio)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
  
  /* Enable GPIO clock */
  RCC_AHBPeriphClockCmd(GPIO_CLK[Gpio], ENABLE);

  /* Configure and initialize GPIO */
  GPIO_InitStructure.GPIO_Pin = GPIO_PIN[Gpio];
  GPIO_InitStructure.GPIO_Mode = GPIO_MODE[Gpio];
  GPIO_InitStructure.GPIO_Speed = GPIO_SPEED[Gpio];
  GPIO_InitStructure.GPIO_OType = GPIO_OTYPE[Gpio];
  GPIO_InitStructure.GPIO_PuPd = GPIO_PUPD[Gpio];
	GPIO_InitStructure.GPIO_Schmit = GPIO_SCHMIT[Gpio];
  GPIO_Init(GPIO_PORT[Gpio], &GPIO_InitStructure);
  
  /* Set GPIO initial state */
  if (GPIO_MODE[Gpio] == GPIO_Mode_OUT)
  {
	  if (GPIO_STATE[Gpio] == LOW)
	  {
			/* Set GPIO initial state to LOW */
	    GPIO_PORT[Gpio]->BRR |= GPIO_PIN[Gpio];
	  }
	  else
	  {
			/* Set GPIO initial state to HIGH */
	    GPIO_PORT[Gpio]->BSRR |= GPIO_PIN[Gpio];
	  }
  }
}


/*******************************************************************************
** @function : BSP_GPIO_SetHigh
** @brief    : Set GPIO to high level 
** @param    : Gpio - Specifies the GPIO to be set																
** @retval   : None
*******************************************************************************/
void BSP_GPIO_SetHigh(Gpio_TypeDef Gpio)
{
	GPIO_PORT[Gpio]->BSRR |= GPIO_PIN[Gpio];
}


/*******************************************************************************
** @function : BSP_GPIO_SetLow
** @brief    : Set GPIO to low level 
** @param    : Gpio - Specifies the GPIO to be set																
** @retval   : None
*******************************************************************************/
void BSP_GPIO_SetLow(Gpio_TypeDef Gpio)
{
	GPIO_PORT[Gpio]->BRR |= GPIO_PIN[Gpio];
}


/*******************************************************************************
** @function : BSP_GPIO_Toggle
** @brief    : Toggle GPIO 
** @param    : Gpio - Specifies the GPIO to be toggled																
** @retval   : None
*******************************************************************************/
void BSP_GPIO_Toggle(Gpio_TypeDef Gpio)
{
	GPIO_PORT[Gpio]->ODR ^= GPIO_PIN[Gpio];
}


/*******************************************************************************
** @function : BSP_LED_Init
** @brief    : Initializes LED 
** @param    : Led - Specifies the LED to be initialized																
** @retval   : None
*******************************************************************************/
void BSP_LED_Init(Gpio_TypeDef Led)
{
	 BSP_GPIO_Init(Led);
}


/*******************************************************************************
** @function : BSP_LED_TurnOn
** @brief    : Turns on LED 
** @param    : Led - Specifies the LED to be turned on																
** @retval   : None
*******************************************************************************/
void BSP_LED_TurnOn(Gpio_TypeDef Led)
{
	BSP_GPIO_SetLow(Led);
}


/*******************************************************************************
** @function : BSP_LED_TurnOff
** @brief    : Turns off LED 
** @param    : Led - Specifies the LED to be turned off																
** @retval   : None
*******************************************************************************/
void BSP_LED_TurnOff(Gpio_TypeDef Led)
{
	BSP_GPIO_SetHigh(Led);
}


/*******************************************************************************
** @function : BSP_LED_Toggle
** @brief    : Toggles LED 
** @param    : Led - Specifies the LED to be toggled																
** @retval   : None
*******************************************************************************/
void BSP_LED_Toggle(Gpio_TypeDef Led)
{
	BSP_GPIO_Toggle(Led);
}


/*******************************************************************************
** @function : BSP_KEY_Init
** @brief    : Initializes Key 
** @param    : Key - Specifies the KEY to be initialized
**             KeyMode - Specifies the key mode
** @retval   : None
*******************************************************************************/
void BSP_KEY_Init(Key_TypeDef Key, KeyMode_TypeDef KeyMode)
{
	GPIO_InitTypeDef GPIO_InitStructure;
  EXTI_InitTypeDef EXTI_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;

  /* Enable the Key Clock */
  RCC_AHBPeriphClockCmd(KEY_CLK[Key], ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

  /* Configure Key pin as input */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Pin = KEY_PIN[Key];
  GPIO_Init(KEY_PORT[Key], &GPIO_InitStructure);

  if (KeyMode == KEY_MODE_EXTI)
  {
    /* Connect Key EXTI Line to Key GPIO Pin */
    SYSCFG_EXTILineConfig(KEY_PORT_SOURCE[Key], KEY_PIN_SOURCE[Key]);

    /* Configure Key EXTI line */
    EXTI_InitStructure.EXTI_Line = KEY_EXTI_LINE[Key];
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);

    /* Enable and set Key EXTI Interrupt to the lowest priority */
    NVIC_InitStructure.NVIC_IRQChannel = KEY_IRQn[Key];
    NVIC_InitStructure.NVIC_IRQChannelPriority = 0x03;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

    NVIC_Init(&NVIC_InitStructure);
		EXTI_ClearFlag(KEY_EXTI_LINE[Key]);
  }
}


/*******************************************************************************
** @function : BSP_KEY_GetKeyState
** @brief    : Returns the selected key state 
** @param    : Key - Specifies the KEY to be check 
** @retval   : 0 - KEY_OFF
**             1 - KEY_ON
*******************************************************************************/
KeyState_TypeDef BSP_KEY_GetKeyState(Key_TypeDef Key)
{
	if(GPIO_ReadInputDataBit(KEY_PORT[Key], KEY_PIN[Key]) == 0)
	{
		/* Wait for Key released */
		while (GPIO_ReadInputDataBit(KEY_PORT[Key], KEY_PIN[Key]) == 1);
		return KEY_ON;
	}
	  
	return KEY_OFF;
}


/*******************************************************************************
** @function : BSP_BEEP_Init
** @brief    : Initializes BEEP 
** @param    : Freq - Only 1KHz, 2KHz, 4KHz, 8KHz															
** @retval   : None
*******************************************************************************/
void BSP_BEEP_Init(BeepFreq_t Freq)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	BEEP_InitTypeDef  BEEP_InitStructure;
  
  /* Enable GPIO clock */
  RCC_AHBPeriphClockCmd(BEEP_GPIO_CLK, ENABLE);
	
	/* Enable BEEP clock */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_BEEPER, ENABLE);
	
	/* Configure BEEP GPIO */
	GPIO_InitStructure.GPIO_Pin = BEEP_GPIO_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(BEEP_GPIO_PORT, &GPIO_InitStructure);
	
	GPIO_PinAFConfig(BEEP_GPIO_PORT, BEEP_GPIO_SOURCE, BEEP_GPIO_AF);
	
	/* Configure BEEPER */
	BEEP_InitStructure.BEEP_Clock = BEEP_CLOCK_LSI;
	BEEP_InitStructure.BEEP_Prescaler = Freq;
	BEEP_Init(&BEEP_InitStructure);
	
	/* Enable Beep */
	BEEP_Cmd(ENABLE);
}


/*******************************************************************************
** @function : BSP_BEEP_SetFreq
** @brief    : Set beeper outputing frequency 
** @param    : Freq - Only 1KHz, 2KHz, 4KHz, 8KHz														
** @retval   : None
*******************************************************************************/
void BSP_BEEP_SetFreq(BeepFreq_t Freq)
{
	while (BEEP_ReadBeepStatus() != RESET) {};
	BEEP_SetPrescaler(Freq);
}


/*******************************************************************************
** @function : BSP_BEEP_TurnOff
** @brief    : Turns off Beeper
** @param    : None														
** @retval   : None
*******************************************************************************/
void BSP_BEEP_TurnOff(Gpio_State Output)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	/* Beep deinitialization */
	BEEP_DeInit();
	
	/* Reconfigure GPIO */
	GPIO_InitStructure.GPIO_Pin = BEEP_GPIO_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(BEEP_GPIO_PORT, &GPIO_InitStructure);
	
	/* Set GPIO leve after turning off the beeper */
	if (Output == HIGH)
	{
	  GPIO_SetBits(BEEP_GPIO_PORT, BEEP_GPIO_PIN);
	}
	else
	{
		GPIO_ResetBits(BEEP_GPIO_PORT, BEEP_GPIO_PIN);
	}
}


/*********************************** EOF **************************************/
