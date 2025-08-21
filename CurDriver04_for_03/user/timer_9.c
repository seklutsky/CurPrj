#include "include.h"



TIM_TimeBaseInitTypeDef TIM_InitStruct_9;



TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure9;
TIM_OCInitTypeDef TIM_OCInitStructure9;
TIM_ICInitTypeDef TIM_ICInitStructure9;
TIM_BDTRInitTypeDef TIM_BDTRInitStructure9;
extern GPIO_InitTypeDef  GPIO_InitStructure;
extern uint8_t NotTest, NoCheck, Reg_Start;

int intc = 0; 
//==========================================================================================================================================
void Timer_9_init(void)  				// 32 bit timer!
{
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);  

  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);	
	
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_TIM9);

	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9, ENABLE);
	
	//42 MHz tik (0.0238 mkS) * 65535 = 1560 mkS ~ 0.64 KHz 
	
	// 1 kHz = 42017
	
	TIM_TimeBaseStructure9.TIM_Period = 0xFFFF; 
  TIM_TimeBaseStructure9.TIM_Prescaler = 1 ;
  TIM_TimeBaseStructure9.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure9.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM9, &TIM_TimeBaseStructure9);		 // 

	
	TIM_ICInitStructure9.TIM_Channel = TIM_Channel_1;
	TIM_ICInitStructure9.TIM_ICPolarity = TIM_ICPolarity_Rising;//TIM_ICPolarity_BothEdge;
	TIM_ICInitStructure9.TIM_ICSelection = TIM_ICSelection_DirectTI;
	TIM_ICInitStructure9.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM_ICInitStructure9.TIM_ICFilter = 0;
	TIM_ICInit(TIM9, &TIM_ICInitStructure9);

  TIM_CCPreloadControl(TIM9, DISABLE);

	
	TIM_ITConfig(TIM9, TIM_IT_CC1|TIM_IT_Update, ENABLE);
	
//	NVIC_EnableIRQ(TIM9_CC_IRQn); 
	NVIC_EnableIRQ(TIM1_BRK_TIM9_IRQn);

	
	TIM_Cmd(TIM9, ENABLE);
	
 }
//==========================================================================================================================================


char LineDown,LineUP;
uint16_t T9int,PWM_chack=1;
uint16_t ProcPWM_Test = 0x7FFF;
 
 void TIM1_BRK_TIM9_IRQHandler(void) {
	 
					TIM9->CNT = 0;
					if(TIM9->SR & TIM_IT_Update)	{
								TIM_ClearITPendingBit(TIM9, TIM_IT_Update);
								if(1&(GPIOA->IDR>>2)) ProcPWM = 0;	
								else  ProcPWM = 0x7FFF;						
					}

					if(TIM9->SR & TIM_IT_CC1) {
								
								TIM_ClearITPendingBit(TIM9, TIM_IT_CC1);
								T9int++;

								if(fall) {
										fall=0;
										TIM9->CCER = 1; //Rising
										Period1_ = TIM9->CCR1;//TIM_GetCapture1(TIM8);	
										LineDown = 1&(GPIOA->IDR>>2);
								}
								else {
										fall=1;
										TIM9->CCER = 3; //Falling
										Period2_ = TIM9->CCR1;//TIM_GetCapture1(TIM8);
										LineUP = 1&(GPIOA->IDR>>2);										
								}
								if(!LineUP) ProcPWM = 0x7FFF;	
								else if(LineDown) ProcPWM = 0;
								else{
											Period_all = Period1_ + Period2_; // 								
											ProcPWM = div_r(Period2_,Period_all);
								}
								
					} 
					if(!PWM_chack) ProcPWM = ProcPWM_Test;
											
}





