//extern void init_CAN1(void);
extern void init_CAN2(void);
extern char error[8], RESOURCE[8], CYCLE_COUNT[4];
extern unsigned short I, T[29], U[14], Uab, C1, C2,TDCH, TCH;
extern uint8_t B1, humidity_B, humidity_A, relay_CB;
extern uint8_t current_mailbox,transmit_state, send_data_flag, balance, charge, discharge, j, tmp, boot_flag;
//extern void CAN_TX(void);
extern GPIO_InitTypeDef  GPIO_InitStructure_B, GPIO_InitStructure;
extern CanTxMsg TxMessage, DATA_message, ERROR_message, RESOURCE_message, BALANCE_message, CHARGE_message, DISCHARGE_message;
extern CanRxMsg RxMessage_0, RxMessage_1;

#define CAN1x                       CAN1
#define CAN1_CLK                    RCC_APB1Periph_CAN1
#define CAN1_RX_PIN                 GPIO_Pin_11
#define CAN1_TX_PIN                 GPIO_Pin_12
#define CAN1_GPIO_PORT              GPIOA
#define CAN1_GPIO_CLK               RCC_AHB1Periph_GPIOA
#define CAN1_AF_PORT                GPIO_AF_CAN1
#define CAN1_RX_SOURCE              GPIO_PinSource11
#define CAN1_TX_SOURCE              GPIO_PinSource12 

#define CAN2x                       CAN2
#define CAN2_CLK                    RCC_APB1Periph_CAN2
#define CAN2_RX_PIN                 GPIO_Pin_5
#define CAN2_TX_PIN                 GPIO_Pin_6
#define CAN2_GPIO_PORT              GPIOB
#define CAN2_GPIO_CLK               RCC_AHB1Periph_GPIOB
#define CAN2_AF_PORT                GPIO_AF_CAN2
#define CAN2_RX_SOURCE              GPIO_PinSource5
#define CAN2_TX_SOURCE              GPIO_PinSource6 

#define US_STATE_REQUEST						0x00
#define BM_STATE_REQUEST						0x01

