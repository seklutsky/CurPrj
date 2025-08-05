#include "include.h"

CAN_InitTypeDef        CAN_InitStructure;
CAN_FilterInitTypeDef  CAN_FilterInitStructure;
GPIO_InitTypeDef  GPIO_InitStructure_B,GPIO_InitStructure;
uint8_t current_mailbox,transmit_state, send_data_flag, balance, charge, discharge, tmp, j;
char error[8], RESOURCE[8], CYCLE_COUNT[4];
u16 broadcast_ID = 0x011, US_BM1_RX_ID = 0x015, US_BM1_TX_ID = 0x104; // adress
// Batteries variables
unsigned short I, T[29], U[14], Uab, C1, C2, TDCH, TCH;
uint8_t  B1;
u8 cmd, boot_flag=0, TX_mailBox, tx_status;
// CAN variables
CanTxMsg TxMessage, DATA_message, ERROR_message, RESOURCE_message, BALANCE_message, CHARGE_message, DISCHARGE_message;
CanRxMsg RxMessage_0, RxMessage_1;
//int cnt;
void init_CAN2(void)
{
	// GPIO
 	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);		
	GPIO_InitStructure_B.GPIO_Pin 	= GPIO_Pin_6|GPIO_Pin_5;
  GPIO_InitStructure_B.GPIO_Mode 	= GPIO_Mode_AF;
  GPIO_InitStructure_B.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure_B.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure_B.GPIO_PuPd  = GPIO_PuPd_UP;
  GPIO_Init(GPIOB, &GPIO_InitStructure_B);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_CAN2);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource5, GPIO_AF_CAN2);
//----------------------------
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN2, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE); // In case you are using CAN2 only, you have to enable the CAN1 clock.
  CAN_DeInit(CAN2);
	CAN_DBGFreeze(CAN2, DISABLE);
  CAN_StructInit(&CAN_InitStructure);	
	CAN_InitStructure.CAN_TTCM = DISABLE; 
  CAN_InitStructure.CAN_ABOM = DISABLE;  // automatic bus off reinit
  CAN_InitStructure.CAN_AWUM = ENABLE;
  CAN_InitStructure.CAN_NART = ENABLE;  // disable retransmission
  CAN_InitStructure.CAN_RFLM = DISABLE;
  CAN_InitStructure.CAN_TXFP = ENABLE;
  CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;
// (42Mhz/12 = 3.5 MHz / (1+3+3) = 500 Kbps
  CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;//CAN_SJW_1tq;  
  CAN_InitStructure.CAN_BS1 = CAN_BS1_3tq;//CAN_BS1_1tq;
  CAN_InitStructure.CAN_BS2 = CAN_BS2_3tq;//CAN_BS2_4tq;
  CAN_InitStructure.CAN_Prescaler = 12; // 500
//  CAN_InitStructure.CAN_Prescaler = 120; // 50
	CAN_Init(CAN2, &CAN_InitStructure);
//FIFO 0 filter for data requests
  CAN_FilterInitStructure.CAN_FilterNumber				= 14;   // 14 or higher for CAN2
  CAN_FilterInitStructure.CAN_FilterMode					= CAN_FilterMode_IdList;
  CAN_FilterInitStructure.CAN_FilterScale					= CAN_FilterScale_32bit;
  CAN_FilterInitStructure.CAN_FilterIdHigh				= (broadcast_ID<<5);					// broadcast identifier 
  CAN_FilterInitStructure.CAN_FilterIdLow       	= 0x0000;
  CAN_FilterInitStructure.CAN_FilterMaskIdHigh		= 0xFFFF;
  CAN_FilterInitStructure.CAN_FilterMaskIdLow			= 0xFFFF;
  CAN_FilterInitStructure.CAN_FilterFIFOAssignment= 0;
  CAN_FilterInitStructure.CAN_FilterActivation		= ENABLE;
  CAN_FilterInit(&CAN_FilterInitStructure);  
