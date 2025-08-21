#include "include.h"
#include <stdio.h>
#include <string.h>
#include "boot.h"

const unsigned int ArrT = 12;
const unsigned int ArrS = 12;



float Array[ArrS][ArrT] = {
    {     0,    10,	  15,	  20,	  25,	  30,	  35,	  40,	  45,	  50,	  55,	    60 },
    {     0,	 161,	 209,	 257,	 304,	 352,	 400,	 447,	 495,	 543,	 590,	    638},
		{	 2517,	1605,	1707,	1809,	1911,	2013,	2116,	2218,	2320,	2422,	2525,	   2627},
		{	 4064,	2494,	2630,	2765,	2901,	3037,	3173,	3310,	3447,	3584,	3722,	   3860},
		{	 5353,	3243,	3407,	3571,	3735,	3900,	4067,	4234,	4404,	4576,	4750,	   4928},
		{	 6427,	3884,	4071,	4259,	4449,	4640,	4835,	5034,	5238,	5449,	5669,	   5899},
		{	 7322,	4441,	4649,	4858,	5070,	5286,	5509,	5742,	5986,	6246,	6523,	   6824},
		{	 8068,	4934,	5158,	5385,	5618,	5859,	6112,	6381,	6671,	6989,	7339,	   7730},
		{	 8690,	5373,	5611,	5855,	6107,	6371,	6655,	6964,	7306,	7690,	8126,	   8624},
		{	 9208,	5765,	6016,	6274,	6543,	6831,	7146,	7496,	7894,	8351,	8881,	   9499},
		{	 9640,	6115,	6377,	6647,	6933,	7244,	7589,	7982,	8436,	8968,	9597,	  10343},
		{	10000,	6426,	6697,	6979,	7280,	7612,	7986,	8420,	8931,	9539,	10268,	11142}
   
};



char can_send=0, can_end = 100, Master_CAN = 0;//Master/slave;

void RegCurrent(void);
int32_t fxlog(uint32_t x); 
uint32_t div_32(uint32_t x, uint32_t y);
void PortsInit(void);
__STATIC_INLINE void All_Pwr_Off(void);
__STATIC_INLINE void All_Pwr_On(void);
__STATIC_INLINE void InitCAN_Master_Slave(void);
__STATIC_INLINE void Check_Err_Mode_Lamps(void);
__STATIC_INLINE void Temperature_Compute(void);
__STATIC_INLINE void CAN_exchange(void);
__STATIC_INLINE void CorrectTemperature (void);
__STATIC_INLINE void InitSynchro(void);
__STATIC_INLINE void Restart_Power_Charge(void);
__STATIC_INLINE void PWM_set(void);
__STATIC_INLINE void PultTest(void);

uint16_t test, counter7, Sin, Istep, U_big, I_tmp, U_tmp, i_real, i_desired, UprADC, U_input, PWM, i_real_kz = I_KZ,i_max_desired, Tcomp = TCOMP;
int16_t ostatok;
char First_Start1,First_Start4,First_Start3,First_Start8,First_Start5;
extern  CanTxMsg TxMessage, DATA_message;
extern s16 val1, val2, val3,val4,val5, Ibus, V_LED, V_BUS, F_COM, U_output;
extern uint16_t F_trm, F_trm_, F_trm__,F5V;
uint16_t Imax_izm = I_MAX_ABS;
extern uint16_t PultTestMode; 
extern uint16_t PultTestActiveCh;
extern uint16_t PultTestPWM;

typedef struct
{
    int16_t ProportionalGain;
    int16_t IntegralGain;
    int32_t IntegralPortion;
    int16_t PositivePILimit;
    int16_t NegativePILimit;
    int8_t ProportionalShift;
    int8_t IntegralShift;
} mc_sPIparams;


char RegOn=0, RegOn_1=0,  UprOn = 0, TemrControl = DatTemp, Error_out = 0, Error_out_buff = 0,  Stop_Mode = 0, CAN_send = 0,CurrentRegTesting;
mc_sPIparams  	PIRegParams_i={PIREG_P_GAIN_I,PIREG_I_GAIN_I,0,FRAC16(1),0,PIREG_P_GAIN_SHIFT_I,PIREG_I_GAIN_SHIFT_I};

