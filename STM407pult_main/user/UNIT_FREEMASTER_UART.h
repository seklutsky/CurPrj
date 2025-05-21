
// UART1 
// TxD=PB6 
// RxD=PB7

// UART3
// TxD=PC10 
// RxD=PC11

#define UART2_A2_A3_FRM

#ifdef UART2_A2_A3_FRM 

#define PC_UART_TX_PORT_CLK    RCC_AHB1Periph_GPIOA
#define PC_UART_TX_PORT        GPIOA
#define PC_UART_TX_PIN         GPIO_Pin_2
#define PC_UART_TX_SOURCE      GPIO_PinSource2
#define PC_UART_TX_AF          GPIO_AF_USART2
#define PC_UART_RX_PORT_CLK    RCC_AHB1Periph_GPIOA
#define PC_UART_RX_PORT        GPIOA
#define PC_UART_RX_PIN         GPIO_Pin_3
#define PC_UART_RX_SOURCE      GPIO_PinSource3
#define PC_UART_RX_AF          GPIO_AF_USART2

#define RCC_APBPeriphClockCmd  RCC_APB1PeriphClockCmd
#define PC_UART_CLK            RCC_APB1Periph_USART2
#define PC_UART                USART2

#define PC_UART_interrupt           USART2_IRQn						  
#define PC_UART_interrupt_Handler   USART2_IRQHandler

#endif

#ifdef UART1_B6_B7_FRM 

#define PC_UART_TX_PORT_CLK    RCC_AHB1Periph_GPIOB
#define PC_UART_TX_PORT        GPIOB
#define PC_UART_TX_PIN         GPIO_Pin_6
#define PC_UART_TX_SOURCE      GPIO_PinSource6
#define PC_UART_TX_AF          GPIO_AF_USART1
#define PC_UART_RX_PORT_CLK    RCC_AHB1Periph_GPIOB
#define PC_UART_RX_PORT        GPIOB
#define PC_UART_RX_PIN         GPIO_Pin_7
#define PC_UART_RX_SOURCE      GPIO_PinSource7
#define PC_UART_RX_AF          GPIO_AF_USART1

#define PC_UART_CLK            RCC_APB2Periph_USART1
#define PC_UART                USART1

#define PC_UART_interrupt           USART1_IRQn						  
#define PC_UART_interrupt_Handler   USART1_IRQHandler

#endif



#ifdef UART6_FRM 

#define PC_UART_TX_PORT_CLK    RCC_AHB1Periph_GPIOC
#define PC_UART_TX_PORT        GPIOC
#define PC_UART_TX_PIN         GPIO_Pin_6
#define PC_UART_TX_SOURCE      GPIO_PinSource6
#define PC_UART_TX_AF          GPIO_AF_USART6
#define PC_UART_RX_PORT_CLK    RCC_AHB1Periph_GPIOC
#define PC_UART_RX_PORT        GPIOC
#define PC_UART_RX_PIN         GPIO_Pin_7
#define PC_UART_RX_SOURCE      GPIO_PinSource7
#define PC_UART_RX_AF          GPIO_AF_USART6

#define PC_UART_CLK            RCC_APB2Periph_USART6
#define PC_UART                USART6

#define PC_UART_interrupt           USART6_IRQn						  
#define PC_UART_interrupt_Handler   USART6_IRQHandler

#endif

extern void UART_init(void);

#include "PE_freemaster_56F8xxx.h"
extern void uartInit(void);
extern void FMSTR_SCI_PUTCHAR(uint8_t _data);
extern uint16_t FMSTR_SCI_GETCHAR(void);
extern void FMSTR_SCI_RE(void);
extern void FMSTR_SCI_RD(void);
extern void FMSTR_SCI_TE(void);
extern void FMSTR_SCI_TD(void);
extern FMSTR_SCISR FMSTR_SCI_RDCLRSR(void);
extern void FMSTR_InitSerial(void) ;
