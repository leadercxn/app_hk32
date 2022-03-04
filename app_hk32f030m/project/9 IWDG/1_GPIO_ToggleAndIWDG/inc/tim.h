
#ifndef __tim__h
#define __tim__h

#include "hk32f030m.h"
#include "hk32f030m_iwdg.h"
#include "hk32f030m_tim.h"

#define SYS_CLK_FREQ     (32000000ul)   /* 系统时钟频率 */

#define SOFT_TIME_NUM    1
#define COM_DELAY_TIM_ID 0

/* 软件定时器结构体 */
typedef struct{
	uint32_t cnt;
	uint8_t en;
}SoftTime_t;

void softTimer_Init(void);
void softTimerBaseTimerCallBack(void);
uint8_t softTimerStart(uint8_t id, uint32_t cnt_init);
uint8_t softTimerStop(uint8_t id);
uint8_t softTimerIsRunning(uint8_t id);

#endif