int16_t controllerPItype(int16_t desired, int16_t actual, mc_sPIparams* piParams);
int32_t sadd32(int32_t a, int32_t b);
__STATIC_INLINE int16_t mult_r(int16_t x, int16_t y);
__STATIC_INLINE int16_t mult_r_ostatok(int16_t x, int16_t y);

RCC_ClocksTypeDef       RCC_Clocks;
GPIO_InitTypeDef  GPIO_InitStructure_;
USART_InitTypeDef USART_InitStructure;
NVIC_InitTypeDef  NVIC_InitStructure;
GPIO_InitTypeDef  GPIO_InitStructure;

uint16_t DeadTime, PWM1=PWM_50,PWM2=PWM_50,PWM3=PWM_50,PWM4=PWM_50,PWM_ALL;
uint16_t  i_max_real = I_MAX_REAL, U_min = Uvh_MIN, U_max = Uvh_MAX, Uvyh_max = Uvyh_MAX, delta_i = DELTA_I;

extern char RegOn, UprOn, Error_out;
extern uint16_t counter7, U_big, i_real, i_desired, UprADC, U_input,i_max_desired;

short Stop_ModeCounter=0, CAN_Counter=0, Start_time=0, End_Start = 2;
s16  Napr_Vyh_Min = NAPR_MIN;

uint32_t  X,TEMP,T_1,TEMP_MIN=F_TRM_MIN,TEMP_MAX=F_TRM_MAX;
const uint32_t Tn_F16=TN_F16;
int32_t  LnX,Ln_B;
int32_t t_cels;
uint16_t X1,Y1,t_cels_,Sin_,Offset_pwm,Restart_Power=0,ChargeTime=100,PauseRestart=10,Count_Reset=0;
int32_t mt,F_down,IeqS,Dr,I111,Result,I222;

const int32_t Kelv=KELV;
extern uint16_t Period_all,Period1,Period1_,Period2,Period2_, ProcPWM;

float float_m = m, float_I0 = I0, float_D0 = D0, float_tmf = tmf, float_Ieq = Ieq, float_t_cels, float_Sout, float_Sin;
// float_Sout = (float_I0 + (float_Ieq*float_Sin-float_I0)*(float_D0+float_m*float_tmf)/(float_D0+float_m*float_t_cels) )/float_Ieq;


extern short CounterTestOn;

char PWM_ALL_ADD[8], PWR_ON, Led1,Led2,Led3,Led4,LedRun, blink, ExternalError, ErrorOn;
uint8_t NotTest = 0, NoCheck = 0, G1=0,G2=0,G3=0,G4=0, G_ALL=0, STB_ON;

int main()
{

		SystemInit();
		SystemCoreClockUpdate();
		RCC_GetClocksFreq(&RCC_Clocks);
		PortsInit();
		CLR_ERROR;
		
		ADC_init();	
	
		Timer_1_init();
		Timer_2_init();
		Timer_4_init();
		Timer_3_init();		
		Timer_7_init();
		
		Timer_8_init();
		
		InitSynchro();
		

		FMSTR_InitSerial();
		
		CLR_POWER;
		Offset_pwm = OFFSET_PWM;
	
		__enable_irq();
	  __set_PRIMASK(0);
		
		DeadTime = DTM;

		NotTest = 1; // All PWM defined G_ALL and PWM_ALL
		NoCheck = 0; // RegOn turn by STB_ON (C5)
		PWR_ON = 0;
		G_ALL = 1;
		
		PWM1=PWM2=PWM3=PWM4=0;
		
		InitCAN_Master_Slave();
			
		while (1)
		{			
//				if(PultTestMode) PultTest();
			
				if(NotTest) Check_Err_Mode_Lamps();
			
				if(PWR_ON) Restart_Power_Charge();
				else {CLR_POWER;	Restart_Power = 0;Count_Reset=0;}		
			
				Temperature_Compute();
							
				if(UprOn)			Sin = mult_r(UprADC,ProcPWM);	
				else if(CurrentRegTesting) Sin = Istep*2;
		
				test = I_MAX_REG;
				
				if(!Tcomp) i_desired = mult_r(Sin,I_MAX_REG); 
				else CorrectTemperature();

				PWM_set();	
				if(!PultTestMode) CAN_exchange();

		}
}

