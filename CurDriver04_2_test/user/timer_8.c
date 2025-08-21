#include "include.h"


extern uint8_t counter;
TIM_TimeBaseInitTypeDef TIM_InitStruct_8;

TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure8;
TIM_OCInitTypeDef TIM_OCInitStructure8;
TIM_ICInitTypeDef TIM_ICInitStructure8;
TIM_BDTRInitTypeDef TIM_BDTRInitStructure8;
extern GPIO_InitTypeDef  GPIO_InitStructure;
extern uint8_t NotTest, NoCheck, Reg_Start;
//int intc = 0; 
//==========================================================================================================================================

//==========================================================================================================================================
void Timer_8_init(void)  				// 32 bit timer!
{
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);  

  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7 ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOC, &GPIO_InitStructure);	
	
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_TIM8);
  GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_TIM8);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);
	
	TIM_TimeBaseStructure8.TIM_Period = PWM_100; 
  TIM_TimeBaseStructure8.TIM_Prescaler = 3 ;
  TIM_TimeBaseStructure8.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure8.TIM_CounterMode = ActualCounterMode;
  TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure8);		 // T8 init

  TIM_OCInitStructure8.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure8.TIM_OutputState = TIM_OutputState_Enable;
//  TIM_OCInitStructure8.TIM_OutputNState = TIM_OutputNState_Enable;
  TIM_OCInitStructure8.TIM_Pulse = 0;
  TIM_OCInitStructure8.TIM_OCPolarity = TIM_OCPolarity_High;
//  TIM_OCInitStructure8.TIM_OCNPolarity = TIM_OCNPolarity_High;
  TIM_OCInitStructure8.TIM_OCIdleState = TIM_OCIdleState_Set;
//  TIM_OCInitStructure8.TIM_OCNIdleState = TIM_OCNIdleState_Set;
  TIM_OC1Init(TIM8, &TIM_OCInitStructure8);

	TIM_OCInitStructure8.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OC2Init(TIM8, &TIM_OCInitStructure8);

  // Automatic Output enable, Break, dead time and lock configuration
  TIM_BDTRInitStructure8.TIM_OSSRState = TIM_OSSRState_Disable;
  TIM_BDTRInitStructure8.TIM_OSSIState = TIM_OSSIState_Disable;
  TIM_BDTRInitStructure8.TIM_LOCKLevel = TIM_LOCKLevel_OFF;
  TIM_BDTRInitStructure8.TIM_DeadTime = 0;
  TIM_BDTRInitStructure8.TIM_Break = TIM_Break_Disable;
  TIM_BDTRInitStructure8.TIM_BreakPolarity = TIM_BreakPolarity_High;
  TIM_BDTRInitStructure8.TIM_AutomaticOutput = TIM_AutomaticOutput_Disable;
  TIM_BDTRConfig(TIM8, &TIM_BDTRInitStructure8);

  TIM_CCPreloadControl(TIM8, DISABLE);
	
  TIM_SetCompare1(TIM8,0);
  TIM_SetCompare2(TIM8,0);
	TIM_SetCompare3(TIM8,OFFSET_PWM);

//  TIM_Cmd(TIM8, ENABLE);                                 // T1 enable

  // Main Output Enable 
  TIM_CtrlPWMOutputs(TIM8, ENABLE);
	
//	TIM_ITConfig(TIM8, TIM_IT_CC3, ENABLE);
//	NVIC_EnableIRQ(TIM8_CC_IRQn); 
 }
//==========================================================================================================================================
 void TIM8_CC_IRQHandler(void)  {
	TIM_ClearITPendingBit(TIM8, TIM_IT_CC3);	
		
}
 
 
 
 /*
 void TIM8_CC_IRQHandler(void)  {
	 
		TIM_ClearITPendingBit(TIM8, TIM_IT_CC1);
		TIM_SetCounter(TIM8,0);
			 
		//intc++;

	  if(fall) {
			  fall=0;
				TIM8->CCER = 1; //Rising
			  Period1_ = TIM8->CCR1;//TIM_GetCapture1(TIM8);	
	  }
		else {
			  fall=1;
				TIM8->CCER = 3; //Falling
			  Period2_ = TIM8->CCR1;//TIM_GetCapture1(TIM8);
		}
		
								if(Period2_ > 150) Period2 = Period2_;
								if( (Period1_ + Period2) > Period_all_MAX ) Period1 = 0;
								else Period1 = Period1_;
								Period_all = Period1 + Period2; // 								
								ProcPWM = div_r(Period2,Period_all);	
		
}


 void TIM8_UP_TIM13_IRQHandler(void) {
			 if(fall) ProcPWM = 0;
	     else ProcPWM = FRAC16(0.9999);
	 
	 		 TIM_ClearITPendingBit(TIM8, TIM_IT_Update);	
 }
*/


