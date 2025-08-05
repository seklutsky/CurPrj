extern void USART6_init(void);
extern void USART6_IRQHandler(void);
extern void send_uart6_message(int bytes_number);
extern char TX_message6[6];
extern void write_data6(uint8_t message_type6);
extern int counter_TX6, need_TX6;


extern char RX_message6 [200], lenght6;
extern uint8_t rx_cnt6, message_rx6, data_message6, error_message6, message_type6, sum6, k6;
extern uint16_t DATA6;
extern int temp6;