// FIFO1 filter  for commands 	
	CAN_FilterInitStructure.CAN_FilterNumber				= 15;   // 14 or higher for CAN2
  CAN_FilterInitStructure.CAN_FilterMode					= CAN_FilterMode_IdList;
  CAN_FilterInitStructure.CAN_FilterScale					= CAN_FilterScale_32bit;
  CAN_FilterInitStructure.CAN_FilterIdHigh				= (RX_ADDRESS<<5);				// specified identifier for 1-st block 
  CAN_FilterInitStructure.CAN_FilterIdLow       	= 0x0000;
  CAN_FilterInitStructure.CAN_FilterMaskIdHigh		= 0xFFFF;
  CAN_FilterInitStructure.CAN_FilterMaskIdLow			= 0xFFFF;
  CAN_FilterInitStructure.CAN_FilterFIFOAssignment= 1;
  CAN_FilterInitStructure.CAN_FilterActivation		= ENABLE;
  CAN_FilterInit(&CAN_FilterInitStructure); 
// interrupt enable 
	CAN_ITConfig(CAN2, CAN_IT_FMP0, ENABLE);  // CAN2 FIFO0 message pending interrupt enable 
	CAN_ITConfig(CAN2, CAN_IT_FF0, ENABLE);  	// CAN2 FIFO0 full interrupt enable 
	CAN_ITConfig(CAN2, CAN_IT_FMP1, ENABLE);  // CAN2 FIFO1 message pending interrupt enable 
  CAN_ITConfig(CAN2, CAN_IT_FF1, ENABLE);  	// CAN2 FIFO1 full interrupt enable 
	CAN_ITConfig(CAN2, CAN_IT_FMP1, ENABLE);  // CAN2 FIFO0 message pending interrupt enable 
  CAN_ITConfig(CAN2, CAN_IT_FF1, ENABLE);  // CAN2 FIFO1 message pending interrupt enable 
	CAN_ITConfig(CAN2, CAN_IT_TME, ENABLE); 	// CAN2 Transmit mailbox empty Interrupt enable
// NVIC  
	NVIC_EnableIRQ(CAN2_RX0_IRQn);
	NVIC_EnableIRQ(CAN2_RX1_IRQn);
	NVIC_EnableIRQ(CAN2_TX_IRQn);
}
//==================================================================================================

//==================================================================================================
void CAN2_TX_IRQHandler(void)  
{ 
  if (CAN_GetITStatus(CAN2,CAN_IT_TME)) 
  {
      CAN_ClearITPendingBit(CAN2,CAN_IT_TME);
  }
}
//==================================================================================================
// bradcast request handler
void CAN2_RX0_IRQHandler(void)
{
	if (CAN_GetITStatus(CAN2,CAN_IT_FF0)) 
	{
		CAN_ClearITPendingBit(CAN2,CAN_IT_FF0);
	}
	if (CAN_GetITStatus(CAN2,CAN_IT_FMP0)) 
	{
		CAN_ClearITPendingBit(CAN2,CAN_IT_FMP0);
	}
// RX-ed message read & answer
  CAN_Receive(CAN2, CAN_FIFO0, &RxMessage_0);
	cmd = RxMessage_0.Data[0];	
	if (cmd <=1) {
	
	tx_status = CAN_Transmit(CAN2, &DATA_message);		// TX data to PC
	while(CAN_TransmitStatus(CAN2, tx_status)!=CAN_TxStatus_Ok);	
	};
}
//==================================================================================================
// specified US_BM identifier ID interrupt
void CAN2_RX1_IRQHandler(void)
{
	if (CAN_GetITStatus(CAN2,CAN_IT_FF1)) 
	{CAN_ClearITPendingBit(CAN2,CAN_IT_FF1);}
	if (CAN_GetITStatus(CAN2,CAN_IT_FMP1)) 
	{	CAN_ClearITPendingBit(CAN2,CAN_IT_FMP1);}
// RX-ed data read
	CAN_Receive(CAN2, CAN_FIFO1, &RxMessage_1);
	cmd = RxMessage_1.Data[0];
	CAN_Transmit(CAN2, &DATA_message);
}
//==================================================================================================
