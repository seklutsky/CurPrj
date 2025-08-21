#include <stm32f4xx.h>
#include <stdio.h>

#define StartADC ADC1->CR2|= 1<<30

extern void ADC_init(void);
extern uint16_t readADC1(char channel);
extern int16_t val;
extern short median_filter (short* data_array, uint8_t array_size);
extern uint16_t current_X10mA, voltage_X10mV;

