#define DAC_MAX		4095
#define	VOLT_MAX	3.3f

void DAC_Init_(void);
void DAC_set_level(uint16_t channel, uint16_t val);

