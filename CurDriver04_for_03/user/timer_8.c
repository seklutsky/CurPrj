#include "include.h"



TIM_TimeBaseInitTypeDef TIM_InitStruct_8;

TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure8;
TIM_OCInitTypeDef TIM_OCInitStructure8;
TIM_ICInitTypeDef TIM_ICInitStructure8;
TIM_BDTRInitTypeDef TIM_BDTRInitStructure8;
extern GPIO_InitTypeDef  GPIO_InitStructure;



uint16_t Period_all,Period1,Period1_,Period2,Period2_, ProcPWM;



__STATIC_INLINE int16_t div_r(int16_t x, int16_t y);
//int intc = 0; 
//==========================================================================================================================================

//==========================================================================================================================================
void Timer_8_init(void)  				// 32 bit timer!
{
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);  

  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOC, &GPIO_InitStructure);	
	
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_TIM8);

	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);
	
	//42 MHz tik (0.0238 mkS) * 65535 = 1560 mkS ~ 0.64 KHz 
	
	// 1 kHz = 42017
	
	TIM_TimeBaseStructure8.TIM_Period = 0xFFFF; 
  TIM_TimeBaseStructure8.TIM_Prescaler = 3 ;
  TIM_TimeBaseStructure8.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure8.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure8);		 // T8 init
	
	TIM_ICInitStructure8.TIM_Channel = TIM_Channel_1;
	TIM_ICInitStructure8.TIM_ICPolarity = TIM_ICPolarity_Rising;//TIM_ICPolarity_BothEdge;
	TIM_ICInitStructure8.TIM_ICSelection = TIM_ICSelection_DirectTI;
	TIM_ICInitStructure8.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM_ICInitStructure8.TIM_ICFilter = 0;
	TIM_ICInit(TIM8, &TIM_ICInitStructure8);
	
  TIM_CCPreloadControl(TIM8, DISABLE);
	
	TIM_ITConfig(TIM8, TIM_IT_CC1|TIM_IT_Update, ENABLE);
	
	NVIC_EnableIRQ(TIM8_CC_IRQn); 
	NVIC_EnableIRQ(TIM8_UP_TIM13_IRQn);

	TIM8->CNT = 0;
	TIM_Cmd(TIM8, ENABLE);
 }
//==========================================================================================================================================

 
 char fall = 0;
 uint16_t start_pulse = 0;
 uint16_t Err1 = 0;
 
 uint32_t timer_check[3] = {0,0,0};
 
 void TIM8_CC_IRQHandler(void)  {

		TIM8->SR = (uint16_t)~TIM_IT_CC1;
	  TIM8->CNT = 0;
//		TIM_ClearITPendingBit(TIM8, TIM_IT_CC1);
		
			 
		//intc++;

	  if(fall) {		
				TIM8->CCER = 1; //Rising
			  Period1_ = TIM8->CCR1;//TIM_GetCapture1(TIM8);	
			
				if(1&(GPIOC->IDR>>6)) {
						Period2_ = 0;
					  TIM8->CCER = 3; //Falling
				}
				else 	{
					fall=0;						
				}
	  }
		else {  
			  TIM8->CCER = 3; //Falling
			  Period2_ = TIM8->CCR1;//TIM_GetCapture1(TIM8);

				if(!(1&(GPIOC->IDR>>6))) {
					 Period1_ = 0;
					 TIM8->CCER = 1; //Rising
				}
				else {
					fall=1;					
				}
					
		}
		Period_all = Period1_ + Period2_;
		if(start_pulse < 2) start_pulse ++;
								  								
		else	if((Period_all > 4000)&&(Period_all < 9000))		ProcPWM = div_r(Period2_,Period_all);	
}


 void TIM8_UP_TIM13_IRQHandler(void) {
			 if(1&(GPIOC->IDR>>6)) {
					ProcPWM = 0;
				  Period2_ = 0;
				  TIM8->CCER = 3; //Falling
				  fall=1;
			 }
	     else {
					ProcPWM = 0x7FFF;
					Period1_ = 0;
				  TIM8->CCER = 1; //Rising
				  fall=0;
			 }
			start_pulse = 0;
			timer_check[0]++;
//	 		 TIM_ClearITPendingBit(TIM8, TIM_IT_Update);	
			TIM8->SR = (uint16_t)~TIM_IT_Update;
 }


__STATIC_INLINE int16_t div_r(int16_t x, int16_t y)
{
    return (uint16_t) (((uint32_t) (x*0xFFFF) / (y)) >> 1 );
}
