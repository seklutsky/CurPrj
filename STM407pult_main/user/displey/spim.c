
#include "include.h"


//==============================================================================
// Процедура инициализации spi (SPI1 или SPI2) в режиме master
//==============================================================================
void spim_init(SPI_TypeDef* SPIx, uint8_t WordLen)
{
  // Стартуем тактирование GPIO и SPI
  if (SPIx == SPI1)
  {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
  }
  else
  {
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
		RCC_APB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
  }
  
  // Настраиваем SPI
  SPI_Cmd(SPIx, DISABLE); 
  SPI_InitTypeDef SPI_InitStruct;
  SPI_InitStruct.SPI_Direction = SPI_Direction_1Line_Tx;
  SPI_InitStruct.SPI_Mode = SPI_Mode_Master;
//  SPI_InitStruct.SPI_DataSize = (WordLen == 16) ? SPI_DataSize_16b : SPI_DataSize_8b;
  SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;
  SPI_InitStruct.SPI_CPOL = SPI_CPOL_Low;
  SPI_InitStruct.SPI_CPHA = SPI_CPHA_1Edge;
  SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;
  SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_128;
  SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStruct.SPI_CRCPolynomial = 0x7;
  SPI_Init(SPIx, &SPI_InitStruct);
  SPI_Cmd(SPIx, ENABLE);
    
  // Настраиваем ноги GPIO для сигналов SCK и MOSI
  GPIO_InitTypeDef InitStruct;
  InitStruct.GPIO_Mode = GPIO_Mode_AF;
  InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	InitStruct.GPIO_OType = GPIO_OType_PP;
  InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	
	
  if (SPIx == SPI1)
  {
    InitStruct.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_7;
    GPIO_Init(GPIOA, &InitStruct);
  }
  else
  {
    InitStruct.GPIO_Pin = GPIO_Pin_13 ;
    GPIO_Init(GPIOB, &InitStruct);

    InitStruct.GPIO_Pin = GPIO_Pin_3 ;
    GPIO_Init(GPIOC, &InitStruct);
		
		GPIO_PinAFConfig(GPIOB, GPIO_PinSource13, GPIO_AF_SPI2); //SCK
		GPIO_PinAFConfig(GPIOC, GPIO_PinSource3, GPIO_AF_SPI2); //MOSI
  }

  // Настраиваем ножку GPIO для сигнала MISO
  InitStruct.GPIO_Mode = GPIO_Mode_AF;
  InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  if (SPIx == SPI1)
  {
    InitStruct.GPIO_Pin = GPIO_Pin_6;
    GPIO_Init(GPIOA, &InitStruct);
  }
  else
  {
    //InitStruct.GPIO_Pin = GPIO_Pin_14;
   // GPIO_Init(GPIOB, &InitStruct);
  }
}
//==============================================================================


//==============================================================================
// Процедура отправляет массив 16-битных слов
//==============================================================================
void SPI_send16b(SPI_TypeDef* SPIx, uint16_t *pBuff, uint16_t Len)
{
  for (uint16_t i = 0; i < Len; i++)
  {
    SPI_I2S_SendData(SPIx, *(pBuff++));
    while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_BSY) == SET) ;
  }
}
//==============================================================================


//==============================================================================
// Процедура отправляет массив 8-битных слов
//==============================================================================
void SPI_send8b(SPI_TypeDef* SPIx, uint8_t *pBuff, uint16_t Len)
{
  for (uint16_t i = 0; i < Len; i++)
  {
    SPI_I2S_SendData(SPIx, *(pBuff++));
		delay_ms(1);
    while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_BSY) == SET) ;
  }
}
//==============================================================================


//==============================================================================
// Процедура отправляет массив 16-битных слов
//==============================================================================
void SPI_recv16b(SPI_TypeDef* SPIx, uint16_t *pBuff, uint16_t Len)
{
  for (uint16_t i = 0; i < Len; i++)
  {
    SPI_I2S_SendData(SPIx, 0xFFFF);
    while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_TXE) == RESET) ;
    *(pBuff++) = SPI_I2S_ReceiveData(SPIx);
  }
}//==============================================================================


//==============================================================================
// Процедура отправляет массив 8-битных слов
//==============================================================================
void SPI_recv8b(SPI_TypeDef* SPIx, uint8_t *pBuff, uint16_t Len)
{
  for (uint16_t i = 0; i < Len; i++)
  {
    SPI_I2S_SendData(SPIx, 0xFF);
    while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_TXE) == RESET) ;
    *(pBuff++) = SPI_I2S_ReceiveData(SPIx);
  }
}
//==============================================================================
