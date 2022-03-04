
#include "eeprom.h"

/**************************************************************************************************
* @functioin     EEPROM_WriteByte
* @brief         ����ָ����ƫ�Ƶ�ַ������д��EEPROM
* @param         address:   Ҫд�����ݵ�Ŀ���ַ,�ǻ���EEPROM��ʼ��ַ��ƫ���� 0<=address< HK32F030M_EE_SIZE
* @param         data_in:   Ҫд�������
* @return        0 д��ʧ��      1 д��ɹ�
* @example       EEPROM_WriteByte(2,0x45);  �ǽ�����д�뵽HK32F030M_EE_BEGIN+5�ĵ�ַ,���д��ɹ���
*                ��1, ���򷵻�0
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
* @brief         ����ָ����ƫ�Ƶ�ַ�����ݴ�EEPROM����
* @param         address:   Ҫ��ȡ���ݵ�Ŀ���ַ,�ǻ���EEPROM��ʼ��ַ��ƫ����0<=address< HK32F030M_EE_SIZE
* @param         data_out:  �������ݵĻ������ָ��
* @return        0 ��ȡʧ��      1 ��ȡ�ɹ�
* @example       uint8_t dataR; 
*                EEPROM_ReadByte(2,&dataR);  
*                �ǽ����ݴӵ�ַHK32F030M_EE_BEGIN+5����,��������ɹ���
*                ��1, ���򷵻�0
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

