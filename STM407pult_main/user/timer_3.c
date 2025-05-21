#include "include.h"


extern uint8_t counter;
TIM_TimeBaseInitTypeDef TIM_InitStruct_3;
TIM_OCInitTypeDef TIM_OCInitStructure3 ;
TIM_ICInitTypeDef TIM_ICInitStructure3 ;
TIM_BDTRInitTypeDef TIM_BDTRInitStructure3 ;


//==========================================================================================================================================
void Timer_3_init(void)  				// 32 bit timer!
{
GPIO_InitTypeDef  GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); 

	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_4|GPIO_Pin_5 ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	

	GPIO_PinAFConfig(GPIOB, GPIO_PinSource4, GPIO_AF_TIM3);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource5, GPIO_AF_TIM3);
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
	TIM_InitStruct_3.TIM_Period = PWM_100; 
  TIM_InitStruct_3.TIM_Prescaler = 0 ;
  TIM_InitStruct_3.TIM_ClockDivision = 0;
  TIM_InitStruct_3.TIM_CounterMode = ActualCounterMode;
  TIM_TimeBaseInit(TIM3, &TIM_InitStruct_3);		 // T2 init	
	
  TIM_OCInitStructure3.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure3.TIM_OutputState = TIM_OutputState_Enable;
//  TIM_OCInitStructure3.TIM_OutputNState = TIM_OutputNState_Enable;
  TIM_OCInitStructure3.TIM_Pulse = 0;
  TIM_OCInitStructure3.TIM_OCPolarity = TIM_OCNPolarity_High;
//  TIM_OCInitStructure3.TIM_OCNPolarity = TIM_OCNPolarity_High;
  TIM_OCInitStructure3.TIM_OCIdleState = TIM_OCIdleState_Set;
//  TIM_OCInitStructure3.TIM_OCNIdleState = TIM_OCNIdleState_Set;
  TIM_OC1Init(TIM3, &TIM_OCInitStructure3);
	
	TIM_OCInitStructure3.TIM_OCPolarity = TIM_OCNPolarity_High;
  TIM_OC2Init(TIM3, &TIM_OCInitStructure3);



  // Automatic Output enable, Break, dead time and lock configuration
  TIM_BDTRInitStructure3.TIM_OSSRState = TIM_OSSRState_Disable;
  TIM_BDTRInitStructure3.TIM_OSSIState = TIM_OSSIState_Disable;
  TIM_BDTRInitStructure3.TIM_LOCKLevel = TIM_LOCKLevel_OFF;
  TIM_BDTRInitStructure3.TIM_DeadTime = 0;
  TIM_BDTRInitStructure3.TIM_Break = TIM_Break_Disable;
  TIM_BDTRInitStructure3.TIM_BreakPolarity = TIM_BreakPolarity_High;
  TIM_BDTRInitStructure3.TIM_AutomaticOutput = TIM_AutomaticOutput_Disable;
  TIM_BDTRConfig(TIM3, &TIM_BDTRInitStructure3);

//  TIM_CCPreloadControl(TIM3, 0);
	

  TIM_SetCompare1(TIM3,PWM_100/2);
  TIM_SetCompare2(TIM3,PWM_100/2);
	TIM_SetCompare3(TIM3,OFFSET_PWM);
  TIM_Cmd(TIM3, ENABLE);                                 // T1 enable

  // Main Output Enable 
  TIM_CtrlPWMOutputs(TIM3, ENABLE);	
	
//	TIM_ITConfig(TIM3, TIM_IT_CC3, ENABLE);
//	NVIC_EnableIRQ(TIM3_IRQn); 
	
	

 }
//==========================================================================================================================================
extern uint8_t NotTest, NoChack, Reg_Start;
 
 void TIM3_IRQHandler(void)
{
	TIM_ClearITPendingBit(TIM3, TIM_IT_CC3);	

	
}


