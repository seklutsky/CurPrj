 #include "include.h"
 extern NVIC_InitTypeDef NVIC_InitStructure;
 CAN_InitTypeDef        CAN_InitStructure;
 CAN_FilterInitTypeDef  CAN_FilterInitStructure;
 extern GPIO_InitTypeDef  GPIO_InitStructure;
 uint8_t current_mailbox,transmit_state, send_data_flag, balance, charge, discharge, tmp, j;
 char error[8], RESOURCE[8], CYCLE_COUNT[4];
 u16 broadcast_ID = 0x100, RX_ADDRESS, RX_ADDRESS1 = 0x201, TX_ADDRESS, defoltADR = 0x150;
// // Batteries variables
 unsigned short I, T[29], U[14], Uab, C1, C2, TDCH, TCH;
 uint8_t  B1;
 u8 cmd, boot_flag=0, TX_mailBox;
 // CAN variables
 CanTxMsg TxMessage, DATA_message, ERROR_message, RESOURCE_message, BALANCE_message, CHARGE_message, DISCHARGE_message;
 CanRxMsg RxMessage_0, RxMessage_1;
 //int cnt;
 //int cnt;
 extern uint16_t ProcPWM;
 
extern char Master_CAN, RegOn, PWR_ON, STB_ON;
extern char RegOn, UprOn, Error_out, Error_out_buff;
extern uint16_t counter7, U_big, i_real, i_desired, UprADC, U_input,i_max_desired,U_output;
short Counter_Slave_On, CounterTestOn;
 extern short Stop_ModeCounter;
 extern char Stop_Mode;
 extern uint16_t Tcomp, Sin;
 extern uint16_t F_trm, F_com;
 
 uint16_t PultTestMode = 0;
 uint16_t PultTestActiveCh = 0;
 uint16_t PultTestPWM = 0;



 void init_CAN1(void)
 {
 	// GPIO
	 
	 if(Master_CAN) {
			TX_ADDRESS = broadcast_ID;
		  RX_ADDRESS = defoltADR;
	 }
	 else {
		 RX_ADDRESS = broadcast_ID;
		 TX_ADDRESS = defoltADR;
	 }
	 
   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);		
   GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_8|GPIO_Pin_9;
   GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AF;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
   GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
   GPIO_Init(GPIOB, &GPIO_InitStructure);
   GPIO_PinAFConfig(GPIOB, GPIO_PinSource8, GPIO_AF_CAN1);//CAN1RX
   GPIO_PinAFConfig(GPIOB, GPIO_PinSource9, GPIO_AF_CAN1);//CAN1TX
 //----------------------------
 	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
 	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE); // In case you are using CAN2 only, you have to enable the CAN1 clock.
  CAN_DeInit(CAN1);
  CAN_DBGFreeze(CAN1, DISABLE);
   CAN_StructInit(&CAN_InitStructure);	
	 
 	 CAN_InitStructure.CAN_TTCM = DISABLE; 
   CAN_InitStructure.CAN_ABOM = ENABLE;  
   CAN_InitStructure.CAN_AWUM = ENABLE;
   CAN_InitStructure.CAN_NART = ENABLE;  
   CAN_InitStructure.CAN_RFLM = DISABLE;
   CAN_InitStructure.CAN_TXFP = ENABLE;
   CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;
	 
  //(42Mhz/12 = 3.5 MHz / (1+3+3) = 500 Kbps => 12
	//(42Mhz/6 = 7 MHz / (1+3+3) = 1000 Kbps = 12
   CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;//CAN_SJW_1tq;  
   CAN_InitStructure.CAN_BS1 = CAN_BS1_3tq;//CAN_BS1_1tq;
   CAN_InitStructure.CAN_BS2 = CAN_BS2_3tq;//CAN_BS2_4tq;
   CAN_InitStructure.CAN_Prescaler = 6;//6=1mega  
 	CAN_Init(CAN1, &CAN_InitStructure);
 //FIFO 0 filter for data requests
   CAN_FilterInitStructure.CAN_FilterNumber				= 0;   // 14 or higher for CAN2
   CAN_FilterInitStructure.CAN_FilterMode					= CAN_FilterMode_IdList;
   CAN_FilterInitStructure.CAN_FilterScale					= CAN_FilterScale_32bit;
   CAN_FilterInitStructure.CAN_FilterIdHigh				= (RX_ADDRESS1<<5);
   CAN_FilterInitStructure.CAN_FilterIdLow       	= 0x0000;
   CAN_FilterInitStructure.CAN_FilterMaskIdHigh		= 0xFFFF;
   CAN_FilterInitStructure.CAN_FilterMaskIdLow			= 0xFFFF;
   CAN_FilterInitStructure.CAN_FilterFIFOAssignment= 0;
   CAN_FilterInitStructure.CAN_FilterActivation		= ENABLE;
   CAN_FilterInit(&CAN_FilterInitStructure);  
 // FIFO1 filter  for commands 	
 	CAN_FilterInitStructure.CAN_FilterNumber				= 1;   // 14 or higher for CAN2
   CAN_FilterInitStructure.CAN_FilterMode					= CAN_FilterMode_IdList;
   CAN_FilterInitStructure.CAN_FilterScale					= CAN_FilterScale_32bit;
   CAN_FilterInitStructure.CAN_FilterIdHigh				= (RX_ADDRESS<<5);
   CAN_FilterInitStructure.CAN_FilterIdLow       	= 0x0000;
   CAN_FilterInitStructure.CAN_FilterMaskIdHigh		= 0xFFFF;
   CAN_FilterInitStructure.CAN_FilterMaskIdLow			= 0xFFFF;
   CAN_FilterInitStructure.CAN_FilterFIFOAssignment= 1;
   CAN_FilterInitStructure.CAN_FilterActivation		= ENABLE;
   CAN_FilterInit(&CAN_FilterInitStructure); 

 	CAN1->IER |= 0<<0;		// Transmit mailbox empty interrupt enable
 	CAN1->IER |= 1<<1;		// FIFO0 message pending interrupt enable
 	CAN1->IER |= 1<<2;		// FIFO0 full interrupt enable
 	CAN1->IER |= 1<<4;		// FIFO1 message pending interrupt enable
 	CAN1->IER |= 1<<5;		// FIFO1 full interrupt enable

 // NVIC  
 	NVIC_EnableIRQ(CAN1_RX0_IRQn);
 	NVIC_EnableIRQ(CAN1_RX1_IRQn);
 	NVIC_EnableIRQ(CAN1_TX_IRQn);
 }
