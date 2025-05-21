#include "include.h"

char testTimeADC = 0;
char ADC_ch=0;

Filtered T_Filter={0, 0, 0, 6}; 

int16_t Filter(int16_t inValue, Filtered *Struct);
void ADC_init_(void)
{
	ADC_InitTypeDef ADC_InitStructure;
	ADC_CommonInitTypeDef ADC_CommonInitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	
			ADC_CommonStructInit(&ADC_CommonInitStructure);
			ADC_CommonInitStructure.ADC_Mode 						 = ADC_Mode_Independent ; 

			ADC_CommonInitStructure.ADC_DMAAccessMode    = ADC_DMAAccessMode_Disabled;    
			ADC_CommonInitStructure.ADC_Prescaler 			 = ADC_Prescaler_Div2;                     // 84MHz/2 = 42
			ADC_CommonInit(&ADC_CommonInitStructure);
			
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

			ADC_StructInit(&ADC_InitStructure);
	
			ADC_InitStructure.ADC_Resolution 						= ADC_Resolution_12b;
			ADC_InitStructure.ADC_ScanConvMode 					= ENABLE;
			ADC_InitStructure.ADC_ContinuousConvMode 		= DISABLE;
			ADC_InitStructure.ADC_ExternalTrigConvEdge  = ADC_ExternalTrigConvEdge_None;//ADC_ExternalTrigConvEdge_Rising;
	    ADC_InitStructure.ADC_ExternalTrigConv			= ADC_ExternalTrigConv_T1_CC1;//ADC_ExternalTrigConv_T8_TRGO;//
			ADC_InitStructure.ADC_DataAlign 						= ADC_DataAlign_Right;
			ADC_InitStructure.ADC_NbrOfConversion 			= 1;

			
			ADC_Init(ADC1, &ADC_InitStructure);
		  ADC_Cmd(ADC1, ENABLE);
			ADC_ITConfig(ADC1, ADC_IT_EOC, ENABLE);
			

			
			NVIC_EnableIRQ(ADC_IRQn);
		  ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_84Cycles);	
	
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);		// Enable clock for GPIO_A
			GPIO_InitStructure.GPIO_OType 	= GPIO_OType_PP;
			GPIO_InitStructure.GPIO_PuPd 		= GPIO_PuPd_NOPULL;
			GPIO_InitStructure.GPIO_Mode 		= GPIO_Mode_AN;		
			GPIO_InitStructure.GPIO_Pin 		= GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_6 | GPIO_Pin_7;
			GPIO_Init(GPIOA, &GPIO_InitStructure);
						
//			ADC1->CR2|= 1<<30;			

}

char ch_num[ADC_ALL] = {I_P48V,I_LOAD,TERM_IN,CON_IN};
uint16_t ADC_result[ADC_ALL];

//=============================================================================
void ADC_IRQHandler(void)
{
	if (ADC_GetITStatus(ADC1,ADC_IT_EOC)==SET)
	{
						ADC_result[ADC_ch] = ADC1->DR;
						if(ADC_ch < ADC_ALL) 
						{
							ADC_ch++;
							ADC_RegularChannelConfig(ADC1, ch_num[ADC_ch], 1, ADC_SampleTime_84Cycles);
							ADC1->CR2|= 1<<30;
						}
						else 
						{
							ADC_ch = 0;
							ADC_RegularChannelConfig(ADC1, ch_num[ADC_ch], 1, ADC_SampleTime_84Cycles);
							testTimeADC = 1;
						}
						ADC1->SR &=~(1<<1);
	}
}
//=============================================================================

uint16_t getADCresult(uint16_t N)
{
	return ADC_result[N];
}
