extern void USART1_init(void);
extern void USART1_IRQHandler(void);
extern void send_uart1_message(int bytes_number);
extern char TX_message1[6];
extern void write_data1(uint8_t message_type6);
extern int counter_TX1, need_TX1;


extern char RX_message1 [200], lenght1;
extern uint8_t rx_cnt1, message_rx1, data_message1, error_message1, message_type1, sum1, k1;
extern uint16_t DATA1;
extern int temp11;
