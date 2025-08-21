#include "include.h"

typedef char byte;
extern uint8_t counter;
TIM_TimeBaseInitTypeDef TIM_InitStruct_2;
TIM_OCInitTypeDef TIM_OCInitStructure2 ;
TIM_ICInitTypeDef TIM_ICInitStructure2 ;
TIM_BDTRInitTypeDef TIM_BDTRInitStructure2 ;
extern GPIO_InitTypeDef  GPIO_InitStructure;
extern char First_Start1;


//==========================================================================================================================================
void Timer_2_init(void)  				// 32 bit timer!
{
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); 
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);  
	
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure);	
	
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource15, GPIO_AF_TIM2);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource3, GPIO_AF_TIM2);
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	TIM_InitStruct_2.TIM_Period = PWM_100; 
  TIM_InitStruct_2.TIM_Prescaler = 1 ;
  TIM_InitStruct_2.TIM_ClockDivision = 0;
  TIM_InitStruct_2.TIM_CounterMode = ActualCounterMode;
  TIM_TimeBaseInit(TIM2, &TIM_InitStruct_2);		 // T2 init	
	
  TIM_OCInitStructure2.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure2.TIM_OutputState = TIM_OutputState_Enable;
//  TIM_OCInitStructure2.TIM_OutputNState = TIM_OutputNState_Enable;
  TIM_OCInitStructure2.TIM_Pulse = 0;
  TIM_OCInitStructure2.TIM_OCPolarity = TIM_OCPolarity_High;
//  TIM_OCInitStructure2.TIM_OCNPolarity = TIM_OCNPolarity_High;
  TIM_OCInitStructure2.TIM_OCIdleState = TIM_OCIdleState_Set;
//  TIM_OCInitStructure2.TIM_OCNIdleState = TIM_OCNIdleState_Set;	
  TIM_OC1Init(TIM2, &TIM_OCInitStructure2);
		
	TIM_OCInitStructure2.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OC2Init(TIM2, &TIM_OCInitStructure2);
	

  // Automatic Output enable, Break, dead time and lock configuration
  TIM_BDTRInitStructure2.TIM_OSSRState = TIM_OSSRState_Disable;
  TIM_BDTRInitStructure2.TIM_OSSIState = TIM_OSSIState_Disable;
  TIM_BDTRInitStructure2.TIM_LOCKLevel = TIM_LOCKLevel_OFF;
  TIM_BDTRInitStructure2.TIM_DeadTime = 0;
  TIM_BDTRInitStructure2.TIM_Break = TIM_Break_Disable;
  TIM_BDTRInitStructure2.TIM_BreakPolarity = TIM_BreakPolarity_High;
  TIM_BDTRInitStructure2.TIM_AutomaticOutput = TIM_AutomaticOutput_Disable;
  TIM_BDTRConfig(TIM2, &TIM_BDTRInitStructure2);

  TIM_CCPreloadControl(TIM2, DISABLE);
	

  TIM_SetCompare1(TIM2,0);
  TIM_SetCompare2(TIM2,0);
	TIM_SetCompare3(TIM2,OFFSET_PWM);

//  TIM_Cmd(TIM2, ENABLE);                                 

  // Main Output Enable 
  TIM_CtrlPWMOutputs(TIM2, ENABLE);	
	
//	TIM_ITConfig(TIM2, TIM_IT_CC3, ENABLE);
//	NVIC_EnableIRQ(TIM2_IRQn); 
	
 }
//==========================================================================================================================================
void TIM2_IRQHandler(void)
{
		TIM_ClearITPendingBit(TIM2, TIM_IT_CC3);

}
