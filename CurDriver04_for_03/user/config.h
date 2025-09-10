#define HARD_REG							1		//From 1 to 4, 1 - Hard 4 - Soft

#define TCOMP									0 //1 - on, 0 - off

#define I_MAX									12 //1 to 16.5

#define U_MAX_OUT_VOLT				15
#define U_MAX_VOLT						16
#define U_MIN_VOLT						9
#define SEC_WAIT_01						60  //60 = 6 secund
#define DatTemp 							1   

#define FILTER_T							15

#define ABS_ERR_MIN 					150.0
#define ABS_ERR_K							(16000.0/ABS_ERR_MIN)//106

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

#define I_MAX_AMPER						15  
#define I_MAX_ABS						  16.5

#define deltaI								0.2
#define SEC_WAIT_01_GIST				1   //1 = 0.1 secunda

#define ADC_SCALE					4096
#define I_MAX_REAL				(I_MAX_AMPER*ADC_SCALE/I_MAX_ABS)	//

#define DELTA_I						(deltaI*ADC_SCALE/I_MAX_ABS)

#define U5V 			(5.0*ADC_SCALE/3.3)
#define U25V 			(U5V/2) //3103 (3106-3108)

#define I_MAX_MEASUREMENT (U25V*I_MAX_ABS/ADC_SCALE) //3103*16.5/4096 = 12.5 ампера максимально измер€емый заданный ток

#define I_MAX_REG 				(I_MAX*0x7FFF/I_MAX_MEASUREMENT)	// 12/12.5 = 0.96
#define I_MAX_CORRECT			(I_MAX*ADC_SCALE/I_MAX_ABS)	// 12/16.5 * 4096 = 2979
#define I_12A							(12*ADC_SCALE/I_MAX_ABS)// 2642

#define U_VH_MAX_IZM					29.91

#define Uvh_MIN						U_MIN_VOLT*ADC_SCALE/U_VH_MAX_IZM //
#define Uvh_MAX						U_MAX_VOLT*ADC_SCALE/U_VH_MAX_IZM //
#define Uvyh_MAX				  U_MAX_OUT_VOLT*ADC_SCALE/U_VH_MAX_IZM 



#define MAX_VOLTAGE 			0x7FFF




#define ActualCounterMode  TIM_CounterMode_CenterAligned2	
#define  DTM  6


//42 MHz tik (0.0238 mkS)
#define PWM_100 		256  			//0.0238 * 256 * 2 = 12.1856 mkS => 82.06 Khz
#define	OFFSET_PWM		PWM_100*2/4///= 82 (12.2 mkS) or 164 kHz
#define PWM_MAX 		PWM_100-DTM-1 


#define PIREG_P_GAIN_I    	   	11000		
#define PIREG_I_GAIN_I   	   		16000

#if HARD_REG == 1
    #define PIREG_I_GAIN_SHIFT_I   0
    #define PIREG_P_GAIN_SHIFT_I   -3
#elif HARD_REG == 2
    #define PIREG_I_GAIN_SHIFT_I   1
    #define PIREG_P_GAIN_SHIFT_I   -2
#elif HARD_REG == 3
    #define PIREG_I_GAIN_SHIFT_I   2
    #define PIREG_P_GAIN_SHIFT_I   -1
#elif HARD_REG == 4
    #define PIREG_I_GAIN_SHIFT_I   3
    #define PIREG_P_GAIN_SHIFT_I   0
#else
    #error "HARD_REG must be between 1 and 4"
#endif


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

#define 	SET_ERROR	GPIOC->MODER |=  (1<<7*2)
#define 	CLR_ERROR	GPIOC->MODER &= ~(1<<7*2)

#define VOFF_IN_PORT ((GPIOC->IDR)&(1<<4))  
#define STB_IN_PORT ((GPIOC->IDR)&(1<<5))   //Tumbler
#define ERR_IN_PORT ((GPIOC->IDR)&(1<<3))
#define MASTER_IN_PORT ((GPIOA->IDR)&(1<<2))
//#define TEST_IN_PORT  ((GPIOD->IDR)&(1<<2))

//#define VL_IN_PORT (GPIOC->IDR)&(1<<6) 		//PWM-IN

#define NAPR_MIN_ 				1 //V
#define NAPR_MIN				  NAPR_MIN_*ADC_SCALE/U_VH_MAX_IZM 
#define I_KZ_							1.8 //A
#define I_KZ							I_KZ_*ADC_SCALE/I_MAX_ABS

#define rsh(x,n) ( (x>=0)?(x>>n):( -((-x)>>n) ))
#define abs(x) (x>=0?x:-x)
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

