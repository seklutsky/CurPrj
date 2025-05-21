 #include "include.h"
 

uint16_t broadcast_ID = 0x100, RX_ADDRESS, TX_ADDRESS1 = 0x201, TX_ADDRESS, defoltADR = 0x150;
char can_send_counter = 0; 
char can_end_time = 25;//25*0.1 = 2.5 mkS
short can1_Counter_Slave_Timeout;
 
 
char	 STB_ON = 0; 
char	 Error_CAN = 0;
char   RegOn = 0;  
char   Error_out = 0; 
char   PWR_ON = 0;
uint16_t 	V_led, V_bus;


uint16_t  i_real;
uint16_t  i_desired;
uint16_t  UprADC, ProcPWM, STB_IN_PORT, MASTER_IN_PORT, VOFF_IN_PORT, ERR_IN_PORT, TemperatureADC;
uint16_t  U_input;

uint16_t  Sin = 0;

CanTxMsg TxMessage;
CanRxMsg RxMessage;

void can_initGPIO(void)
{
	 GPIO_InitTypeDef GPIO_InitStructure;
	
   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);		
   GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_11|GPIO_Pin_12;
   GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AF;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
   GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
   GPIO_Init(GPIOA, &GPIO_InitStructure);
   GPIO_PinAFConfig(GPIOA, GPIO_PinSource11, GPIO_AF_CAN1);//CAN1RX
   GPIO_PinAFConfig(GPIOA, GPIO_PinSource12, GPIO_AF_CAN1);//CAN1TX	
}


void can1_init(char   Master_CAN)
{
 CAN_InitTypeDef        CAN_InitStructure;
 CAN_FilterInitTypeDef  CAN_FilterInitStructure;
	 
	 if(Master_CAN) {
			TX_ADDRESS = broadcast_ID;
		  RX_ADDRESS = defoltADR;
	 }
	 else {
		 RX_ADDRESS = broadcast_ID;
		 TX_ADDRESS = defoltADR;
	 }
	 

 //----------------------------
 	 RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
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
//   CAN_FilterInitStructure.CAN_FilterNumber				= 0;   // 14 or higher for CAN2
//   CAN_FilterInitStructure.CAN_FilterMode					= CAN_FilterMode_IdList;
//   CAN_FilterInitStructure.CAN_FilterScale					= CAN_FilterScale_32bit;
//   CAN_FilterInitStructure.CAN_FilterIdHigh				= (RX_ADDRESS1<<5);
//   CAN_FilterInitStructure.CAN_FilterIdLow       	= 0x0000;
//   CAN_FilterInitStructure.CAN_FilterMaskIdHigh		= 0xFFFF;
//   CAN_FilterInitStructure.CAN_FilterMaskIdLow			= 0xFFFF;
//   CAN_FilterInitStructure.CAN_FilterFIFOAssignment= 0;
//   CAN_FilterInitStructure.CAN_FilterActivation		= ENABLE;
//   CAN_FilterInit(&CAN_FilterInitStructure);  
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
// 	NVIC_EnableIRQ(CAN1_RX0_IRQn);
 	NVIC_EnableIRQ(CAN1_RX1_IRQn);
 	NVIC_EnableIRQ(CAN1_TX_IRQn);
}
//==================================================================================================  
 

 __STATIC_INLINE void Fill_data_message(void)
 {
 	TxMessage.StdId 	= TX_ADDRESS;
 	TxMessage.RTR		= CAN_RTR_DATA;
 	TxMessage.IDE 		= CAN_ID_STD;			
  TxMessage.DLC 		= 8;

 	TxMessage.Data[0] = 0xAA;	 
	TxMessage.Data[1] = 0xAB;
	TxMessage.Data[2] = 0xAC;
	TxMessage.Data[3] = Error_out;
	TxMessage.Data[4] = Sin;
	TxMessage.Data[5] = Sin>>8;
	TxMessage.Data[6] = 0;
	TxMessage.Data[7] = RegOn | (PWR_ON << 1) | (STB_ON<<2);
 }
 
  
