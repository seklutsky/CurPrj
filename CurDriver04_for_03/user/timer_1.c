#include "include.h"


extern uint8_t counter;
extern char First_Start1;
TIM_TimeBaseInitTypeDef TIM_InitStruct_1;

TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
TIM_OCInitTypeDef TIM_OCInitStructure;
TIM_ICInitTypeDef TIM_ICInitStructure;
TIM_BDTRInitTypeDef TIM_BDTRInitStructure;
extern GPIO_InitTypeDef  GPIO_InitStructure;
uint32_t Timer_Counter,Timer_Counter1,Timer_Counter2;

//==========================================================================================================================================
void Timer_1_init(void)  				// 32 bit timer!
{
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);  

  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_8 ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure);	
	
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_9 ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);	
	
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_TIM1);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_TIM1);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	
	TIM_TimeBaseStructure.TIM_Period = PWM_100; 
  TIM_TimeBaseStructure.TIM_Prescaler = 3 ;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = ActualCounterMode;
  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);		 // T1 init

  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = 0;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;

  TIM_OC1Init(TIM1, &TIM_OCInitStructure);

	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	TIM_OC2Init(TIM1, &TIM_OCInitStructure);

  // Automatic Output enable, Break, dead time and lock configuration
  TIM_BDTRInitStructure.TIM_OSSRState = TIM_OSSRState_Disable;
  TIM_BDTRInitStructure.TIM_OSSIState = TIM_OSSIState_Disable;
  TIM_BDTRInitStructure.TIM_LOCKLevel = TIM_LOCKLevel_OFF;
  TIM_BDTRInitStructure.TIM_DeadTime = 0;
  TIM_BDTRInitStructure.TIM_Break = TIM_Break_Disable;
  TIM_BDTRInitStructure.TIM_BreakPolarity = TIM_BreakPolarity_High;
  TIM_BDTRInitStructure.TIM_AutomaticOutput = TIM_AutomaticOutput_Disable;
  TIM_BDTRConfig(TIM1, &TIM_BDTRInitStructure);
	
  TIM_CCPreloadControl(TIM1, DISABLE);
	
  TIM_SetCompare1(TIM1,0);
  TIM_SetCompare2(TIM1,0);
	TIM_SetCompare3(TIM1,0);
  //TIM_Cmd(TIM1, ENABLE);                                 // T1 enable

  // Main Output Enable 
  TIM_CtrlPWMOutputs(TIM1, ENABLE);
	
	TIM_ITConfig(TIM1, TIM_IT_CC3, ENABLE);


	NVIC_EnableIRQ(TIM1_CC_IRQn); 

 }
//==========================================================================================================================================
uint16_t Tim_test0,Tim_test1,Tim_test2,Tim_test3,Tim_test4,Tim_test5;
uint16_t  TimSinc1,TimSinc2,TimSinc3,TimSinc4,TimSinc5,TimSinc6;
extern char ADC_ch,_ADC_ch,ADC_INIT_DONE;
char ResetCounters=0;
extern long int ADC_counter,ADC_counter1,ADC_counter2,ADC_counter3,ADC_counter4,ADC_counter5;
extern uint16_t  Istep;
uint16_t I_test=I_TEST;
 
 void TIM1_CC_IRQHandler(void)  {
	
	 TIM_ClearITPendingBit(TIM1, TIM_IT_CC3);	
//	 TIM1->SR = 0;
	 Timer_Counter++;
	 
	 if(Timer_Counter&0x100) Istep = 0;
	 else Istep = I_test;
	 
	 if(Timer_Counter&0x1)	{//24.3712 mkS
			if(ADC_INIT_DONE) {
						ADC_INIT_DONE=0;
						_ADC_ch=ADC_ch; 
						ADC_ch = 0;
						ADC_RegularChannelConfig(ADC1, CH_I_LED, 1, ADC_SampleTime_);
						StartADC;	
						Timer_Counter2++;
			}
			else Timer_Counter1++;
		}
}


