
#include "eeprom.h"

/**************************************************************************************************
* @functioin     EEPROM_WriteByte
* @brief         根据指定的偏移地址将数据写入EEPROM
* @param         address:   要写入数据的目标地址,是基于EEPROM起始地址的偏移量 0<=address< HK32F030M_EE_SIZE
* @param         data_in:   要写入的数据
* @return        0 写入失败      1 写入成功
* @example       EEPROM_WriteByte(2,0x45);  是将数据写入到HK32F030M_EE_BEGIN+5的地址,如果写入成功则返
*                回1, 否则返回0
**************************************************************************************************/
uint8_t EEPROM_WriteByte(uint32_t address, uint8_t data_in)
{
	if(HK32F030M_EE_SIZE <= address)
	{
		return 0;
	}
	
	FLASH_Unlock();
	EEPROM_EraseByte(address+HK32F030M_EE_BEGIN);
	EEPROM_ProgramByte(address+HK32F030M_EE_BEGIN, data_in);
	FLASH_Lock();
	
	if((*(uint8_t *)(address+HK32F030M_EE_BEGIN)) != data_in)
	{
		return 0;
	}
	return 1;
}
/**************************************************************************************************
* @functioin     EEPROM_ReadByte
* @brief         根据指定的偏移地址将数据从EEPROM读出
* @param         address:   要读取数据的目标地址,是基于EEPROM起始地址的偏移量0<=address< HK32F030M_EE_SIZE
* @param         data_out:  读出数据的缓存变量指针
* @return        0 读取失败      1 读取成功
* @example       uint8_t dataR; 
*                EEPROM_ReadByte(2,&dataR);  
*                是将数据从地址HK32F030M_EE_BEGIN+5读出,如果读出成功则返
*                回1, 否则返回0
**************************************************************************************************/
uint8_t EEPROM_ReadByte(uint32_t address,uint8_t *data_out)
{
	if(HK32F030M_EE_SIZE <= address)
	{
		return 0;
	}
	
	*data_out = (*((uint8_t *)(address + HK32F030M_EE_BEGIN)));
	return 1;
}

