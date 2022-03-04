/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *该工程旨在做复位功能测试，通过设置Option byte 的nRST_Stop位，MCU会在进入低功耗模式的stop mode之后复位，
  通过判断RCC->CSR可知MCU复位源
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "hk32f030m.h"
#include "hk32f030m_rcc.h"
#include "hk32f030m_wwdg.h" 
#include "hk32f030m_misc.h"
#include "hk32f030m_pwr.h"
#include "hk32f030m_flash.h"
#include "uart.h"

/*************************************************************
Function : Reset_Init
Description: 复位初始化
Input : none
return :
*************************************************************/
void Reset_Init(void)
{

    if(RCC_GetFlagStatus(RCC_FLAG_LPWRRST))//Lowpower复位 
    {
         printf("SystemRest by LowpowrRest ,Rcc_csr:0x%08X\r\n",RCC->CSR);
    }
		else if(RCC_GetFlagStatus(RCC_FLAG_PORRST) != RESET)//上电复位
		{	
			printf("SystemRest by power on rest ,Rcc_csr :0x%08X\r\n",RCC->CSR);       
		}
    else
    {
      /* code */
      printf("SystemRest by other Rest ,Rcc_csr:0x%08X\r\n",RCC->CSR);
    }
    
    
}

void flash_opt_prog(int addr, int data) {
  FLASH->CR |= 0x00000010 ;
  *((short *)(addr)) = data ;
  while( ( FLASH->SR & 0x00000001 ) == 0x00000001 ) ;
  FLASH->CR &= 0xffffffef ;
  FLASH->SR |= 0x20 ;
}

void flash_opt_erase(int addr) {
  FLASH->CR |= 0x00000020 ;
  FLASH->AR = addr ;
  FLASH->CR |= 0x00000040 ;
  while( ( FLASH->SR & 0x00000001 ) == 0x00000001 ) ;
  FLASH->CR &= 0xffffffdf ;
  FLASH->SR |= 0x20 ;
}



// flash ob mode
void FlashOBConfig(void)
{
  // 在对芯片进行OB设置的时候，要注意将芯片解锁，在操作，最后再上锁，否则配置不成功
  FLASH_OB_Unlock();

 // //对Optionbyes 选项字节全部复位之后，再重新配置
  FLASH_OB_EraseByte(0x1ffff800);
  FLASH_OB_EraseByte(0x1ffff801);
  FLASH_OB_EraseByte(0x1ffff802);
  FLASH_OB_EraseByte(0x1ffff803);
  FLASH_OB_EraseByte(0x1ffff804);
  FLASH_OB_EraseByte(0x1ffff805);
  FLASH_OB_EraseByte(0x1ffff806);
  FLASH_OB_EraseByte(0x1ffff807);
  FLASH_OB_EraseByte(0x1ffff808);
  FLASH_OB_EraseByte(0x1ffff809);
  FLASH_OB_EraseByte(0x1ffff80a);
  FLASH_OB_EraseByte(0x1ffff80b);
  FLASH_OB_EraseByte(0x1ffff80c);
  FLASH_OB_EraseByte(0x1ffff80d);
  FLASH_OB_EraseByte(0x1ffff80e);
  FLASH_OB_EraseByte(0x1ffff80f);
	FLASH->CR &= 0xFFFFFFDF;
	 FLASH->CR |= 0x10 ;	 
   flash_opt_prog(0x1ffff800,0x55aa);
	 FLASH->CR &= 0xFFFFFFEF ;

  FLASH_OB_UserConfig(OB_IWDG_SW,OB_STOP_RST);

	 	flash_opt_prog(0x1ffff804,0x00FF);
	flash_opt_prog(0x1ffff806,0x00FF);
	flash_opt_prog(0x1ffff808,0x00FF);
	flash_opt_prog(0x1ffff80A,0x00FF);
	flash_opt_prog(0x1ffff80C,0x00FF);
	flash_opt_prog(0x1ffff80E,0x00FF);
	
   FLASH_OB_Lock();
}
//进入stop低功耗模式：让LDO处于低功耗状态。WFI中断唤醒
void MCU_Enter_STOPMode(void)
{
  PWR_EnterStopMode(PWR_Regulator_LowPower,PWR_Entry_WFE);
}


int main(void)
{
  Uart_Config();
	   // 
  printf("\r\nMainloop--\r\nLowPower Reset Test\r\n");
  Reset_Init(); 
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);//初始化电源控制时钟与备份寄存器时钟
  FLASH_Unlock();  

  FlashOBConfig();
  printf("\r\nEnterSTOPMode\r\n");
  MCU_Enter_STOPMode();  

FLASH_Lock();
  /* Infinite loop */
  while (1)
  {
  }
}



// printf redefine
int fputc(int ch,FILE *f)
{

	 USART_SendData(USART1, (uint8_t) ch);
 // while((USART1->SR&USART_FLAG_TC)==RESET);
  while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
  {}		
  return ch;
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


