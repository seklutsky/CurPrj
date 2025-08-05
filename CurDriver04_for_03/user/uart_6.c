#include "include.h"
int counter_TX6, need_TX6;
GPIO_InitTypeDef  GPIO_InitStructure_C;
USART_InitTypeDef USART_InitStructure_6;
char RX_message6 [200], lenght6, test6 = 0;
uint8_t rx_cnt6, message_rx6, data_message6 = 103, error_message6, message_type6, sum6, k6;
uint16_t DATA6;
int temp6;
void USART6_init(void)
{
// init manualy (SPL functions = no effect)	
 	RCC->APB2ENR|= 1<<5;			// enable clock
 	USART6-> BRR = 42000000*2/38400;			// Baudrate register
	USART6-> CR1|= 1<<2;			// RX enable
	USART6-> CR1|= 1<<3;			// TX enable
	USART6-> CR1|= 1<<5;			// RX interrupt enable
	USART6-> CR1|= 1<<6;			// TX interrupt enable
	USART6-> CR1|= 1<<13;		// UART enable
	NVIC_EnableIRQ (USART6_IRQn);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);		// Enable clock for GPIO_C
	// PC6 - TX
	GPIO_InitStructure_C.GPIO_OType = 								GPIO_OType_PP;
  GPIO_InitStructure_C.GPIO_PuPd = 									GPIO_PuPd_UP;
  GPIO_InitStructure_C.GPIO_Mode = 									GPIO_Mode_AF;		// out???
  GPIO_InitStructure_C.GPIO_Pin = 									GPIO_Pin_6;
  GPIO_InitStructure_C.GPIO_Speed = 								GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure_C);
  // PC7 - RX
  GPIO_InitStructure_C.GPIO_OType = 								GPIO_OType_PP;
  GPIO_InitStructure_C.GPIO_PuPd = 									GPIO_PuPd_NOPULL;
  GPIO_InitStructure_C.GPIO_Mode = 									GPIO_Mode_AF;
  GPIO_InitStructure_C.GPIO_Pin = 									GPIO_Pin_7;
  GPIO_InitStructure_C.GPIO_Speed = 								GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure_C);
	//----------------------------------------------------------------------
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_USART6);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_USART6); 
}
//------------------------------------------------------------------
void USART6_IRQHandler(void)
{
	if ((USART6->SR)&(1<<6))			// Transmission complete interrupt
		{
		  USART6->SR &= !(1<<6); 	// clear flag
	
		}	
			// RX interrupt		
	if ((USART6->SR)&(1<<5))			
		{
			USART6->SR &= !(1<<5); 	// clear flag
			DATA6 = USART6->DR ;
			USART6->DR = DATA6 + 6;		
		}
}
