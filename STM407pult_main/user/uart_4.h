extern void UART4_init(void);
extern void UART4_IRQHandler(void);
extern void send_uart_message(int bytes_number);
extern char TX_message[6];
extern void write_data(uint8_t message_type);
extern int counter_TX, need_TX;


extern char RX_message [200], RX_message6 [200], lenght;
extern uint8_t rx_cnt, message_rx, data_message, error_message, message_type, sum, k;
extern uint16_t DATA;
extern int temp;
