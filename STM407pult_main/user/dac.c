#include "include.h"

DAC_InitTypeDef DAC_InitStructure;


void DAC_Init_(void)
{
			GPIO_InitTypeDef GPIO_InitStructure;	
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);
			
			DAC_StructInit(&DAC_InitStructure);
			DAC_Init(DAC_Channel_1, &DAC_InitStructure);
			DAC_Init(DAC_Channel_2, &DAC_InitStructure);
			DAC_Cmd(DAC_Channel_1, ENABLE);
			DAC_Cmd(DAC_Channel_2, ENABLE);
			DAC_SetChannel1Data(DAC_Align_12b_R, 0);
			DAC_SetChannel2Data(DAC_Align_12b_R, 0);
	
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);		// Enable clock for GPIO_A
			GPIO_InitStructure.GPIO_OType 	= GPIO_OType_PP;
			GPIO_InitStructure.GPIO_PuPd 		= GPIO_PuPd_NOPULL;
			GPIO_InitStructure.GPIO_Mode 		= GPIO_Mode_AN;		
			GPIO_InitStructure.GPIO_Pin 		= GPIO_Pin_4 | GPIO_Pin_5;
			GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void DAC_set_level(uint16_t channel, uint16_t val)
{
		if(val > 0xFFF) val = 0xFFF;
		switch(channel)
		{
			case 1:
						DAC->DHR12R1 = val;//DAC_SetChannel1Data(DAC_Align_12b_R, val);
			break;
			case 2:
						DAC->DHR12R2 = val;//DAC_SetChannel2Data(DAC_Align_12b_R, val);
			break;
			default:
						DAC->DHR12R1 = val;//DAC_SetChannel1Data(DAC_Align_12b_R, val);
		}
	
}