// //==================================================================================================
 void Fill_data_message(void)
 {
 	DATA_message.StdId 	= TX_ADDRESS;
 	DATA_message.RTR		= CAN_RTR_DATA;
 	DATA_message.IDE 		= CAN_ID_STD;			
   DATA_message.DLC 		= 8;
// // Data messages

 	DATA_message.Data[0] = 0xAA;
	 
	if(Master_CAN)	{	 
					DATA_message.Data[1] = 0xAB;
					DATA_message.Data[2] = 0xAC;
					DATA_message.Data[3] = U_output>>4;//CH_V_LED
					DATA_message.Data[4] = Sin;
					DATA_message.Data[5] = Sin>>8;
					DATA_message.Data[6] = U_input>>4;//CH_V_BUS
					DATA_message.Data[7] = RegOn | (PWR_ON << 1) | (STB_ON<<2);
	}
// 	TX_mailBox = CAN_Transmit(CAN1, &DATA_message);		// TX data to PC
// 	while(CAN_TransmitStatus(CAN1, TX_mailBox)!=CAN_TxStatus_Ok){};


 }
 
 
 // //==================================================================================================
uint16_t Signals; 
 
 
void Fill_data_test_message(void)
{

	 
 	DATA_message.StdId 	= broadcast_ID;
 	DATA_message.RTR		= CAN_RTR_DATA;
 	DATA_message.IDE 		= CAN_ID_STD;			
   DATA_message.DLC 		= 8;
// // Data messages
	 
	if(STB_IN_PORT) Signals |= 0x1;
	else Signals  &= ~0x1;

	if(ERR_IN_PORT) Signals |= 0x2;
	else Signals  &= ~0x2;	 
	 
	if(MASTER_IN_PORT) Signals |= 0x4;
	else Signals  &= ~0x4;

	if(VOFF_IN_PORT) Signals |= 0x8;
	else Signals  &= ~0x8;	 
	 
 	DATA_message.Data[0] = 0xAA;	 
	DATA_message.Data[1] = 0xAB;
	DATA_message.Data[2] = 0xAC;
	DATA_message.Data[3] = 0;
	DATA_message.Data[4] = Signals;
	DATA_message.Data[5] = F_com >> 4;
	DATA_message.Data[6] = ProcPWM >> 7;
	DATA_message.Data[7] = F_trm >> 4;

// 	TX_mailBox = CAN_Transmit(CAN1, &DATA_message);		// TX data to PC
// 	while(CAN_TransmitStatus(CAN1, TX_mailBox)!=CAN_TxStatus_Ok){};


}
//================================================================================================