__STATIC_INLINE void Blink_lamp(uint16_t N)
{
		switch(N)
		{
			case 0:
					 if(blink < 5)  SET_LED_RUN;
					 else 	 				CLR_LED_RUN;
				break;
			case 1:
					 if(blink < 5)  SET_LED1;
					 else 	 				CLR_LED1;
				break;
			case 2:
					 if(blink < 5)  SET_LED2;
					 else 	 				CLR_LED2;
				break;
			case 3:
					 if(blink < 5)  SET_LED3;
					 else 	 				CLR_LED3;
				break;
			case 4:
					 if(blink < 5)  SET_LED4;
					 else 	 				CLR_LED4;
				break;
//			default:	
		}			
}


__STATIC_INLINE void PultTest(void) {
	static uint16_t j = 0;
		
			NotTest = 0; 
			NoCheck = 0; 
			UprOn = 0; 
			RegOn = 0;		
			
			if(CounterTestOn < 5) 
			{
				Blink_lamp(j);
				j++;
				if(j > 4) j = 0;
			}
			else
			{
				SET_LED_RUN;
				SET_LED1;
				SET_LED2;
				SET_LED3;
				SET_LED4;
			}
	
			if(VOFF_IN_PORT) PWR_ON = 1;
			else PWR_ON = 0;
		
			PWM1=PWM2=PWM3=PWM4=PultTestPWM;
			G1 = (PultTestActiveCh>>0) & 1;
			G2 = (PultTestActiveCh>>1) & 1;
			G3 = (PultTestActiveCh>>2) & 1;
			G4 = (PultTestActiveCh>>3) & 1;

}

__STATIC_INLINE void PWM_set(void) {

				if(NotTest)	{
								PWM1=PWM_ALL;
								PWM2=PWM_ALL+PWM_ALL_ADD[0];
								PWM4=PWM_ALL+PWM_ALL_ADD[1];
								PWM3=PWM_ALL+PWM_ALL_ADD[2];
				
								G1=G2=G3=G4=G_ALL;
				}
				else {
								if(PWM1 > PWM_MAX) PWM1 = PWM_MAX;
								if(PWM2 > PWM_MAX) PWM2 = PWM_MAX;
								if(PWM3 > PWM_MAX) PWM3 = PWM_MAX;
								if(PWM4 > PWM_MAX) PWM4 = PWM_MAX;						
					
/*								if(G1) SET_LED1;
								else CLR_LED1;
								if(G2) SET_LED2;
								else CLR_LED2;
								if(G3) SET_LED3;
								else CLR_LED3;
								if(G4) SET_LED4;
								else CLR_LED4;	
								if(G5) SET_LED_RUN;
								else CLR_LED_RUN;*/
								//if(G6) SET_LED1;
								//else CLR_LED1;												
				}
				
			
				if(G2==1) TIM2->CCMR1 = 0x6060;	
				else	 if(G2==0) TIM2->CCMR1 = 0x4040;
							else if(G2==2) TIM2->CCMR1 = 0x5040;
			
				if(G1==1) TIM1->CCMR1 = 0x6060;	
				else	 if(G1==0) TIM1->CCMR1 = 0x4040;
							else if(G1==2) TIM1->CCMR1 = 0x5040;

				if(G3==1) TIM3->CCMR1 = 0x6060;	
				else	 if(G3==0) TIM3->CCMR1 = 0x4040;
							else if(G3==2) TIM3->CCMR1 = 0x5040;
			
				if(G4==1) TIM4->CCMR1 = 0x6060;	
				else	 if(G4==0) TIM4->CCMR1 = 0x4040;
							else if(G4==2) TIM4->CCMR1 = 0x5040;
			
				TIM_SetCompare1(TIM1,PWM1);
			  TIM_SetCompare2(TIM1,PWM1+DeadTime);
			
				TIM_SetCompare1(TIM2,PWM2);
			  TIM_SetCompare2(TIM2,PWM2+DeadTime);
			
			  TIM_SetCompare1(TIM3,PWM3);
				TIM_SetCompare2(TIM3,PWM3+DeadTime);
			
				TIM_SetCompare1(TIM4,PWM4);
			  TIM_SetCompare2(TIM4,PWM4+DeadTime);
}

