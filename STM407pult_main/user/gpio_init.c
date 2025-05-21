#include "include.h"


void PortsInit(void) {
	
GPIO_InitTypeDef  GPIO_InitStructure;
	
	//outputs
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	GPIO_InitStructure.GPIO_OType = 								GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = 									GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Mode = 									GPIO_Mode_OUT;		
  GPIO_InitStructure.GPIO_Pin = 									GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Speed = 								GPIO_Speed_2MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
//	GPIOB->ODR = 0x0;

	
	//inputs
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	GPIO_InitStructure.GPIO_OType = 								GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = 									GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Mode = 									GPIO_Mode_IN;		
  GPIO_InitStructure.GPIO_Pin = 									GPIO_Pin_All;
  GPIO_InitStructure.GPIO_Speed = 								GPIO_Speed_2MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);	
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_OType = 								GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = 									GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Mode = 									GPIO_Mode_IN;		
  GPIO_InitStructure.GPIO_Pin = 									GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Speed = 								GPIO_Speed_2MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);		
	
	

//	GPIOC->ODR &= ~(1<<7);	

	SET_VOFF_OUT_PORT;
	CLR_STB_OUT_PORT;
	SET_ERR_OUT_PORT;
}



