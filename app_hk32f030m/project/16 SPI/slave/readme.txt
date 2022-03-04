芯片型号：
HK32F030M
时钟配置：
HSI 32M
配置用途：
SPI slave模式，中断方式发送数据
接口定义：
1. SPI
	#define  SPI_CS_PORT      GPIOD
	#define  SPI_CS_Pin       GPIO_Pin_7
			
	#define  SPI_CLK_PORT      GPIOA
	#define  SPI_CLK_Pin       GPIO_Pin_2
			
	#define  SPI_MOSI_PORT      GPIOD
	#define  SPI_MOSI_Pin       GPIO_Pin_4
			
	#define  SPI_MISO_PORT      GPIOB
	#define  SPI_MISO_Pin       GPIO_Pin_4
	

测试方法：
SPI作为slave，接收cmd（1byte），发送3byte数据。

