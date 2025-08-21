#include "include.h"


extern uint8_t counter;
TIM_TimeBaseInitTypeDef TIM_InitStruct_5;
TIM_OCInitTypeDef TIM_OCInitStructure5 ;
TIM_ICInitTypeDef TIM_ICInitStructure5 ;
TIM_BDTRInitTypeDef TIM_BDTRInitStructure5 ;
extern GPIO_InitTypeDef  GPIO_InitStructure;




//==========================================================================================================================================
void Timer_5_init(void)  				// 32 bit timer!
{
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 

	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0|GPIO_Pin_1 ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_TIM5);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_TIM5);
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
	
	TIM_InitStruct_5.TIM_Period = PWM_100; 
  TIM_InitStruct_5.TIM_Prescaler = 1 ;
  TIM_InitStruct_5.TIM_ClockDivision = 0;
  TIM_InitStruct_5.TIM_CounterMode = ActualCounterMode;
  TIM_TimeBaseInit(TIM5, &TIM_InitStruct_5);		 // T2 init	
	
  TIM_OCInitStructure5.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure5.TIM_OutputState = TIM_OutputState_Enable;
//  TIM_OCInitStructure5.TIM_OutputNState = TIM_OutputNState_Enable;
  TIM_OCInitStructure5.TIM_Pulse = 0;
  TIM_OCInitStructure5.TIM_OCPolarity = TIM_OCPolarity_High;
//  TIM_OCInitStructure5.TIM_OCNPolarity = TIM_OCNPolarity_High;
  TIM_OCInitStructure5.TIM_OCIdleState = TIM_OCIdleState_Set;
//  TIM_OCInitStructure5.TIM_OCNIdleState = TIM_OCNIdleState_Set;
  TIM_OC1Init(TIM5, &TIM_OCInitStructure5);

  TIM_OCInitStructure5.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OC2Init(TIM5, &TIM_OCInitStructure5);


  // Automatic Output enable, Break, dead time and lock configuration
  TIM_BDTRInitStructure5.TIM_OSSRState = TIM_OSSRState_Disable;
  TIM_BDTRInitStructure5.TIM_OSSIState = TIM_OSSIState_Disable;
  TIM_BDTRInitStructure5.TIM_LOCKLevel = TIM_LOCKLevel_OFF;
  TIM_BDTRInitStructure5.TIM_DeadTime = 0;
  TIM_BDTRInitStructure5.TIM_Break = TIM_Break_Disable;
  TIM_BDTRInitStructure5.TIM_BreakPolarity = TIM_BreakPolarity_High;
  TIM_BDTRInitStructure5.TIM_AutomaticOutput = TIM_AutomaticOutput_Disable;
  TIM_BDTRConfig(TIM5, &TIM_BDTRInitStructure5);

//  TIM_CCPreloadControl(TIM5, 0);
	

  TIM_SetCompare1(TIM5,0);
  TIM_SetCompare2(TIM5,0);
	TIM_SetCompare3(TIM5,5);
//  TIM_Cmd(TIM5, ENABLE);                                 // T1 enable

  // Main Output Enable 
  TIM_CtrlPWMOutputs(TIM5, ENABLE);	
	
		
//	TIM_ITConfig(TIM5, TIM_IT_CC3, ENABLE);
//	NVIC_EnableIRQ(TIM5_IRQn); 
	
	

 }
//==========================================================================================================================================
extern uint16_t DeadTime;
extern uint8_t NotTest, NoCheck, Reg_Start;
 
 
void TIM5_IRQHandler(void)
{
		TIM_ClearITPendingBit(TIM5, TIM_IT_CC3);	

}