__STATIC_INLINE void Restart_Power_Charge(void) {
					if(Count_Reset == 0)	{
						if(Restart_Power < ChargeTime) {SET_POWER;Restart_Power++;}
						else if(Restart_Power < ChargeTime+PauseRestart) {CLR_POWER;Restart_Power++;}
						else {SET_POWER;Count_Reset++;Restart_Power=0;}
					}
					else if(Count_Reset == 1)	{
						if(Restart_Power < ChargeTime) {SET_POWER;Restart_Power++;}
						else if(Restart_Power < ChargeTime+PauseRestart) {CLR_POWER;Restart_Power++;}
						else {SET_POWER;Count_Reset++;Restart_Power=0;}
					}
					else if(Count_Reset == 2)	{
						if(Restart_Power < ChargeTime) {SET_POWER;Restart_Power++;}
						else if(Restart_Power < ChargeTime+PauseRestart) {CLR_POWER;Restart_Power++;}
						else {SET_POWER;Count_Reset++;Restart_Power=0;}
					}
}

uint8_t PWM_Off_now=0;

void RegCurrent(void) {
	
		int16_t i;// j = MAX_VOLTAGE;
	
		i=PWM_100-2*DeadTime;
						
		if((!Stop_Mode)&&(NoCheck)&&(Master_CAN)) RegOn = STB_ON;
	
		if((Stop_Mode)&&(NoCheck)) RegOn = 0;

		if(Uvyh_max < U_input) PIRegParams_i.PositivePILimit = ((int32_t)MAX_VOLTAGE)*((int32_t)Uvyh_max)/U_input;		// Uvyh_max = 50 
		else PIRegParams_i.PositivePILimit = MAX_VOLTAGE;
		PIRegParams_i.NegativePILimit = 0;    				
		U_big = controllerPItype(i_desired, i_real, &PIRegParams_i);	
		//if(Istep) U_big = (Istep<<7)-3276;
		//else U_big=0;
	  
	
		if(RegOn){	if(!RegOn_1) {All_Pwr_On();}							
								PWM_ALL = mult_r_ostatok(U_big, i)+ DeadTime;	//Correct dead zone
								if(ostatok > 8000) PWM_ALL_ADD[0] = 1;
								else PWM_ALL_ADD[0] = 0;
								if(ostatok > 16000) PWM_ALL_ADD[1] = 1;
								else PWM_ALL_ADD[1] = 0;		
								if(ostatok > 24000) PWM_ALL_ADD[2] = 1;
								else PWM_ALL_ADD[2] = 0;				
								SET_LED_RUN;	
								PWM_Off_now=0;
		}	
		else {
								if(NoCheck) {
												PWM_ALL = 0;
												if(RegOn_1) {All_Pwr_Off();}
									
											/*	if(RegOn_1) {
															//All_Pwr_Off();
															PWM_Off_now = 1;
															PWM_ALL = PWM_ALL/2;															
												}
												else {
															PWM_ALL = 0;
															if(PWM_Off_now) {All_Pwr_Off();PWM_Off_now=0;}
												}*/
								}
								PIRegParams_i.IntegralPortion = 0;
								CLR_LED_RUN;
		}
		RegOn_1 = RegOn;
	  can_send++;//= 1;
}

int32_t sadd32(int32_t a, int32_t b) { 
__int64 r;
	r = (__int64)a + (__int64)b;
	if(r > 0x7FFFFFFF) { return 0x7FFFFFFF; }
	else if(r < -0x7FFFFFFF) { return -0x80000000; }
	return (int32_t)r; 
}



int32_t Err, Integr32, Prop32, High, Low, out, Prop323;
int16_t shift;