//================================================================================================ 
void CAN_exchange(void) {			
				if(can_send_counter >= can_end_time) 
				{
					can_send_counter = 0;
					Error_out = 0;
					RegOn = 1;
					PWR_ON = 1;
					STB_ON = 1;					
					Fill_data_message();
					CAN_Transmit(CAN1, &TxMessage);					
				}			
}
//================================================================================================ 
 __STATIC_INLINE void Fill_data_messageTest(uint16_t TestPwm, uint16_t ActiveCh)
 {
 	TxMessage.StdId 	= TX_ADDRESS1;
 	TxMessage.RTR		= CAN_RTR_DATA;
 	TxMessage.IDE 		= CAN_ID_STD;			
  TxMessage.DLC 		= 8;

 	TxMessage.Data[0] = 0xAA;	 
	TxMessage.Data[1] = 0xAB;
	TxMessage.Data[2] = 0xAC;
	TxMessage.Data[3] = 0;
	TxMessage.Data[4] = 0;
	TxMessage.Data[5] = 0;
	TxMessage.Data[6] = TestPwm;
	TxMessage.Data[7] = ActiveCh;
 }
 
  
//================================================================================================ 
void CAN_exchangeTest(uint16_t TestPwm, uint16_t ActiveCh) {			
				if(can_send_counter >= can_end_time) 
				{
					can_send_counter = 0;				
					Fill_data_messageTest(TestPwm, ActiveCh);
					CAN_Transmit(CAN1, &TxMessage);					
				}			
} 
 
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
//   CAN_Receive(CAN1, CAN_FIFO0, &RxMessage_0);
 	//cmd = RxMessage_0.Data[0];	
 
 	//Fill_data_message();								// write data according to request 
 	//CAN_Transmit(CAN1, &DATA_message);		// TX data to PC

 }
// //==================================================================================================
 uint16_t Signals = 0;
 // commands handler
 void CAN1_RX1_IRQHandler(void)
 {
  if (CAN_GetITStatus(CAN1,CAN_IT_FF1)) 
 	{CAN_ClearITPendingBit(CAN1,CAN_IT_FF1);}
 	if (CAN_GetITStatus(CAN1,CAN_IT_FMP1)) 
 	{	CAN_ClearITPendingBit(CAN1,CAN_IT_FMP1);}
 // RX-ed data read
 	CAN_Receive(CAN1, CAN_FIFO1, &RxMessage);
 	//cmd = RxMessage_1.Data[0];
	if(TestMode)
	{
					if(	(RxMessage.Data[0]==0xAA) && 
											(RxMessage.Data[1]==0xAB) && 
											(RxMessage.Data[2]==0xAC))	{		
													can1_Counter_Slave_Timeout = 0;												
												  Error_CAN = 0;
													UprADC = RxMessage.Data[5];
												  ProcPWM = RxMessage.Data[6];
												  Signals = RxMessage.Data[4];
													TemperatureADC = RxMessage.Data[7];
													STB_IN_PORT = ((Signals) & 1);
													ERR_IN_PORT = ((Signals>>1) & 1);	
													MASTER_IN_PORT = ((Signals>>2) & 1);
													VOFF_IN_PORT = ((Signals>>3) & 1);													
					}			
	}
	else if(!CanMaster) {

					if(	(RxMessage.Data[0]==0xAA) && 
											(RxMessage.Data[1]==0xAB) && 
											(RxMessage.Data[2]==0xAC))	{		
													can1_Counter_Slave_Timeout = 0;												
												  Error_CAN = 0;
													Sin = (((uint16_t)RxMessage.Data[5])<<8) + RxMessage.Data[4];	
													RegOn = (RxMessage.Data[7] & 1);
													PWR_ON = ((RxMessage.Data[7]>>1) & 1);
													STB_ON = ((RxMessage.Data[7]>>2) & 1);	
												  V_led = RxMessage.Data[3];
												  V_bus = RxMessage.Data[6];
					}						
	}

 	//Fill_data_message();								// write data according to request 
 	//CAN_Transmit(CAN1, &DATA_message);
 	
 }
// //==================================================================================================

 
