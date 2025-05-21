#include "include.h"
TIM_TimeBaseInitTypeDef TIM_InitStruct_7;
extern short Stop_ModeCounter, Counter_Slave_On, Start_time, End_Start, CounterTestOn;
extern char Stop_Mode, Error_out, Error_out_buff;
extern char Master_CAN, UprOn, blink, RegOn, ErrorOn;
extern uint16_t PultTestMode;

//==========================================================================================================================================
void Timer_7_init(void)  				
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);
	TIM_InitStruct_7.TIM_CounterMode 			= TIM_CounterMode_Up;
	TIM_InitStruct_7.TIM_Prescaler				= 8400-1;					// prescaler for bus clock = 84 max
	TIM_InitStruct_7.TIM_Period						= 1000;					// 10000 = 1 s period
	TIM_TimeBaseInit(TIM7, &TIM_InitStruct_7);							
	TIM_ITConfig(TIM7, TIM_IT_Update, ENABLE);
	NVIC_EnableIRQ(TIM7_IRQn); 
	TIM_Cmd(TIM7, ENABLE);
 }
//==========================================================================================================================================
extern uint8_t NotTest;

void TIM7_IRQHandler(void)
{
		 TIM_ClearITPendingBit(TIM7, TIM_IT_Update);
	
			if(Start_time < End_Start) Start_time++;
	
			else	{
	

																	if(Stop_ModeCounter) {
																					if(!Error_out) Stop_ModeCounter--;
																					else Stop_ModeCounter = SEC_WAIT_01;
																					if(Stop_ModeCounter < SEC_WAIT_01_GIST) CLR_ERROR;
																	}
																	else {
																					if(NotTest) Stop_Mode = 0;
																					Error_out_buff = 0;																					
																					CLR_ERROR;
																					ErrorOn = 0;
																	}
	
																	if(!Master_CAN) {
																					Counter_Slave_On++;
																					if(Counter_Slave_On >= 5) {
																							Error_out |= ERROR_CAN;
																					}																	
																	}
																	if(PultTestMode) {
																		if(CounterTestOn < 5) CounterTestOn++;
																	}
													
													blink++;
													if(blink>10) blink=0;
			}
}



