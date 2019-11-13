#include "main.h"
int main(void)
{
  Display_Init();                                        
  ADC3_CH13_DMA_Config();
  
  /* Start ADC3 Software Conversion */ 
  ADC_SoftwareStartConv(ADC3);
  
  while (1)
  {
		Convert_ADC_Voltage();
    Display();
  }
}
