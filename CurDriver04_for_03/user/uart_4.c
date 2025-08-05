#include "include.h"
int counter_TX, need_TX;
GPIO_InitTypeDef  GPIO_InitStructure_A;
USART_InitTypeDef USART_InitStructure_4;
char RX_message [200], lenght;
uint8_t rx_cnt, message_rx, data_message = 103, error_message, message_type, sum, k;
uint16_t DATA;
int temp;
void UART4_init(void)
{
// init manualy (SPL functions = no effect)	
 	RCC->APB1ENR|= 1<<19;			// enable clock
 	UART4-> BRR = 42000000/38400;			// Baudrate register
	UART4-> CR1|= 1<<2;			// RX enable
	UART4-> CR1|= 1<<3;			// TX enable
	UART4-> CR1|= 1<<5;			// RX interrupt enable
	UART4-> CR1|= 1<<6;			// TX interrupt enable
	UART4-> CR1|= 1<<13;		// UART enable
	NVIC_EnableIRQ (UART4_IRQn);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);		// Enable clock for GPIO_A
	// PA0 - TX
	GPIO_InitStructure_A.GPIO_OType = 								GPIO_OType_PP;
  GPIO_InitStructure_A.GPIO_PuPd = 									GPIO_PuPd_UP;
  GPIO_InitStructure_A.GPIO_Mode = 									GPIO_Mode_AF;		// out???
  GPIO_InitStructure_A.GPIO_Pin = 									GPIO_Pin_0;
  GPIO_InitStructure_A.GPIO_Speed = 								GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure_A);
  // PA1 - RX
  GPIO_InitStructure_A.GPIO_OType = 								GPIO_OType_PP;
  GPIO_InitStructure_A.GPIO_PuPd = 									GPIO_PuPd_NOPULL;
  GPIO_InitStructure_A.GPIO_Mode = 									GPIO_Mode_AF;
  GPIO_InitStructure_A.GPIO_Pin = 									GPIO_Pin_1;
  GPIO_InitStructure_A.GPIO_Speed = 								GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure_A);
	//----------------------------------------------------------------------
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_UART4);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_UART4); 
	
}
//------------------------------------------------------------------
void UART4_IRQHandler(void)
{
	if ((UART4->SR)&(1<<6))			// Transmission complete interrupt
		{
		  UART4->SR &= !(1<<6); 	// clear flag

		}	
			// RX interrupt		
	if ((UART4->SR)&(1<<5))			
		{
			UART4->SR &= !(1<<5); 	// clear flag
			DATA = UART4->DR ;
			
			UART4->DR = DATA + 4;
		}
}