//================================================================================================
void CAN1_TX_IRQHandler(void)  
 { 
   if (CAN_GetITStatus(CAN1,CAN_IT_TME)) 
   {
       CAN_ClearITPendingBit(CAN1,CAN_IT_TME);
   }
 }
// //==================================================================================================
 // data requests handler 
 void CAN1_RX0_IRQHandler(void)
 {
 	if (CAN_GetITStatus(CAN1,CAN_IT_FF0)) 
 	{
 		CAN_ClearITPendingBit(CAN1,CAN_IT_FF0);
 	}
 	if (CAN_GetITStatus(CAN1,CAN_IT_FMP0)) 
 	{
 		CAN_ClearITPendingBit(CAN1,CAN_IT_FMP0);
 	}
 //// RX-ed message read & answer
   CAN_Receive(CAN1, CAN_FIFO0, &RxMessage_0);
	
	
					if(	(RxMessage_0.Data[0]==0xAA) && 
											(RxMessage_0.Data[1]==0xAB) && 
											(RxMessage_0.Data[2]==0xAC) &&
											(PultTestMode == 1)
						)	
					{
//									PultTestMode = 1;		
									CounterTestOn = 0;
									PultTestPWM	=	RxMessage_0.Data[6];
									PultTestActiveCh = RxMessage_0.Data[7];
					}
	
	
 	//cmd = RxMessage_0.Data[0];	
 
 	Fill_data_test_message();								// write data according to request 
 	CAN_Transmit(CAN1, &DATA_message);		// TX data to PC

 }
// //==================================================================================================

 // commands handler
 void CAN1_RX1_IRQHandler(void)
 {
  if (CAN_GetITStatus(CAN1,CAN_IT_FF1)) 
 	{CAN_ClearITPendingBit(CAN1,CAN_IT_FF1);}
 	if (CAN_GetITStatus(CAN1,CAN_IT_FMP1)) 
 	{	CAN_ClearITPendingBit(CAN1,CAN_IT_FMP1);}
 // RX-ed data read
 	CAN_Receive(CAN1, CAN_FIFO1, &RxMessage_1);
 	//cmd = RxMessage_1.Data[0];
	if(!Master_CAN) {

					if(	(RxMessage_1.Data[0]==0xAA) && 
											(RxMessage_1.Data[1]==0xAB) && 
											(RxMessage_1.Data[2]==0xAC))	{
													Counter_Slave_On = 0;
												  Error_out &= ~ERROR_CAN;
													Sin = (((uint16_t)RxMessage_1.Data[5])<<8) + RxMessage_1.Data[4];	
													RegOn = (RxMessage_1.Data[7] & 1);
													PWR_ON = ((RxMessage_1.Data[7]>>1) & 1);
													STB_ON = ((RxMessage_1.Data[7]>>2) & 1);							
					}
						
	}

 	//Fill_data_message();								// write data according to request 
 	//CAN_Transmit(CAN1, &DATA_message);
 	
 }
// //==================================================================================================
