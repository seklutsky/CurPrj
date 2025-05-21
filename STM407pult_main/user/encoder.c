
#include "include.h"

#define INC_TIM1


#ifdef INC_TIM8

#define TIM_ENC TIM8 //TIM1 or TIM8

#define TIM_ENC_GPIO1 					GPIO_Pin_6
#define TIM_ENC_GPIO2 					GPIO_Pin_7
#define TIM_ENC_GPIOSource1 		GPIO_PinSource6
#define TIM_ENC_GPIOSource2 		GPIO_PinSource7
#define TIM_ENC_PORT 						GPIOC
#define TIM_ENC_AF							GPIO_AF_TIM8
#define TIM_ENC_RCC_APB					RCC_APB2Periph_TIM8
#define TIM_ENC_RCC_Periph_GPIO RCC_AHB1Periph_GPIOC

#else

#define TIM_ENC TIM1 //TIM1 or TIM8

#define TIM_ENC_GPIO1 					GPIO_Pin_8
#define TIM_ENC_GPIO2 					GPIO_Pin_9
#define TIM_ENC_GPIOSource1 		GPIO_PinSource8
#define TIM_ENC_GPIOSource2 		GPIO_PinSource9
#define TIM_ENC_PORT						GPIOA
#define TIM_ENC_AF							GPIO_AF_TIM1
#define TIM_ENC_RCC_APB 				RCC_APB2Periph_TIM1
#define TIM_ENC_RCC_Periph_GPIO RCC_AHB1Periph_GPIOA

#endif


void Encoder_Init(void)
{
GPIO_InitTypeDef  GPIO_InitStructure;	
 	
	RCC_APB2PeriphClockCmd(TIM_ENC_RCC_APB, ENABLE);
	RCC_AHB1PeriphClockCmd(TIM_ENC_RCC_Periph_GPIO, ENABLE);
	
  GPIO_InitStructure.GPIO_Pin =  TIM_ENC_GPIO1 | TIM_ENC_GPIO2 ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(TIM_ENC_PORT, &GPIO_InitStructure);	
	
  GPIO_PinAFConfig(TIM_ENC_PORT, TIM_ENC_GPIOSource1, TIM_ENC_AF);
	GPIO_PinAFConfig(TIM_ENC_PORT, TIM_ENC_GPIOSource2, TIM_ENC_AF);	
	
	TIM_ENC->SMCR = 0x03;	
  TIM_Cmd(TIM_ENC, ENABLE);	
	TIM_CtrlPWMOutputs(TIM_ENC, ENABLE);
}


uint16_t Encoder_get_position(void)
{
#ifdef ENCODER_INVERSION
	int16_t a = -TIM_ENC->CNT;
#else
		int16_t a = TIM_ENC->CNT;
#endif
	if(a < 0) 
	{
		TIM_ENC->CNT = 0;
		return 0;
	}
	else if(a > ENCODER_MAX) 
	{
#ifdef ENCODER_INVERSION
		TIM_ENC->CNT = -ENCODER_MAX;
#else
		TIM_ENC->CNT = ENCODER_MAX;
#endif
		
		return ENCODER_MAX;
	}
	return a;
}

void Encoder_set_position(int16_t a)
{
	if(a < 0) 
	{
		TIM_ENC->CNT = 0;
	}
	else if(a > ENCODER_MAX) 
	{
#ifdef ENCODER_INVERSION
		TIM_ENC->CNT = -ENCODER_MAX;
#else
		TIM_ENC->CNT = ENCODER_MAX;
#endif
	}
  else 
	{
#ifdef ENCODER_INVERSION
		TIM_ENC->CNT = -a;
#else
		TIM_ENC->CNT = a;
#endif
	}
}

void Encoder_reset(void)
{
		TIM_ENC->CNT = 0;
}
