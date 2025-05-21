#define  				ERROR_TRM					  		0x01 //1
#define  				ERROR_UNDERCURRENT	  	0x02 //6
#define  				ERROR_OVERVOLT	  			0x04 //7
#define  				ERROR_UNDERVOLT		  		0x08 //3
#define  				ERROR_OVERCURRENT	  		0x10 //2
#define  				ERROR_CAN								0x20 //8
#define  				ERROR_PWR_ON						0x40 //4	
#define  				ERROR_KZ                0x80 //5


typedef enum
{
  Disp_process_off,
  Disp_process_start,
  Disp_process_ended
}TDispProcess;




typedef enum
{
  Disp_ControlPWM,
  Disp_ControlDAC1,
	Disp_ControlDAC2,
	Disp_ADC,
	Disp_CAN,
	Disp_Temp1,
	Disp_Temp2,
	Disp_Temp3
}TDispMode;


