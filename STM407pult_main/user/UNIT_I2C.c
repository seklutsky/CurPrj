//#include "stm32f4xx.h"
//#include "math.h"
#include "include.h"

I2C_InitTypeDef I2C_InitStructure;

NVIC_InitTypeDef I2C_NVIC_InitStructure;
unsigned short Timeout_I2C;
//I2C1
//SDA - B9 / B7
//SCL - B8 / B6

void init_I2C_(void)
{
GPIO_InitTypeDef  GPIO_InitStructure;
	
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_7|GPIO_Pin_6;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_I2C1); 
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_I2C1); 

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
	
	I2C_Cmd(I2C1,ENABLE);

	I2C_DeInit(I2C1);
	
	
	I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_InitStructure.I2C_ClockSpeed = 300000;
	I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
	I2C_InitStructure.I2C_OwnAddress1 = 0xFF;
	
	I2C_Init(I2C1,&I2C_InitStructure);
	while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));
	
	
	I2C_ITConfig(I2C1, I2C_IT_BUF, ENABLE);
	
	
	// NVIC
  I2C_NVIC_InitStructure.NVIC_IRQChannel = I2C1_EV_IRQn;
  I2C_NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  I2C_NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  I2C_NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//  NVIC_Init(&NVIC_InitStructure); 

	
}


void I2C1_EV_IRQHandler (void)	{
	
		I2C_ClearITPendingBit(I2C1,I2C_IT_RXNE);
	  I2C_ClearITPendingBit(I2C1,I2C_IT_TXE);
	
}
