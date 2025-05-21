#include "include.h"

u16 SPI_RX_Array[100], SPI_RX_count ;
u16 SPI_TX_Array[100], SPI_TX_count ;
extern NVIC_InitTypeDef NVIC_InitStructure;


void init_SPI(void)
{
SPI_InitTypeDef SPI_InitStructure ;	
GPIO_InitTypeDef GPIO_InitStructure;
	
//GPIO
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_14 ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_2 | GPIO_Pin_3 ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_10 ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOB, &GPIO_InitStructure);	
	
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_SPI2); //SCK
  GPIO_PinAFConfig(GPIOC, GPIO_PinSource2, GPIO_AF_SPI2); //MISO
  GPIO_PinAFConfig(GPIOC, GPIO_PinSource3, GPIO_AF_SPI2); //MOSI

//SPI
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);

  SPI_I2S_DeInit(SPI2);
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256; //42MHz / prescaler
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStructure.SPI_CRCPolynomial = 7;
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_Init(SPI2, &SPI_InitStructure);
	
  SPI_Cmd(SPI2, ENABLE);
	
  SPI_I2S_ITConfig(SPI2, SPI_I2S_IT_RXNE, ENABLE);

// NVIC
  NVIC_InitStructure.NVIC_IRQChannel = SPI2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);      	
}

void SPI2_IRQHandler (void) 
{
 

 if (SPI_I2S_GetITStatus(SPI2, SPI_I2S_IT_RXNE) == SET)
  {
	 SPI_RX_Array[SPI_RX_count] = SPI_I2S_ReceiveData(SPI2);
	 SPI_RX_count++;
		
	 SPI_TX_count++;	
   if(SPI_TX_count < SPI_TX_Array[0]) { SPI_I2S_SendData(SPI2, SPI_TX_Array[SPI_TX_count]);	}
	 else {SPI_RX_count = 0; SPI_TX_count = 0; } 
  }
}

uint32_t SPI_send(void) 
{
	u16 _i,Timeout_Delay_SPI ;
	
//	CS_HALL = 0 ;	CS_TORQ = 0 ;

	_i = 1 ;
	SPI_TX_Array[_i] = 0xAA ; _i++;
	SPI_TX_Array[_i] = 0xF1 ; _i++;
	SPI_TX_Array[_i] = 0x00 ; _i++;
	SPI_TX_Array[_i] = 0xFF ; _i++;
	SPI_TX_Array[_i] = 0x02 ; _i++;

	SPI_TX_Array[0] = _i;
	
	SPI_RX_count = 1 ;
	
	SPI_TX_count = 1 ;
  SPI_I2S_SendData(SPI2, SPI_TX_Array[SPI_TX_count]);	
	
	Timeout_Delay_SPI = SPI_TX_Array[0] << 1 ; //2ms / byte
 	while((SPI_TX_count != 0) && (Timeout_Delay_SPI |= 0));

//	CS_HALL = 1 ;	CS_TORQ = 1 ;

  return(Timeout_Delay_SPI);
}
