
#include "adc.h"

#define MESSAGE1   "ADC conversion w/DMA"
#define MESSAGE1_1 "continuouslyTransfer" 
#define MESSAGE2   " ADC Ch13 Conv   "
#define MESSAGE2_1 "    2.4Msps      "
#define MESSAGE5   " ADC3 = %d,%1d C "
#define LINENUM            0x15
#define FONTSIZE         Font12x12
#define ADC3_DR_ADDRESS     ((uint32_t)0x4001224C)

__IO uint16_t uhADC3ConvertedValue = 0;
__IO uint32_t uwADC3ConvertedVoltage = 0;

/* Private function prototypes -----------------------------------------------*/

#ifdef USE_LCD
#endif /* USE_LCD */
/* Private functions ---------------------------------------------------------*/

void Convert_ADC_Voltage(void){
    uwADC3ConvertedVoltage = uhADC3ConvertedValue *3000/0xFFF;
}

void Display(void)
{
  uint32_t uwVoltage =0, uwMVoltage=0;
  uint32_t temperature;
  uint8_t aTextBuffer[50];
	
	temperature = (uwADC3ConvertedVoltage - 0.76);
  uwVoltage = 25+(temperature/2500);
  uwMVoltage = (temperature%2500)/100;

  sprintf((char*)aTextBuffer, MESSAGE5, uwVoltage, uwMVoltage);
  LCD_DisplayStringLine(LCD_LINE_6, (uint8_t*)aTextBuffer);
}

void Display_Init(void)
{
  /* Initialize the LCD */
  LCD_Init();
  LCD_LayerInit();
  /* Enable the LTDC */
  LTDC_Cmd(ENABLE);
  
  /* Set LCD Background Layer  */
  LCD_SetLayer(LCD_BACKGROUND_LAYER);
  
  /* Clear the Background Layer */ 
  LCD_Clear(LCD_COLOR_WHITE);
  
  /* Configure the transparency for background */
  LCD_SetTransparency(0);
  
  /* Set LCD Foreground Layer  */
  LCD_SetLayer(LCD_FOREGROUND_LAYER);

  /* Configure the transparency for foreground */
  LCD_SetTransparency(200);
  
  /* Clear the Foreground Layer */ 
  LCD_Clear(LCD_COLOR_BLACK);
  
  /* Set the LCD Text size */
  LCD_SetFont(&Font16x24);
  
  
  /* Set the LCD Back Color and Text Color*/
  LCD_SetBackColor(LCD_COLOR_BLACK);
  LCD_SetTextColor(LCD_COLOR_GREEN);
}

void ADC3_CH13_DMA_Config(void)
{
  ADC_InitTypeDef       ADC_InitStructure;
  ADC_CommonInitTypeDef ADC_CommonInitStructure;
  DMA_InitTypeDef       DMA_InitStructure;
  GPIO_InitTypeDef      GPIO_InitStructure;

  /* Enable ADC3, DMA2 and GPIO clocks ****************************************/
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2 | RCC_AHB1Periph_GPIOC, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3, ENABLE);

  /* DMA2 Stream0 channel2 configuration **************************************/
  DMA_InitStructure.DMA_Channel = DMA_Channel_2;  
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)ADC3_DR_ADDRESS;
  DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)&uhADC3ConvertedValue;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
  DMA_InitStructure.DMA_BufferSize = 1;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;         
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
  DMA_Init(DMA2_Stream0, &DMA_InitStructure);
  DMA_Cmd(DMA2_Stream0, ENABLE);

  /* Configure ADC3 Channel13 pin as analog input ******************************/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  /* ADC Common Init **********************************************************/
  ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
  ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;
  ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
  ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
  ADC_CommonInit(&ADC_CommonInitStructure);

  /* ADC3 Init ****************************************************************/
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
  ADC_InitStructure.ADC_ScanConvMode = DISABLE;
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;	
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_NbrOfConversion = 1;
  ADC_Init(ADC3, &ADC_InitStructure);

  /* ADC3 regular channel13 configuration *************************************/
  ADC_RegularChannelConfig(ADC3, ADC_Channel_13, 1, ADC_SampleTime_3Cycles);

 /* Enable DMA request after last transfer (Single-ADC mode) */
  ADC_DMARequestAfterLastTransferCmd(ADC3, ENABLE);

  /* Enable ADC3 DMA */
  ADC_DMACmd(ADC3, ENABLE);

  /* Enable ADC3 */
  ADC_Cmd(ADC3, ENABLE);
}
uint32_t L3GD20_TIMEOUT_UserCallback(void)
{
  return 0;
}
void TimingDelay_Decrement(void)
{
}
