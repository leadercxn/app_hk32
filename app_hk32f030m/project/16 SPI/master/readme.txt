оƬ�ͺţ�
HK32F030M
ʱ�����ã�
HSI 32M
������;��
SPI masterģʽ����ѯģʽ��ȡ����
�ӿڶ��壺
1. SPI
	#define  SPI_CS_PORT      GPIOD
	#define  SPI_CS_Pin       GPIO_Pin_7
			
	#define  SPI_CLK_PORT      GPIOA
	#define  SPI_CLK_Pin       GPIO_Pin_2
			
	#define  SPI_MOSI_PORT      GPIOD
	#define  SPI_MOSI_Pin       GPIO_Pin_4
			
	#define  SPI_MISO_PORT      GPIOB
	#define  SPI_MISO_Pin       GPIO_Pin_4
	
2. USART
	#define  USART1_TX_PORT         GPIOA
	#define  USART1_TX_PIN          GPIO_Pin_3

	#define  USART1_RX_PORT         GPIOD
	#define  USART1_RX_PIN          GPIO_Pin_6
���Է�����
SPI��Ϊmaster������cmd��1byte������ȡ3byte���ݡ�
