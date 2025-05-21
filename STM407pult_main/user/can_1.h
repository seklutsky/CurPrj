#include <types.h>

void can1_init(char   Master_CAN);
void can_initGPIO(void);
void CAN_exchange(void);
void CAN_exchangeTest(uint16_t TestPwm, uint16_t ActiveCh);
void Fill_data_message(void);
void InitCAN_Master_Slave(uint16_t MASTER_IN_PORT);

extern char RegOn; 
extern char PWR_ON; 
extern char STB_ON; 
extern char Error_CAN;
extern char   Error_out;
extern uint16_t Sin;
extern short can1_Counter_Slave_Timeout;
extern char can_send_counter;
extern uint16_t  UprADC, ProcPWM, STB_IN_PORT, MASTER_IN_PORT, VOFF_IN_PORT, ERR_IN_PORT, TemperatureADC, V_led, V_bus;
