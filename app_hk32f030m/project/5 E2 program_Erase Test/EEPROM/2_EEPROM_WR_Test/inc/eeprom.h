
#ifndef _eeprom_h
#define _eeprom_h

#ifdef __cplusplus
extern "C" {
#endif
	
#include "hk32f030m.h"
#include "hk32f030m_flash.h"
	
#define  HK32F030M_EE_BEGIN    (0x0C000000ul)             // HK32F0301MоƬ��EEPROM��ʼ��ַ
#define  HK32F030M_EE_END      (0x0C0001C0ul)             // HK32F0301MоƬ��EEPROM������ַ
#define  HK32F030M_EE_SIZE     (448)                      // HK32F0301MоƬ��EEPROM����

uint8_t EEPROM_WriteByte(uint32_t address, uint8_t data_in);
uint8_t EEPROM_ReadByte(uint32_t address,uint8_t *data_out);	
	
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _usart_h */
