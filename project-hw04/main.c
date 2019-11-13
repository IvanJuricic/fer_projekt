#include "main.h"
RCC_ClocksTypeDef RCC_Clocks;
int main(void)
{
  /*!< At this stage the microcontroller clock setting is already configured, 
  this is done through SystemInit() function which is called from startup
  files (startup_stm32f429_439xx.s) before to branch to application main. 
  To reconfigure the default setting of SystemInit() function, refer to
  system_stm32f4xx.c file
  */  
  /* SysTick end of count event each 10ms */
  RCC_GetClocksFreq(&RCC_Clocks);
  SysTick_Config(RCC_Clocks.HCLK_Frequency / 100);
  
  /* Initialize the LCD */
  LCD_Init();
  /* Initialize the LCD Layers*/
  LCD_LayerInit();
  
  /* Enable the LTDC */
  LTDC_Cmd(ENABLE);
  
  /* Set LCD Background Layer  */
  LCD_SetLayer(LCD_FOREGROUND_LAYER);
  
  /* Clear the Background Layer */ 
  LCD_Clear(LCD_COLOR_WHITE);

  /* Gyroscope configuration */
  Demo_GyroConfig();

  /* Gyroscope calibration */
  Gyro_SimpleCalibration();
  
  /* Infinite loop */
  while (1)
  {
    Demo_MEMS();
  }
}