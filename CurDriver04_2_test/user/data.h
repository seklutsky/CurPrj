typedef char byte;
extern byte crc8(byte *data,int count);
extern void interpret_data(void);
extern uint8_t state[8], cell_state[8], cnt, data_interpret_ready;
