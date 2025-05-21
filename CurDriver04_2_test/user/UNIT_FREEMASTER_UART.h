
// UART1 
// TxD=PB6 
// RxD=PB7

// UART3
// TxD=PC10 
// RxD=PC11

//USART 4
// TxD=PA0 
// RxD=PA1
// TxD=PC10 
// RxD=PC11



#define PC_UART_TX_PORT_CLK    RCC_AHB1Periph_GPIOC
#define PC_UART_TX_PORT        GPIOC
#define PC_UART_TX_PIN         GPIO_Pin_10
#define PC_UART_TX_SOURCE      GPIO_PinSource10
#define PC_UART_TX_AF          GPIO_AF_USART3//GPIO_AF_UART4
#define PC_UART_RX_PORT_CLK    RCC_AHB1Periph_GPIOC
#define PC_UART_RX_PORT        GPIOC
#define PC_UART_RX_PIN         GPIO_Pin_11
#define PC_UART_RX_SOURCE      GPIO_PinSource11
#define PC_UART_RX_AF          GPIO_AF_USART3//GPIO_AF_UART4

#define PC_UART_CLK            RCC_APB1Periph_USART3//RCC_APB1Periph_UART4
#define PC_UART                USART3//UART4

#define PC_UART_interrupt           USART3_IRQn//UART4_IRQn						  
#define PC_UART_interrupt_Handler   USART3_IRQHandler//UART4_IRQHandler


extern void UART_init(void) ;

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
