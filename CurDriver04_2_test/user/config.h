#define TCOMP									1 //1 - on, 0 - off

#define I_MAX									20 //1 to 20

#define U_MAX_OUT_VOLT				50
#define U_MAX_VOLT						60
#define U_MIN_VOLT						20
#define SEC_WAIT_01						60  //60 = 6 secund
#define DatTemp 							1   

#define FILTER_T							15

#define MaxTemp								60
#define MinTemp								0
#define B_TEMP								3380			//
#define TN										(273+25)
#define KELV   								(273<<RAZ_BASE)

#define I0										-3.000// 0 to -50
#define m											-0.00929// 0 to -0,5
#define D0										2.1429// 0,1 to 20
#define tmf										20.0// 10 to 60
#define Ieq										12.00// 1 to 12

#define RAZ_BASE							16
#define RAZ_D 								25
#define RAZ_Tn 								10					

#define  				ERROR_TRM					  		0x01 //1
#define  				ERROR_UNDERCURRENT	  	0x02 //6
#define  				ERROR_OVERVOLT	  			0x04 //7
#define  				ERROR_UNDERVOLT		  		0x08 //3
#define  				ERROR_OVERCURRENT	  		0x10 //2
#define  				ERROR_CAN								0x20 //8
#define  				ERROR_PWR_ON						0x40 //4	
#define  				ERROR_KZ                0x80 //5

// + ExternalError



#define B_T 									((1<<RAZ_D)/B_TEMP)
#define	TN_F16								((1<<(RAZ_BASE+RAZ_Tn))/TN)

#define I_MAX_AMPER						24  
#define I_MAX_ABS						  31

#define deltaI								0.4
#define SEC_WAIT_01_GIST				1   //1 = 0.1 secunda

#define ADC_SCALE					4096
#define I_MAX_REAL				(I_MAX_AMPER*ADC_SCALE/I_MAX_ABS)	//

#define DELTA_I						(deltaI*ADC_SCALE/I_MAX_ABS)

#define U5V 			(5.0*ADC_SCALE/3.3)
#define U25V 			(U5V/2) //3103 (3106-3108)

#define I_MAX_MEASUREMENT (U25V*I_MAX_ABS/ADC_SCALE) //3103*31/4096 = 23.48 ампера максимально измер€емый заданный ток

#define I_MAX_REG 				(I_MAX*0x7FFF/I_MAX_MEASUREMENT)	// 20/23.48 = 0.85
#define I_MAX_CORRECT			(I_MAX*ADC_SCALE/I_MAX_ABS)	// 20/31 * 4096 = 2642
#define I_20A							(20*ADC_SCALE/I_MAX_ABS)// 2642

//#define I_MAX_REAL				3723	//(15 A)	//4096~16.5
//#define DELTA_I						50

#define Uvh_MIN						U_MIN_VOLT*ADC_SCALE/63.3 //
#define Uvh_MAX						U_MAX_VOLT*ADC_SCALE/63.3 //
#define Uvyh_MAX				  U_MAX_OUT_VOLT*ADC_SCALE/63.3 



#define MAX_VOLTAGE 			0x7FFF




#define ActualCounterMode  TIM_CounterMode_CenterAligned2	
#define  DTM  6


//42 MHz tik (0.0238 mkS)
#define PWM_100 		256  			           //0.0238 * 256 * 2 = 12.1856 mkS => 82.06 Khz
#define	OFFSET_PWM		PWM_100*2/6       ////-15////= 70 
#define PWM_MAX 		PWM_100-DTM-1 


#define PIREG_P_GAIN_I    	   	16000		
#define PIREG_I_GAIN_I   	   		16000


#define PIREG_P_GAIN_SHIFT_I 		-1   //-1
#define PIREG_I_GAIN_SHIFT_I   	0    //-1
		
//#define PIREG_P_GAIN_SHIFT_I 		-2  //-2
//#define PIREG_I_GAIN_SHIFT_I   	1   //1

