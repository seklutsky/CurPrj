//#define ActualCounterMode  TIM_CounterMode_CenterAligned2	

#define 	ENCODER_INVERSION
//#define		DAC2_INVERSION

#define 	SYS_CLK					42.0f
#define 	PWM10KHz				100*SYS_CLK	
#define 	ImaxA						24.0

#define ADC_SCALE					4096
#define U5V 							(5*ADC_SCALE/3.3)
#define U2_5V 						(U5V/2) //3103 (3106-3108)
#define U1V 							(U5V/5) 


#define START_TIME				150

#define I_MAX							20 //1 to 20
#define ADC_SCALE					4096
#define I_MAX_ABS					31
#define I_MAX_CORRECT			(I_MAX*ADC_SCALE/I_MAX_ABS)	// 20/31 * 4096 = 2642
#define I_20A							(20*ADC_SCALE/I_MAX_ABS)// 2642

//42 MHz tik (0.0238 mkS)
/*#define PWM_100 		256  			
#define	OFFSET_PWM		PWM_100*2/6////-15////= 70 
#define PWM_MAX 		PWM_100-DTM-1 


#define  				ERROR_TRM					  		0x01 //1
#define  				ERROR_UNDERCURRENT	  	0x02 //6
#define  				ERROR_OVERVOLT	  			0x04 //7
#define  				ERROR_UNDERVOLT		  		0x08 //3
#define  				ERROR_OVERCURRENT	  		0x10 //2
#define  				ERROR_CAN								0x20 //8
#define  				ERROR_PWR_ON						0x40 //4	
#define  				ERROR_KZ                0x80 //5
*/
