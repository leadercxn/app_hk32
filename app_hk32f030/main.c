#include "board_config.h"

static gpio_object_t   m_led_gpio = 
{
    .gpio_port_periph_clk = LED_PORT_PERIPH_CLK,
    .p_gpio_port = LED_PORT,
    .gpio_dir = GPIO_DIR_OUTPUR,
    .gpio_pin = LED_PIN,
};

static void delay_ms_xx(uint32_t times)
{
  uint32_t  t = times;

  while(t)
  {
     t = t - 1;
  }
}

int main(void)
{
#if 0
  /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       file (startup_stm32f0xx.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32f0xx.c file
     */
  delay_init();
  
  Led_Init();

 
    
  /* Infinite loop */
  while (1)
  {
    Led_On();
    delay_ms(100);
    Led_Off();
    delay_ms(2000);
  }
#endif

  /**
   * delay 函数的初始化
   */
  mid_system_tick_init();

  gpio_config(&m_led_gpio);

  while(1)
  {
    gpio_output_set(&m_led_gpio, 1);
    delay_ms(100);
    gpio_output_set(&m_led_gpio, 0);
    delay_ms(1000);
  }
}

 