#define F_TRM_MAX					((MaxTemp+273)<<16)
#define F_TRM_MIN					((MinTemp+273)<<16)

#define PWM_50			PWM_100/2

#define 	SET_POWER	GPIOC->ODR |=  (1<<2)
#define 	CLR_POWER	GPIOC->ODR &=  ~(1<<2)

#define 	SET_LED1	GPIOB->ODR |=  (1<<11)
#define 	CLR_LED1	GPIOB->ODR &=  ~(1<<11)

#define 	SET_LED2	GPIOB->ODR |=  (1<<12)
#define 	CLR_LED2	GPIOB->ODR &=  ~(1<<12)

#define 	SET_LED3	GPIOB->ODR |=  (1<<13)
#define 	CLR_LED3	GPIOB->ODR &=  ~(1<<13)

#define 	SET_LED4	GPIOB->ODR |=  (1<<14)
#define 	CLR_LED4	GPIOB->ODR &=  ~(1<<14)

#define 	SET_LED_RUN	GPIOB->ODR |=  (1<<15)
#define 	CLR_LED_RUN	GPIOB->ODR &=  ~(1<<15)

//#define 	SET_ERROR	GPIOC->ODR |=  (1<<9)
//#define 	CLR_ERROR	GPIOC->ODR &= ~(1<<9)

#define 	SET_ERROR	GPIOC->MODER |=  (1<<9*2)
#define 	CLR_ERROR	GPIOC->MODER &= ~(1<<9*2)

#define VOFF_IN_PORT ((GPIOC->IDR)&(1<<4))  
#define STB_IN_PORT ((GPIOC->IDR)&(1<<5))   //Tumbler
#define ERR_IN_PORT ((GPIOC->IDR)&(1<<3))
#define MASTER_IN_PORT ((GPIOA->IDR)&(1<<3))
#define TEST_IN_PORT  ((GPIOD->IDR)&(1<<2))

//#define VL_IN_PORT (GPIOC->IDR)&(1<<6) 		//PWM-IN

#define NAPR_MIN_ 				1 //V
#define NAPR_MIN				  NAPR_MIN_*ADC_SCALE/66 
#define I_KZ_							1.8 //A
#define I_KZ							I_KZ_*ADC_SCALE/I_MAX_ABS

#define rsh(x,n) ( (x>=0)?(x>>n):( -((-x)>>n) ))
#define abs(x) (x>0?x:-x)
#define saturate(x,a,b) ((x>b)?b:((x<a)?a:x))

#define FRAC16(x) ((uint16_t)((x) < 1 ? ((x) >= -1 ? ((uint16_t)((x)*0x8000)) : ((uint16_t)0x8000)) : ((uint16_t)0x7FFF)))
#define FRAC32(x) ((uint32_t)((x) < 1 ? ((x) >= -1 ? ((uint32_t)((x)*0x80000000)) : ((uint32_t)0x80000000)) : ((uint32_t)0x7FFFFFFF)))

#define I_TEST 0x80

//#define 				ADC_SampleTime_    ADC_SampleTime_3Cycles                   
//#define 				ADC_SampleTime_    ADC_SampleTime_15Cycles              
//#define 				ADC_SampleTime_    ADC_SampleTime_28Cycles              
//#define 				ADC_SampleTime_    ADC_SampleTime_56Cycles       
#define 				ADC_SampleTime_    ADC_SampleTime_84Cycles   
//#define 				ADC_SampleTime_    ADC_SampleTime_112Cycles   
//#define 				ADC_SampleTime_    ADC_SampleTime_144Cycles  
//#define 				ADC_SampleTime_    ADC_SampleTime_480Cycles  



#define CH_I_LED 				ADC_Channel_9
#define CH_V_BUS 				ADC_Channel_8
#define CH_V_LED 				ADC_Channel_7
#define CH_I_BUS 				ADC_Channel_6
#define CH_F_COM 				ADC_Channel_11
#define CH_F_TRM 				ADC_Channel_10

