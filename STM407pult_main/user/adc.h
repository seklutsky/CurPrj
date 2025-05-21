#include <types.h>

#define ADC_ALL				4

#define I_P48V 				ADC_Channel_0
#define I_LOAD 				ADC_Channel_1
#define TERM_IN 			ADC_Channel_6
#define CON_IN 				ADC_Channel_7

void ADC_init_(void);
short median_filter (short* data_array, uint8_t array_size);
uint16_t getADCresult(uint16_t N);
