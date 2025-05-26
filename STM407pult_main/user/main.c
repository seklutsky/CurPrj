#include "include.h"
#include "boot.h"

RCC_ClocksTypeDef       RCC_Clocks;


int main()
{

	
		SystemInit();
		SystemCoreClockUpdate();
	
		RCC_GetClocksFreq(&RCC_Clocks);
		PortsInit();

  	Timer_3_pwm_init(7000);
		Timer_2_init();

		Encoder_Init();
		FMSTR_InitSerial();
	
		ADC_init_();
		DAC_Init_();
	
		disp1color_Init();
			
		display_initControlDAC2();
	
	
		can_initGPIO();
		can1_init(CanMaster);
		
		Disp_preved();

		__enable_irq();
		__set_PRIMASK(0);


		while (1)   {
			
			Run();
		}
}




