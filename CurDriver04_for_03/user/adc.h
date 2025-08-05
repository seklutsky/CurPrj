
#define StartADC ADC1->CR2|= 1<<30

extern void ADC_init(void);
extern uint16_t readADC1(u8 channel);
extern s16 val;
extern short median_filter (short* data_array, uint8_t array_size);
extern u16 current_X10mA, voltage_X10mV;

