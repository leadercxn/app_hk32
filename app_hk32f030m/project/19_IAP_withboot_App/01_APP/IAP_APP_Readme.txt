IAP_APP 工程

功能说明:
1、该工程主要是IAP案例里面的APP工程，现象为LED（PC7）慢闪。
2、慢闪一段时间之后，会跳转到IAP_BOOT工程里面去。

接口说明:
LED：PC7	

程序配置说明：
1、在system_hk32f030m.c文件中，将#define VECT_TAB_OFFSET  定义为 0x1280，即将中断向量表映射到0x08001280 。
2、在APP 跳转到boot的函数中，请参考一下写法，主要特别注意的是在FLASH->INT_VEC_OFFSET = 0x0；的位置，一定要在
   重载BOOT地址之前


e.g：


#define USER_BOOT_ADDRESS       (uint32_t)(0x08000000)

typedef  void (*pFunction)(void);
static void JumpToBootapplication(void);

static void JumpToBootapplication(void)
{
	pFunction Jump_To_BOOTApplication;
	uint32_t UserAppAddr;
	
	/* Calculate the address of user application */
    FLASH->INT_VEC_OFFSET = 0x0 ; /* Vector Table Relocation in Internal FLASH. */

	UserAppAddr = *(__IO uint32_t*)(USER_BOOT_ADDRESS + 4);
	Jump_To_BOOTApplication = (pFunction) UserAppAddr;
	
	/* Initialize user application's Stack Pointer, Disable any interrupts during SP setting */
	__set_PRIMASK(1); // Disable interrupts
  
	__set_MSP(*(__IO uint32_t*) USER_BOOT_ADDRESS);
	
	/* Jump to application */
	Jump_To_BOOTApplication();
}