// PI controller
int16_t controllerPItype(int16_t desired, int16_t actual, mc_sPIparams* piParams) {

int32_t i,j;
	Err = (int32_t)desired - (int32_t)actual;	
	
	High=(int32_t)piParams->PositivePILimit<<16;
	Low=(int32_t)piParams->NegativePILimit<<16;	
	
	shift=piParams->ProportionalShift;
	if (piParams->ProportionalShift>=0) {
		Prop32 = (Err * piParams->ProportionalGain)>>piParams->ProportionalShift;		
	} else {
		Prop32=(Err * (int32_t)piParams->ProportionalGain);	
		j=abs(piParams->ProportionalShift);
		i=0x7FFFFFFF>>j;
		if (Prop32>i) Prop32=i;
		i=-i;
		if (Prop32<i) Prop32=i;		
		Prop32=Prop32<<j;
	}	
  	
	if (piParams->IntegralShift>=0) {
		Integr32 = (Err * piParams->IntegralGain)>>piParams->IntegralShift;
	} else {
		Integr32=(Err * piParams->IntegralGain);		
		j=abs(piParams->IntegralShift);
		i=0x7FFFFFFF>>j;
		if (Integr32>i) Integr32=i;
		i=-i;
		if (Integr32<i) Integr32=i;		
		Integr32=Integr32<<j;		
	}	
	
	piParams->IntegralPortion = sadd32(piParams->IntegralPortion, Integr32);
	
	if (piParams->IntegralPortion>High) piParams->IntegralPortion=High;
	if (piParams->IntegralPortion<Low) piParams->IntegralPortion=Low;
	
	out=sadd32(piParams->IntegralPortion, Prop32);
	
	if (out>High) { out=High; } // piParams->IntegralPortion=ssub32(High,Prop32); }
	if (out<Low) { out=Low; } // piParams->IntegralPortion=ssub32(Low,Prop32); }
	
//	if (piParams->IntegralPortion>High) piParams->IntegralPortion=High;
//	if (piParams->IntegralPortion<Low) piParams->IntegralPortion=Low;
	
	return (int16_t)(out>>16);
}

uint16_t PWM_Off=0,PWM_On=0;

__STATIC_INLINE void All_Pwr_Off(void) {
	TIM1->CCER = 0;
	TIM2->CCER = 0;
	TIM3->CCER = 0;
	TIM4->CCER = 0;
	
	PWM_Off++;
}

__STATIC_INLINE void All_Pwr_On(void) {
	TIM1->CCER = 0x11;
	TIM2->CCER = 0x11;
	TIM3->CCER = 0x11;
	TIM4->CCER = 0x11;
	
	PWM_On++;
}




__STATIC_INLINE int16_t mult_r(int16_t x, int16_t y)
{
    return (int16_t) (((int32_t) (x) * (y)) >> 15);
}


__STATIC_INLINE int16_t mult_r_ostatok(int16_t x, int16_t y)
{
	int32_t result;
		result = ((int32_t) (x) * (y));
		ostatok = result & 0x7FFF;
    return (int16_t) (result >> 15);
}


 int32_t fxlog(uint32_t x) {
						uint32_t t,y;

						y=0xa65af;
						if(x<0x00008000) x<<=16,              y-=0xb1721;
						if(x<0x00800000) x<<= 8,              y-=0x58b91;
						if(x<0x08000000) x<<= 4,              y-=0x2c5c8;
						if(x<0x20000000) x<<= 2,              y-=0x162e4;
						if(x<0x40000000) x<<= 1,              y-=0x0b172;
						t=x+(x>>1); if((t&0x80000000)==0) x=t,y-=0x067cd;
						t=x+(x>>2); if((t&0x80000000)==0) x=t,y-=0x03920;
						t=x+(x>>3); if((t&0x80000000)==0) x=t,y-=0x01e27;
						t=x+(x>>4); if((t&0x80000000)==0) x=t,y-=0x00f85;
						t=x+(x>>5); if((t&0x80000000)==0) x=t,y-=0x007e1;
						t=x+(x>>6); if((t&0x80000000)==0) x=t,y-=0x003f8;
						t=x+(x>>7); if((t&0x80000000)==0) x=t,y-=0x001fe;
						x=0x80000000-x;
						y-=x>>15;
						return y;
}



