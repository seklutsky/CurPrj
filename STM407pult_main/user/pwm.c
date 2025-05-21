#include "include.h"


//42 MHz tik (0.0238 mkS)

uint16_t pwm100;
//==========================================================================================================================================
void Timer_3_pwm_init(uint16_t pwm_Hz)  				
{
	
	if(pwm_Hz < 5000) pwm_Hz = 5000;
	else if(pwm_Hz > 10000) pwm_Hz = 10000;
	
TIM_TimeBaseInitTypeDef TIM_InitStruct;
TIM_OCInitTypeDef TIM_OCInitStructure ;
//TIM_ICInitTypeDef TIM_ICInitStructure ;
TIM_BDTRInitTypeDef TIM_BDTRInitStructure ;
GPIO_InitTypeDef  GPIO_InitStructure;
	
	pwm100 = (uint16_t)((float)PWM10KHz * 10000.0f/(float)pwm_Hz);
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); 

	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	

	GPIO_PinAFConfig(GPIOB, GPIO_PinSource0, GPIO_AF_TIM3);
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
	TIM_InitStruct.TIM_Period = pwm100; 
  TIM_InitStruct.TIM_Prescaler = 0 ;
  TIM_InitStruct.TIM_ClockDivision = 0;
  TIM_InitStruct.TIM_CounterMode = TIM_CounterMode_CenterAligned2;
  TIM_TimeBaseInit(TIM3, &TIM_InitStruct);		 
	
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
//  TIM_OCInitStructure3.TIM_OutputNState = TIM_OutputNState_Enable;
  TIM_OCInitStructure.TIM_Pulse = 0;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCNPolarity_High;
//  TIM_OCInitStructure3.TIM_OCNPolarity = TIM_OCNPolarity_High;
  TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
//  TIM_OCInitStructure3.TIM_OCNIdleState = TIM_OCNIdleState_Set;
  TIM_OC3Init(TIM3, &TIM_OCInitStructure);

  // Automatic Output enable, Break, dead time and lock configuration
  TIM_BDTRInitStructure.TIM_OSSRState = TIM_OSSRState_Disable;
  TIM_BDTRInitStructure.TIM_OSSIState = TIM_OSSIState_Disable;
  TIM_BDTRInitStructure.TIM_LOCKLevel = TIM_LOCKLevel_OFF;
  TIM_BDTRInitStructure.TIM_DeadTime = 0;
  TIM_BDTRInitStructure.TIM_Break = TIM_Break_Disable;
  TIM_BDTRInitStructure.TIM_BreakPolarity = TIM_BreakPolarity_High;
  TIM_BDTRInitStructure.TIM_AutomaticOutput = TIM_AutomaticOutput_Disable;
  TIM_BDTRConfig(TIM3, &TIM_BDTRInitStructure);

//  TIM_CCPreloadControl(TIM3, 0);
	

	TIM_SetCompare3(TIM3,pwm100);
  TIM_Cmd(TIM3, ENABLE);                                 

  // Main Output Enable 
  TIM_CtrlPWMOutputs(TIM3, ENABLE);	
	
//	TIM_ITConfig(TIM3, TIM_IT_CC3, ENABLE);
//	NVIC_EnableIRQ(TIM3_IRQn); 
	
	

 }
//==========================================================================================================================================

 
void PWM_set(uint16_t val)
{
				uint16_t a;
				a = (uint16_t)((float)(val*pwm100)/100.0f);
			  TIM_SetCompare3(TIM3,pwm100-a);	
}
 
 void TIM3_IRQHandler(void)
{
	TIM_ClearITPendingBit(TIM3, TIM_IT_CC3);	
}

