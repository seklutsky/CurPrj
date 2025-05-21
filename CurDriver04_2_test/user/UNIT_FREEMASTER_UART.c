#include "include.h"

extern USART_InitTypeDef USART_InitStructure;
extern NVIC_InitTypeDef NVIC_InitStructure;
extern GPIO_InitTypeDef  GPIO_InitStructure;

void uartInit(void);

//-------------------------------------------------------------------------------------------------------------------------
void FMSTR_SCI_PUTCHAR(uint8_t _data)
{
 PC_UART->DR = _data;		
}

uint16_t FMSTR_SCI_GETCHAR()
{
 return PC_UART->DR ;
}

void FMSTR_SCI_RE(void)
{
 PC_UART->CR1 |= USART_CR1_RE ;
 USART_ITConfig(PC_UART, USART_IT_RXNE, ENABLE);
}

void FMSTR_SCI_RD(void)
{
 PC_UART->CR1 &= ~USART_CR1_RE ;
 USART_ITConfig(PC_UART, USART_IT_RXNE, DISABLE);
}

void FMSTR_SCI_TE(void)
{
 PC_UART->CR1 |= USART_CR1_TE ;
 USART_ITConfig(PC_UART, USART_IT_TC  , ENABLE);
}

void FMSTR_SCI_TD(void)
{
 PC_UART->CR1 &= ~USART_CR1_TE ;
 USART_ITConfig(PC_UART, USART_IT_TC  , DISABLE);
}

FMSTR_SCISR FMSTR_SCI_RDCLRSR(void)
{
    FMSTR_SCISR SciSR = 0;

    if(USART_GetITStatus(PC_UART, USART_IT_RXNE) != RESET) // UART receive buffer full 
      {
//       USART_ClearITPendingBit(PC_UART, USART_IT_RXNE) ;
       SciSR = FMSTR_SCISR_RDRF; 
      }

    if(USART_GetITStatus(PC_UART, USART_IT_TC) != RESET)  // UART is transmitting data or transmit register full (UART busy)
      {   
       SciSR |= FMSTR_SCISR_TDRE; 
      }      

    return SciSR;
}

void uartInit(void)
{
 UART_init();
}
//-------------------------------------------------------------------------------------------------------------------------


void UART_init(void)
{
// GPIO
  // Configure USART Tx as alternate function 
  RCC_AHB1PeriphClockCmd(PC_UART_TX_PORT_CLK, ENABLE);

  GPIO_PinAFConfig(PC_UART_TX_PORT, PC_UART_TX_SOURCE, PC_UART_TX_AF);
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Pin = PC_UART_TX_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(PC_UART_TX_PORT, &GPIO_InitStructure);

  // Configure USART Rx as alternate function  
  RCC_AHB1PeriphClockCmd(PC_UART_RX_PORT_CLK, ENABLE);

  GPIO_PinAFConfig(PC_UART_RX_PORT, PC_UART_RX_SOURCE, PC_UART_RX_AF);
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Pin = PC_UART_RX_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(PC_UART_RX_PORT, &GPIO_InitStructure);


// USART
  RCC_APB1PeriphClockCmd (PC_UART_CLK, ENABLE);

  USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

  USART_Init(PC_UART, &USART_InitStructure);
    
  USART_Cmd(PC_UART, ENABLE);

//  USART_ITConfig(PC_UART, USART_IT_TC  , ENABLE);
  USART_ITConfig(PC_UART, USART_IT_RXNE, ENABLE);

// interrupt
  NVIC_InitStructure.NVIC_IRQChannel = PC_UART_interrupt;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}


void PC_UART_interrupt_Handler(void)
{
			FMSTR_Poll();
	  //PC_UART->DR = 0xA5;	
}

