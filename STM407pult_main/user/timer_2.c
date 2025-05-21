#include "include.h"
uint8_t tx_not_complete, tx_not_complete6;
typedef char byte;

TIM_TimeBaseInitTypeDef TIM_InitStruct_2;
unsigned short SPI_1_Counter, CountTime, SPI_1_Counter_TO, CountTime180ms, Alarm_counter;
char Read_h,Read_l,num_send,test_i2c;

uint16_t step, dac1=0, dac2=0;

//==========================================================================================================================================
void Timer_2_init(void)  				// 32 bit timer!
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	TIM_InitStruct_2.TIM_CounterMode 			= TIM_CounterMode_Up;
	TIM_InitStruct_2.TIM_Prescaler				= 84-1;					// prescaler for bus clock 
	TIM_InitStruct_2.TIM_Period						= 100;					// 1000000 = 1 s period, 100 = 100 mKS
	TIM_TimeBaseInit(TIM2, &TIM_InitStruct_2);							
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	NVIC_EnableIRQ(TIM2_IRQn); 
	TIM_Cmd(TIM2, ENABLE);
 }
//==========================================================================================================================================
//uint16_t toggle=0;
uint16_t TimeOfAdcMeasuring = 0;
uint16_t TimeOfDisplayRun = 0;
uint16_t TimeOverrun = 0;
char dispStart =0;
uint16_t c1=0, c2=0;
uint16_t Tik = 0;
 
uint16_t timer_get_tick(void)
{
		return Tik;
}	

extern CanTxMsg DATA_message;
uint16_t StartCounter = 0;

__STATIC_INLINE void Time300mS(void)
{			
		if(c2 < 30) c2++;
		else 	
		{
			c2 = 0;					
			if(testTimeDisp == Disp_process_off) testTimeDisp = Disp_process_start;	//если предыдущий процесс вывода на экран звершён, то начинаем новый					
			else TimeOverrun++;
		}		
		if(StartCounter < START_TIME) StartCounter++;
}


__STATIC_INLINE void Time10mS(void)
{			
			if(c1 < 100) c1++;
			else 
			{
				
				if((!CanMaster) || (TestMode))
				{
							can1_Counter_Slave_Timeout++;
							if(can1_Counter_Slave_Timeout >= 50) { // если 500 мс не приходит посылка по CAN, то это потеря связи
										Error_CAN |= 1;
							}																	
				}
				c1 = 0;				
				Time300mS();					
			}
}

__STATIC_INLINE void timerCalcTimeDisplayOutputTime(void)
{
			if(testTimeDisp == Disp_process_ended)
			{
				testTimeDisp = Disp_process_off;
				TimeOfDisplayRun = c1 + (c2 * 100); // 1 = 100 mkS - Считает время вывода на экран
				ADC1->CR2|= 1<<30; // Запуск АЦП по окончании каждого вывода на экран
			}				
}


void TIM2_IRQHandler(void) //100mkS
{
			TIM_ClearITPendingBit(TIM2, TIM_IT_Update);	
			Tik++;			
			can_send_counter++;
			timerCalcTimeDisplayOutputTime();			
			Time10mS();
			FMSTR_Poll();
//			FMSTR_Recorder();	
}


