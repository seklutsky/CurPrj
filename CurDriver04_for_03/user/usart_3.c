#include "include.h"
// USART 3 -> RS-485
char DATA_485;
void USART3_init(void)
{
// init manualy (SPL functions = no effect)	
 	RCC->APB1ENR|= 1<<18;			// enable clock
 	USART3-> BRR = 42000000/38400;			// Baudrate register
	USART3-> CR1|= 1<<2;			// RX enable
	USART3-> CR1|= 1<<3;			// TX enable
	USART3-> CR1|= 1<<5;			// RX interrupt enable
	USART3-> CR1|= 1<<6;			// TX interrupt enable
	USART3-> CR1|= 1<<13;			// UART enable
	NVIC_EnableIRQ (USART3_IRQn);
//
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);		// Enable clock for GPIO_B
// TX
	GPIO_InitStructure_B.GPIO_OType = 								GPIO_OType_PP;
  GPIO_InitStructure_B.GPIO_PuPd = 									GPIO_PuPd_UP;
  GPIO_InitStructure_B.GPIO_Mode = 									GPIO_Mode_AF;		
  GPIO_InitStructure_B.GPIO_Pin = 									GPIO_Pin_10;
  GPIO_InitStructure_B.GPIO_Speed = 								GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure_B);
//  RX
  GPIO_InitStructure_B.GPIO_OType = 								GPIO_OType_PP;
  GPIO_InitStructure_B.GPIO_PuPd = 									GPIO_PuPd_NOPULL;
  GPIO_InitStructure_B.GPIO_Mode = 									GPIO_Mode_AF;
  GPIO_InitStructure_B.GPIO_Pin = 									GPIO_Pin_11;
  GPIO_InitStructure_B.GPIO_Speed = 								GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure_B);
//----------------------------------------------------------------------
// RE (RS485_REn_CB) - inverted Receive enable 
	GPIO_InitStructure_B.GPIO_OType = 								GPIO_OType_PP;
  GPIO_InitStructure_B.GPIO_PuPd = 									GPIO_PuPd_DOWN;
  GPIO_InitStructure_B.GPIO_Mode = 									GPIO_Mode_OUT;
  GPIO_InitStructure_B.GPIO_Pin = 									GPIO_Pin_12;
  GPIO_InitStructure_B.GPIO_Speed = 								GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure_B);
// RS485_DE_CB driver enable
	GPIO_InitStructure_B.GPIO_OType = 								GPIO_OType_PP;
  GPIO_InitStructure_B.GPIO_PuPd = 									GPIO_PuPd_UP;
  GPIO_InitStructure_B.GPIO_Mode = 									GPIO_Mode_OUT;
  GPIO_InitStructure_B.GPIO_Pin = 									GPIO_Pin_13;
  GPIO_InitStructure_B.GPIO_Speed = 								GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure_B);
	GPIOB->ODR |= 1<<13;
//----------------------------------------------------------------------
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_USART3);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_USART3);
///
//USART3->DR = 0x01;
}

void USART3_IRQHandler(void)
{
	// TX complete interrupt
	if ((USART3->SR)&(1<<6))			
		{
		  USART3->SR &= !(1<<6);

		}
	// RX interrupt		
	if ((USART3->SR)&(1<<5))			
		{
			USART3->SR &= !(1<<5); 
			DATA = USART3->DR;	
			USART3->DR = DATA + 3;

		}
}
