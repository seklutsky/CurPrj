#include "include.h"


TIM_TimeBaseInitTypeDef TIM_InitStruct_1;
TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure1;
TIM_OCInitTypeDef TIM_OCInitStructure1;
TIM_ICInitTypeDef TIM_ICInitStructure1;
TIM_BDTRInitTypeDef TIM_BDTRInitStructure1;
uint8_t NotTest, NoChack, Reg_Start;
//int intc = 0; 
//==========================================================================================================================================

//==========================================================================================================================================
void Timer_1_init(void)  				// 32 bit timer!
{
GPIO_InitTypeDef  GPIO_InitStructure;	
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);  

  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_8|GPIO_Pin_9 ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure);	
	
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_TIM1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_TIM1);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	
	TIM1->SMCR = 0x03;
	
	
/*	TIM_TimeBaseStructure1.TIM_Period = Period; 
  TIM_TimeBaseStructure1.TIM_Prescaler = 0xC8 ;
  TIM_TimeBaseStructure1.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure1.TIM_CounterMode = TIM_CounterMode_CenterAligned2;
  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure1);		 // T1 init

  TIM_OCInitStructure1.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure1.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure1.TIM_Pulse = 0;
  TIM_OCInitStructure1.TIM_OCPolarity = TIM_OCNPolarity_High;
  TIM_OCInitStructure1.TIM_OCIdleState = TIM_OCIdleState_Set;
  TIM_OC1Init(TIM1, &TIM_OCInitStructure1);

  // Automatic Output enable, Break, dead time and lock configuration
  TIM_BDTRInitStructure1.TIM_OSSRState = TIM_OSSRState_Disable;
  TIM_BDTRInitStructure1.TIM_OSSIState = TIM_OSSIState_Disable;
  TIM_BDTRInitStructure1.TIM_LOCKLevel = TIM_LOCKLevel_OFF;
  TIM_BDTRInitStructure1.TIM_DeadTime = 0;
  TIM_BDTRInitStructure1.TIM_Break = TIM_Break_Disable;
  TIM_BDTRInitStructure1.TIM_BreakPolarity = TIM_BreakPolarity_High;
  TIM_BDTRInitStructure1.TIM_AutomaticOutput = TIM_AutomaticOutput_Enable;
  TIM_BDTRConfig(TIM1, &TIM_BDTRInitStructure1);

  TIM_CCPreloadControl(TIM1, DISABLE);
	
  TIM_SetCompare1(TIM1,0);
  TIM_SetCompare2(TIM1,0);
	TIM_SetCompare3(TIM1,0);*/

  TIM_Cmd(TIM1, ENABLE);                                 // T1 enable

  // Main Output Enable 
  //TIM_CtrlPWMOutputs(TIM1, ENABLE);
	
//	TIM_ITConfig(TIM1, TIM_IT_CC1, ENABLE);
//	NVIC_EnableIRQ(TIM1_CC_IRQn); 
 }
//==========================================================================================================================================
 void TIM1_CC_IRQHandler(void)  {
	TIM_ClearITPendingBit(TIM1, TIM_IT_CC1);	
		
}
 
 



