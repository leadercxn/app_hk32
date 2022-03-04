
#include "tim.h"

SoftTime_t soft_timer_list[SOFT_TIME_NUM];

static void softTimer_VariableInit(void);
static void softTimerBaseTimerInit(void);

void softTimer_Init(void)
{
	softTimer_VariableInit();
	softTimerBaseTimerInit();
}

static void softTimer_VariableInit(void)
{
	int i;
	
	for(i=0;i<SOFT_TIME_NUM;i++)
	{
		soft_timer_list[i].en = 0;
	}
}

static void softTimerBaseTimerInit(void)
{
	SysTick_Config(SYS_CLK_FREQ/1000);  /* ÖÜÆÚÎª1ms */
	NVIC_EnableIRQ(SysTick_IRQn);
}

uint8_t softTimerStart(uint8_t id, uint32_t cnt_init)
{
	if(id >= SOFT_TIME_NUM)
	{
		return 0;
	}
	soft_timer_list[id].en = 0;
	soft_timer_list[id].cnt = cnt_init;
	soft_timer_list[id].en = 1;
	return 1;
}

uint8_t softTimerStop(uint8_t id)
{
	if(id >= SOFT_TIME_NUM)
	{
		return 0;
	}
	soft_timer_list[id].en = 0;
	return 1;
}
uint8_t softTimerIsRunning(uint8_t id)
{
	return soft_timer_list[id].en;
}

void softTimerBaseTimerCallBack(void)
{
	uint8_t i;
	for(i=0;i<SOFT_TIME_NUM;i++)
	{
		if(soft_timer_list[i].en == 1)
		{
			if(soft_timer_list[i].cnt > 0)
			{
				soft_timer_list[i].cnt--;
				if(soft_timer_list[i].cnt==0)
				{
					soft_timer_list[i].en = 0;
				}
			}
		}
	}
}
