
#ifndef __ADC_H
#define __ADC_H

#include "stm32f4xx.h"
#include <stdio.h>
#include "stm32f429i_discovery.h"
#include "stm32f429i_discovery_lcd.h"

#define USE_LCD


void Display_Init(void);
void Display(void);
void ADC3_CH13_DMA_Config(void);
void Convert_ADC_Voltage(void);
void TimingDelay_Decrement(void);

#endif /* __ADC_H */

