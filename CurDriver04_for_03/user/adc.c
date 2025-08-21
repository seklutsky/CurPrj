#include "include.h"
ADC_InitTypeDef ADC_InitStructure;
ADC_CommonInitTypeDef adc_init, ADC_CommonInitStructure;
float current, val_f1, val_f2;
int i, l;
int16_t val1, val2, val3,val4,val5,val6, Ibus, V_led, V_bus, F_com, U_output;
uint16_t F_trm, F_trm_,F_trm__, ARR_F_TRM[32768], F5V = U5V, deltaT = 0;
uint32_t ACC_F_TRM;
uint16_t i_ARR=0;
uint16_t current_X10mA, voltage_X10mV;
float voltage;
int16_t median, tmp_, CURRENT[32], VOLTAGE[32];
char temp1, temp2;
extern GPIO_InitTypeDef  GPIO_InitStructure;
long int current_sum1 = 0, current_sum2 = 0, current_sum = 0,ADC_counter,ADC_counter1,ADC_counter2,ADC_counter3,ADC_counter4,ADC_counter5;
char ADC_ch=0,_ADC_ch=1,ADC_INIT_DONE=0;
extern uint16_t counter7, U_big, i_real, i_desired, UprADC, U_input,i_max_desired;
extern void RegCurrent(void);





char ch_num[6] = {CH_I_LED,CH_V_BUS,CH_V_LED,CH_I_BUS,CH_F_COM,CH_F_TRM};


typedef struct {
	int16_t Value16in;		// Нефильрованное значение
	int16_t Value16filtered;	// Фильрованное значение
	int32_t Value32;			// Конечное напряжение тренировки
	int16_t ShiftFilter;		// Filters
} Filtered;

Filtered T_Filter={0, 0, 0, FILTER_T}; 

int16_t Filter(int16_t inValue, Filtered *Struct);


void ADC_init(void)
{

			ADC_CommonStructInit(&adc_init);
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
		  ADC_RegularChannelConfig(ADC1, CH_I_BUS, 1, ADC_SampleTime_);	
	
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);		// Enable clock for GPIO_C
			GPIO_InitStructure.GPIO_OType 	= GPIO_OType_PP;
			GPIO_InitStructure.GPIO_PuPd 		= GPIO_PuPd_NOPULL;
			GPIO_InitStructure.GPIO_Mode 		= GPIO_Mode_AN;		
			GPIO_InitStructure.GPIO_Pin 		= GPIO_Pin_0|GPIO_Pin_1;
			GPIO_Init(GPIOC, &GPIO_InitStructure);
			
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);		// Enable clock for GPIO_B
			GPIO_InitStructure.GPIO_OType 	= GPIO_OType_PP;
			GPIO_InitStructure.GPIO_PuPd 		= GPIO_PuPd_NOPULL;
			GPIO_InitStructure.GPIO_Mode 		= GPIO_Mode_AN;		
			GPIO_InitStructure.GPIO_Pin 		= GPIO_Pin_0|GPIO_Pin_1;
			GPIO_Init(GPIOB, &GPIO_InitStructure);
			
				
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);		// Enable clock for GPIO_A
			GPIO_InitStructure.GPIO_OType 	= GPIO_OType_PP;
			GPIO_InitStructure.GPIO_PuPd 		= GPIO_PuPd_NOPULL;
			GPIO_InitStructure.GPIO_Mode 		= GPIO_Mode_AN;		
			GPIO_InitStructure.GPIO_Pin 		= GPIO_Pin_6|GPIO_Pin_7;
			GPIO_Init(GPIOA, &GPIO_InitStructure);
			
			ADC_INIT_DONE = 1;
			
}

extern uint8_t NotTest, NoCheck;
//=============================================================================
void ADC_IRQHandler(void)
{
	  if (ADC_GetITStatus(ADC1,ADC_IT_EOC)==SET)   {

						ADC1->SR &=~(1<<1);		
						switch(ADC_ch) {
							
									case 0: 
										      i_real = ADC1->DR;													
													ADC_ch=_ADC_ch+1;
													ADC_RegularChannelConfig(ADC1, ch_num[ADC_ch], 1, ADC_SampleTime_);	
													RegCurrent();
													StartADC;
													ADC_counter++;		
									
													// Freemaster Recoder
													FMSTR_Recorder();
									break;							
									case 1: //CH_V_BUS
									        U_input = ADC1->DR;
													ADC_counter1++;
													ADC_INIT_DONE=1;
									break;
									case 2: //CH_V_LED
													U_output = ADC1->DR;
													ADC_counter2++;
													ADC_INIT_DONE=1;
									break;
									case 3:
													Ibus = ADC1->DR;
													ADC_counter3++;
													ADC_INIT_DONE=1;
									break;
									case 4:
													F_com = ADC1->DR;
													if(F_com < U25V) UprADC=F_com;
													else UprADC=U25V;
													ADC_counter4++;
													ADC_INIT_DONE=1;
									break;
									case 5:
													ACC_F_TRM += ARR_F_TRM[i_ARR] = F_trm = val5 = ADC1->DR;
													i_ARR++; i_ARR &= 0x7FFF;
													ACC_F_TRM -= ARR_F_TRM[i_ARR];
													F_trm_ = (ACC_F_TRM >> 15) + deltaT;
													F_trm__=Filter(F_trm_, &T_Filter);											
													ADC_counter5++;
													ADC_ch=0;
													ADC_INIT_DONE=1;										
									break;

									default:
													ADC_ch=0;
						}	
	   }

}
//=============================================================================
short median_filter (short* data_array, uint8_t array_size)
{
// bubble sort
	for (i = 0; i<array_size; i++)
	{
		for (l=(i+1); l<array_size; l++)
		if (data_array[i] < data_array[l]) 
			{
				tmp_ = data_array[i];
				data_array[i] = data_array[l];
				data_array[l] = tmp_; 
			}	
			
	}
median = data_array[array_size/2];
return median;
}
//==================================
short median_filter_my (short* data_array, uint8_t array_size)
{
	current_sum = 0;
	for (i = 0; i<array_size; i++)
	{
			current_sum += data_array[i];		
	}
median = current_sum/array_size;
return median;
}




// Фильтр сигнала
int16_t Filter(int16_t inValue, Filtered *Struct) {	
	(*Struct).Value16in = inValue;	
	(*Struct).Value32+=(int32_t)((*Struct).Value16in)-(int32_t)((*Struct).Value16filtered);
	(*Struct).Value16filtered =(int16_t)(((*Struct).Value32)>>((*Struct).ShiftFilter));
	return ((*Struct).Value16filtered);
}