uint32_t div_32(uint32_t x, uint32_t y)	{
	
uint32_t x_l,res_h,res_l,result;
	
	if(y == 0) return 0xFFFFFFFF;
	else {

		    res_h = x/y;
		    x=x-res_h*y;

				x_l = ((int32_t)x)<<16;				

				res_l = x_l/y;
				result=res_l+(res_h<<16);
				return result;
	}
}


__STATIC_INLINE void InitCAN_Master_Slave(void) {
	
		if(MASTER_IN_PORT) Master_CAN = 0;
		else Master_CAN = 1;			
		UprOn = Master_CAN;		
		init_CAN1();
		
		if(Master_CAN) {End_Start--; can_send=can_end;}
		Start_time = 0;
		while(Start_time < End_Start) {
		}		
	
}

uint16_t T_kz,Check_KZ;




__STATIC_INLINE void Check_Err_Mode_Lamps(void)	{

				
				if(Master_CAN) {
								if(VOFF_IN_PORT) PWR_ON = 1;
								else PWR_ON = 0;
				  
								if (STB_IN_PORT) STB_ON = 0;
								else STB_ON = 1;
				}

				
			 	if(PWM_ALL <= DeadTime) 	PWM_ALL = 0;
				if(PWM_ALL > PWM_MAX) 		PWM_ALL = PWM_MAX;
			
		    if(i_real > i_max_real) 	Error_out |= ERROR_OVERCURRENT;
				else 											Error_out &= ~ERROR_OVERCURRENT;
				
				if(STB_ON) T_kz = 0;
				else {if(T_kz <= 100) T_kz++;}
				if((T_kz == 0) || (T_kz >= 100)) Check_KZ = 1; // первые 100 тактов после включения STB
				else Check_KZ = 0;
			
				
				if((U_output < Napr_Vyh_Min)&&(i_real > i_real_kz)&&Check_KZ)		{Error_out |= ERROR_KZ; I_tmp = i_real;}
				else 																									Error_out &= ~ERROR_KZ;  
							
				if(U_input > U_max)  											Error_out |= ERROR_OVERVOLT;
				else																	Error_out &= ~ERROR_OVERVOLT;
				
				
				if(!PWR_ON) 													Error_out |= ERROR_PWR_ON;
				else										  						Error_out &= ~ERROR_PWR_ON;
				 
				if((U_input < U_min)&&(PWR_ON))  					Error_out |= ERROR_UNDERVOLT;
				else										  						Error_out &= ~ERROR_UNDERVOLT;
			  				 				 
				 
				if(TemrControl) {
					if((TEMP > TEMP_MAX)||(TEMP < TEMP_MIN)) 		  Error_out |= ERROR_TRM;
					else											Error_out &= ~ERROR_TRM;
				}
				
				if ((RegOn) &&
							( (PWM_ALL >= PWM_MAX) ) &&
									  ((i_desired-i_real)>delta_i)) {Error_out |= ERROR_UNDERCURRENT;}										
				else 	 																		Error_out &= ~ERROR_UNDERCURRENT;
				

			  if(Error_out) {
						if(NotTest) {Stop_Mode = 1; SET_ERROR;}
						Stop_ModeCounter = 60;
						Error_out_buff = Error_out;
					  ErrorOn = 1;
				}

				else {			
									if(ERR_IN_PORT) {ExternalError = 1;Stop_Mode = 2;}
									else {ExternalError = 0;	Stop_Mode = 0;}
				}

				GPIOB->ODR = ((uint16_t) (Error_out_buff&0x0F))<<11; //SET_LED
				
				if(Error_out_buff & ERROR_OVERCURRENT) Blink_lamp(1);
				if(Error_out_buff & ERROR_KZ) Blink_lamp(2);		
				if(Error_out_buff & ERROR_CAN) Blink_lamp(3);
				if(Error_out_buff & ERROR_PWR_ON)  Blink_lamp(4);	
}


