#include "include.h"
int counter_TX5, need_TX5;
extern GPIO_InitTypeDef  GPIO_InitStructure_C; 
GPIO_InitTypeDef  GPIO_InitStructure_D;
USART_InitTypeDef USART_InitStructure_5;
char RX_message5 [200], lenght5;
uint8_t rx_cnt5, message_rx5, data_message5 = 103, error_message5, message_type5, sum5, k5;
uint16_t DATA5;
int temp5;
void UART5_init(void)
{
// init manualy (SPL functions = no effect)	
 	RCC->APB1ENR|= 1<<20;			// enable clock
 	UART5-> BRR = 42000000/38400;			// Baudrate register
	UART5-> CR1|= 1<<2;			// RX enable
	UART5-> CR1|= 1<<3;			// TX enable
	UART5-> CR1|= 1<<5;			// RX interrupt enable
	UART5-> CR1|= 1<<6;			// TX interrupt enable
	UART5-> CR1|= 1<<13;		// UART enable
	NVIC_EnableIRQ (UART5_IRQn);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);		// Enable clock for GPIO_C
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);		// Enable clock for GPIO_D
	// PA0 - TX
	GPIO_InitStructure_C.GPIO_OType = 								GPIO_OType_PP;
  GPIO_InitStructure_C.GPIO_PuPd = 									GPIO_PuPd_UP;
  GPIO_InitStructure_C.GPIO_Mode = 									GPIO_Mode_AF;		// out???
  GPIO_InitStructure_C.GPIO_Pin = 									GPIO_Pin_12;
  GPIO_InitStructure_C.GPIO_Speed = 								GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure_C);
  // PA1 - RX
  GPIO_InitStructure_D.GPIO_OType = 								GPIO_OType_PP;
  GPIO_InitStructure_D.GPIO_PuPd = 									GPIO_PuPd_NOPULL;
  GPIO_InitStructure_D.GPIO_Mode = 									GPIO_Mode_AF;
  GPIO_InitStructure_D.GPIO_Pin = 									GPIO_Pin_2;
  GPIO_InitStructure_D.GPIO_Speed = 								GPIO_Speed_50MHz;
  GPIO_Init(GPIOD, &GPIO_InitStructure_D);
	//----------------------------------------------------------------------
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource12, GPIO_AF_UART5);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource2, GPIO_AF_UART5); 
	
}
//------------------------------------------------------------------
void UART5_IRQHandler(void)
{
	if ((UART5->SR)&(1<<6))			// Transmission complete interrupt
		{
		  UART5->SR &= !(1<<6); 	// clear flag

		}	
			// RX interrupt		
	if ((UART5->SR)&(1<<5))			
		{
			UART5->SR &= !(1<<5); 	// clear flag
			DATA = UART5->DR ;
			
			UART5->DR = DATA + 5;			
													
			
		}
}
