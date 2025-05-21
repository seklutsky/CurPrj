#include "include.h"
int counter_TX1, need_TX1;
extern GPIO_InitTypeDef  GPIO_InitStructure_A;
USART_InitTypeDef USART_InitStructure_1;
char RX_message1 [200], lenght1, test = 0;
uint8_t rx_cnt1, message_rx1, data_message1 = 103, error_message1, message_type1, sum1, k1;
uint16_t DATA1;
int temp11;
void USART1_init(void)
{
// init manualy (SPL functions = no effect)	
 	RCC->APB2ENR|= 1<<4;			// enable clock
 	USART1-> BRR = 42000000*2/38400;			// Baudrate register
	USART1-> CR1|= 1<<2;			// RX enable
	USART1-> CR1|= 1<<3;			// TX enable
	USART1-> CR1|= 1<<5;			// RX interrupt enable
	USART1-> CR1|= 1<<6;			// TX interrupt enable
	USART1-> CR1|= 1<<13;		// UART enable
	NVIC_EnableIRQ (USART1_IRQn);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);		// Enable clock for GPIO_A
	// PC6 - TX
	GPIO_InitStructure_A.GPIO_OType = 								GPIO_OType_PP;
  GPIO_InitStructure_A.GPIO_PuPd = 									GPIO_PuPd_UP;
  GPIO_InitStructure_A.GPIO_Mode = 									GPIO_Mode_AF;		// out???
  GPIO_InitStructure_A.GPIO_Pin = 									GPIO_Pin_9;
  GPIO_InitStructure_A.GPIO_Speed = 								GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure_A);
  // PC7 - RX
  GPIO_InitStructure_A.GPIO_OType = 								GPIO_OType_PP;
  GPIO_InitStructure_A.GPIO_PuPd = 									GPIO_PuPd_NOPULL;
  GPIO_InitStructure_A.GPIO_Mode = 									GPIO_Mode_AF;
  GPIO_InitStructure_A.GPIO_Pin = 									GPIO_Pin_10;
  GPIO_InitStructure_A.GPIO_Speed = 								GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure_A);
	//----------------------------------------------------------------------
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1); 
}
//------------------------------------------------------------------
void USART1_IRQHandler(void)  
{
		// TX complete interrupt
	if ((USART1->SR)&(1<<6))			
		{
		  USART1->SR &= !(1<<6);

		}
	// RX interrupt		
	if ((USART1->SR)&(1<<5))			
		{
			USART1->SR &= !(1<<5); 
			//DATA_485 = USART3->DR;
			
			DATA = USART1->DR ;
			
			USART1->DR = DATA + 1;
		}
}