__STATIC_INLINE void Temperature_Compute(void) {				
				if(F_trm__ > 150) {
				
										X = div_32(F_trm__,(U25V-F_trm__));
										LnX = fxlog(X);
										Ln_B = (((int)(LnX * B_T)) >> (RAZ_D-RAZ_Tn));				
										T_1 = Ln_B+Tn_F16;
										TEMP = div_32(((uint32_t)1<<(RAZ_BASE+RAZ_Tn)),T_1);

										t_cels = (TEMP-Kelv); // hight byte is kelvin
				}
}


__STATIC_INLINE void CAN_exchange(void) {
				if(can_send >= can_end) {
					can_send = 0;
					if(Master_CAN) {
								Fill_data_message();
								CAN_Transmit(CAN1, &DATA_message);
					}
				}
}



__STATIC_INLINE void CorrectTemperature (void) {
	
float Tn=10,Tv=10,Sn=0,Sv=0,Snm,Svm,Snb,Svb,S1,S2;	
char iii,it,is;	
									float_t_cels = ((float)t_cels)/((float)65536);
									float_Sin = ((float)Sin)/((float)U25V)*10000;
					
									iii=1;
									
									while(float_t_cels > Array[0][iii]) iii++;
									it = iii;
									Tn = Array[0][it-1];
									Tv = Array[0][it];
					
									iii=1;
									
									while(float_Sin > Array[iii][0]) iii++;
									is = iii;
									Sn = Array[is-1][0];
									Sv = Array[is][0];									
									
									Snm = Array[is-1][it-1];
									Svm = Array[is-1][it];
									Snb = Array[is][it-1];
									Svb = Array[is][it];
					
									S1 = Snm + (float_Sin - Sn)*(Snb - Snm)/(Sv-Sn);
									S2 = Svm + (float_Sin - Sn)*(Svb - Svm)/(Sv-Sn);
									float_Sout = S1 + (S2 - S1)*(float_t_cels - Tn)/(Tv - Tn);
									
									Result = (uint16_t)((float)I_20A*(float_Sout/10000));
									
									if(Result > I_MAX_CORRECT) i_desired = I_MAX_CORRECT;
									else i_desired = Result;
}

__STATIC_INLINE void InitSynchro(void)	{
	TIM1->CNT = 0;
	TIM2->CNT = OFFSET_PWM+6;
	TIM3->CNT = OFFSET_PWM*2+12;
	TIM4->CNT = OFFSET_PWM*3+18;
	
	TIM1->CR1 |= TIM_CR1_CEN;
//	TIM2->CR1 |= TIM_CR1_CEN;
//	TIM3->CR1 |= TIM_CR1_CEN;
//	TIM4->CR1 |= TIM_CR1_CEN;

	//First_Start1=1;
}

void PortsInit(void) {
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	GPIO_InitStructure.GPIO_OType = 								GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = 									GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Mode = 									GPIO_Mode_OUT;		
  GPIO_InitStructure.GPIO_Pin = 									GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Speed = 								GPIO_Speed_2MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIOB->ODR = 0x0;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_OType = 								GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = 									GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Mode = 									GPIO_Mode_OUT;		
  GPIO_InitStructure.GPIO_Pin = 									GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Speed = 								GPIO_Speed_2MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	GPIO_InitStructure.GPIO_OType = 								GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = 									GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Mode = 									GPIO_Mode_OUT;		
  GPIO_InitStructure.GPIO_Pin = 									GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Speed = 								GPIO_Speed_2MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);	
	
	//inputs
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	GPIO_InitStructure.GPIO_OType = 								GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = 									GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Mode = 									GPIO_Mode_IN;		
  GPIO_InitStructure.GPIO_Pin = 									GPIO_Pin_5|GPIO_Pin_4|GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Speed = 								GPIO_Speed_2MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);	
	
		
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_OType = 								GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = 									GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Mode = 									GPIO_Mode_IN;		
  GPIO_InitStructure.GPIO_Pin = 									GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Speed = 								GPIO_Speed_2MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	
//	GPIOC->ODR &= ~(1<<7);	

}











