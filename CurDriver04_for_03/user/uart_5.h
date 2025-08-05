extern void UART5_init(void);
extern void UART5_IRQHandler(void);
extern void send_uart_message5(int bytes_number);
extern char TX_message5[6];
extern void write_data5(uint8_t message_type);
extern int counter_TX5, need_TX5;


extern char RX_message5 [200], RX_message5 [200], lenght5;
extern uint8_t rx_cnt5, message_rx5, data_message5, error_message5, message_type5, sum5, k5;
extern uint16_t DATA5;
extern int temp5;
