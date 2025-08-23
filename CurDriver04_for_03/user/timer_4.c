#include "include.h"



TIM_TimeBaseInitTypeDef TIM_InitStruct_4;
TIM_OCInitTypeDef TIM_OCInitStructure4 ;
TIM_ICInitTypeDef TIM_ICInitStructure4 ;
TIM_BDTRInitTypeDef TIM_BDTRInitStructure4 ;
extern GPIO_InitTypeDef  GPIO_InitStructure;

//==========================================================================================================================================
void Timer_4_init(void)  				// 32 bit timer!
{
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); 

	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6|GPIO_Pin_7 ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	

	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_TIM4);
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	
	TIM_InitStruct_4.TIM_Period = PWM_100; 
  TIM_InitStruct_4.TIM_Prescaler = 1 ;
  TIM_InitStruct_4.TIM_ClockDivision = 0;
  TIM_InitStruct_4.TIM_CounterMode = ActualCounterMode;
  TIM_TimeBaseInit(TIM4, &TIM_InitStruct_4);		 // T2 init	
	
  TIM_OCInitStructure4.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure4.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure4.TIM_Pulse = 0;
  TIM_OCInitStructure4.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OCInitStructure4.TIM_OCIdleState = TIM_OCIdleState_Set;
  TIM_OC1Init(TIM4, &TIM_OCInitStructure4);


	TIM_OCInitStructure4.TIM_OCPolarity = TIM_OCPolarity_Low;
  TIM_OC2Init(TIM4, &TIM_OCInitStructure4);



  // Automatic Output enable, Break, dead time and lock configuration
  TIM_BDTRInitStructure4.TIM_OSSRState = TIM_OSSRState_Disable;
  TIM_BDTRInitStructure4.TIM_OSSIState = TIM_OSSIState_Disable;
  TIM_BDTRInitStructure4.TIM_LOCKLevel = TIM_LOCKLevel_OFF;
  TIM_BDTRInitStructure4.TIM_DeadTime = 0;
  TIM_BDTRInitStructure4.TIM_Break = TIM_Break_Disable;
  TIM_BDTRInitStructure4.TIM_BreakPolarity = TIM_BreakPolarity_High;
  TIM_BDTRInitStructure4.TIM_AutomaticOutput = TIM_AutomaticOutput_Disable;
  TIM_BDTRConfig(TIM4, &TIM_BDTRInitStructure4);

//  TIM_CCPreloadControl(TIM4, DISABLE);
	
  
  TIM_SetCompare1(TIM4,0);
  TIM_SetCompare2(TIM4,0);
	TIM_SetCompare3(TIM4,0);
//  TIM_Cmd(TIM4, ENABLE);                                 // T1 enable

  // Main Output Enable 
  TIM_CtrlPWMOutputs(TIM4, ENABLE);	
	
//	TIM_ITConfig(TIM4, TIM_IT_CC3, ENABLE);
	NVIC_EnableIRQ(TIM4_IRQn); 

 }
//==========================================================================================================================================

uint16_t TestTim4; 
 
 void TIM4_IRQHandler(void)
{
		TIM_ClearITPendingBit(TIM4, TIM_IT_CC3);		
		TIM_ITConfig(TIM4, TIM_IT_CC3, DISABLE);
}


