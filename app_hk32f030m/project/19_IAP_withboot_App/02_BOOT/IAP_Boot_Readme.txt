IAP_BOOT 工程

功能说明:
1、该工程主要是IAP案例里面的BOOT工程，现象为LED（PC7）快闪。
2、快闪一段时间之后，会跳转到IAP_IAP工程里面去。

接口说明:
LED：PC7	

程序配置说明：

e.g：


#define USER_APP_ADDRESS       (uint32_t)(0x08001280)

typedef  void (*pFunction)(void);
static void JumpToApplication(void);


static void JumpToApplication(void)
{
	pFunction Jump_To_Application;
	uint32_t UserAppAddr;
	
	/* Calculate the address of user application */
	UserAppAddr = *(__IO uint32_t*) (USER_APP_ADDRESS + 4);
	Jump_To_Application = (pFunction) UserAppAddr;
	
	/* Initialize user application's Stack Pointer, Disable any interrupts during SP setting */
	__set_PRIMASK(1); // Disable interrupts
	__set_MSP(*(__IO uint32_t*) USER_APP_ADDRESS); 
	
	/* Jump to application */
	Jump_To_Application();
}
