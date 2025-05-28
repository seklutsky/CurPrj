#include "include.h"

void Disp_preved(void) 
{	
	
  disp1color_SetBrightness(255);
  
  disp1color_FillScreenbuff(0);
  disp1color_UpdateFromBuff();
  delay_ms(100);

  disp1color_DrawRectangleFilled(0, 0, 127, 63);
  disp1color_UpdateFromBuff();
  delay_ms(100);
	
	SSD1306_SetCOMoutScanDirection(1);
	SSD1306_SetSegmentRemap(1);

  disp1color_FillScreenbuff(0);
  disp1color_DrawRectangle(0, 0, 127, 63); //рамка

  disp1color_printf(5, 1, FONTID_10X16F, "Выбор режима");
  disp1color_printf(5, 21, FONTID_10X16F, "нажатием");
	disp1color_printf(5, 41, FONTID_10X16F, "енкодера");
//  disp1color_printf(5, 40, FONTID_6X8M, "%d", 2024);
  disp1color_UpdateFromBuff();
  delay_ms(100);
}



TDispMode DisplayControlMode = Disp_ControlPWM, DisplayControlMode_ = Disp_ControlPWM, DisplayTestMode = 0;
TDispProcess testTimeDisp = Disp_process_off;
uint16_t EncoderMode[8] = {0,0,0,0,0,0,0,0};

uint16_t display_getEncoderMode(TDispMode Mode)
{
	return EncoderMode[Mode];
}

void display_initControlDAC2(void)
{	
		uint16_t Temp_dac;
		EncoderMode[Disp_ControlDAC2] = 69;//0.88 v
		Temp_dac = (uint16_t)((float)(EncoderMode[Disp_ControlDAC2] * DAC_MAX) / (float)ENCODER_MAX);//*4095/256
		DAC_set_level(2,Temp_dac);
}




void display_ControlPWM(void)
{
	uint16_t Temp_pwm;
	float Temp_PWM_proc;
	uint16_t adcI;
	uint16_t adcIP48;
	float Temp_adcI_float_B = 0;
	float Temp_adcIP48_float_B = 0;
	uint16_t Temp_dac;
	float VA_IN;
	
		CLR_STB_OUT_PORT;
		SET_VOFF_OUT_PORT;
		DAC_set_level(1,DAC_MAX);
	  EncoderMode[Disp_ControlDAC1] = ENCODER_MAX;
		disp1color_printf(1, 0, FONTID_6X8M, "VL-IN(PWM) Control");
	
	if(CanMaster == 0) 
	{	
		if(AutoMode) 
		{
			EncoderMode[Disp_ControlPWM] = Encoder_get_position();
			Temp_pwm = (uint16_t)((float)(EncoderMode[Disp_ControlPWM] * 100.0f) / (float)ENCODER_MAX);
			PWM_set(Temp_pwm);
			Temp_PWM_proc = (float)Temp_pwm;
			disp1color_printf(1, 10, FONTID_6X8M, "PWM = %0.0f %%", Temp_PWM_proc);
			adcI = getADCresult(1);
			Temp_adcI_float_B = (float)adcI * 31.0f/4096.0f;
			disp1color_printf(1, 20, FONTID_6X8M, "I-LOAD =  %0.2f A", Temp_adcI_float_B);
			adcIP48 = getADCresult(0);
			Temp_adcIP48_float_B = (float)adcIP48 * 31.0f/4096.0f;
			disp1color_printf(1, 30, FONTID_6X8M, "I-P48 =  %0.2f A", Temp_adcIP48_float_B);	
			Temp_dac = (uint16_t)((float)(EncoderMode[Disp_ControlDAC1] * DAC_MAX) / (float)ENCODER_MAX);
			VA_IN = (float)Temp_dac * VOLT_MAX/4096.0f;
			disp1color_printf(1, 40, FONTID_6X8M, "ЦАП VA-IN =  %0.2f V", VA_IN);
			disp1color_printf(1, 50, FONTID_6X8M, "V-LED=%0.1f V-BUS=%0.1f", (float)V_led*63.3/256.0, (float)V_bus*63.3/256.0);
		}
		else
		{
			disp1color_printf(1, 10, FONTID_6X8M, "В режиме MANUAL");
			disp1color_printf(1, 20, FONTID_6X8M, "ШИМ выставляется");
			disp1color_printf(1, 30, FONTID_6X8M, "тумблером VL(0 или 1)");
			disp1color_printf(1, 40, FONTID_6X8M, "переключите в AUTO");
			disp1color_printf(1, 50, FONTID_6X8M, "для управления ручкой");			
		}
	}
	else
	{
		PWM_set(0);
		DAC_set_level(1,0);
		disp1color_printf(1, 10, FONTID_6X8M, "Источник SLAVE");
    disp1color_printf(1, 20, FONTID_6X8M, "и не регулируется");
		disp1color_printf(1, 30, FONTID_6X8M, "внешними сигналами");
		disp1color_printf(1, 40, FONTID_6X8M, "Перейдите в окно CAN");
		disp1color_printf(1, 50, FONTID_6X8M, "чтобы управлять");
	}
}

void display_ControlDAC1(void)
{
	uint16_t Temp_dac;
	float VA_IN;
	uint16_t adcI;
	float Temp_adcI_float_B = 0;
	uint16_t adcIP48;
	float Temp_adcIP48_float_B = 0;
	uint16_t Temp_pwm;
	float Temp_PWM_proc;
	
	CLR_STB_OUT_PORT;
	SET_VOFF_OUT_PORT;
	PWM_set(100);
	EncoderMode[Disp_ControlPWM] = ENCODER_MAX;
	disp1color_printf(1, 0, FONTID_6X8M, "VA-IN Control");
	
	if(CanMaster == 0) 
	{		
		EncoderMode[Disp_ControlDAC1] = Encoder_get_position();
		Temp_dac = (uint16_t)((float)(EncoderMode[Disp_ControlDAC1] * DAC_MAX) / (float)ENCODER_MAX);
		DAC_set_level(1,Temp_dac);
		VA_IN = (float)Temp_dac * VOLT_MAX/4096.0f;
		disp1color_printf(1, 12, FONTID_6X8M, "ЦАП =  %0.2f V", VA_IN);
		adcI = getADCresult(1);
		Temp_adcI_float_B = (float)adcI * 31.0f/4096.0f;
		disp1color_printf(1, 24, FONTID_6X8M, "I-LOAD =  %0.2f A", Temp_adcI_float_B);
		adcIP48 = getADCresult(0);
		Temp_adcIP48_float_B = (float)adcIP48 * 31.0f/4096.0f;
		disp1color_printf(1, 36, FONTID_6X8M, "I-P48 =  %0.2f A", Temp_adcIP48_float_B);
		Temp_pwm = (uint16_t)((float)(EncoderMode[Disp_ControlPWM] * 100.0) / (float)ENCODER_MAX);	
		Temp_PWM_proc = (float)Temp_pwm;
		disp1color_printf(1, 48, FONTID_6X8M, "PWM = %0.0f %%", Temp_PWM_proc);
	}		
	else
	{
		PWM_set(0);
		DAC_set_level(1,0);
		disp1color_printf(1, 10, FONTID_6X8M, "Источник SLAVE");
    disp1color_printf(1, 20, FONTID_6X8M, "и не регулируется");
		disp1color_printf(1, 30, FONTID_6X8M, "внешними сигналами");
		disp1color_printf(1, 40, FONTID_6X8M, "Перейдите в окно CAN");
		disp1color_printf(1, 50, FONTID_6X8M, "чтобы управлять");
	}
}



void display_ControlDAC2(void)
{
	uint16_t Temp_dac;
	float Temp2;
	float Temp_adcTerm_float_B, Temp_cels_float;
	int32_t Temp_cels;
	uint16_t adcTerm;
	uint16_t adcI;
	float Temp_adcI_float_B = 0;
	
	disp1color_printf(1, 0, FONTID_6X8M, "Термодатчик");
	EncoderMode[Disp_ControlDAC2] = Encoder_get_position();
	Temp_dac = (uint16_t)((float)(EncoderMode[Disp_ControlDAC2] * DAC_MAX) / (float)ENCODER_MAX);
#ifdef DAC2_INVERSION
	DAC_set_level(2,(4095 - Temp_dac));
#else
	DAC_set_level(2,Temp_dac);
#endif
	Temp2 = (float)Temp_dac * VOLT_MAX/4096.0f;
	disp1color_printf(1, 12, FONTID_6X8M, "ЦАП =  %0.2f V", Temp2);
	adcTerm = getADCresult(2);
	Temp_adcTerm_float_B = (float)adcTerm * 3.3f/4096.0f;
	disp1color_printf(1, 24, FONTID_6X8M, "АЦП TEMP =  %0.2f V", Temp_adcTerm_float_B);
	Temp_cels = Temperature_Compute(adcTerm);
	Temp_cels_float = (float)Temp_cels/65536;
	disp1color_printf(1, 36, FONTID_6X8M, "t =  %0.2f град цельс", Temp_cels_float);	
	
	adcI = getADCresult(1);
	Temp_adcI_float_B = (float)adcI * 31.0f/4096.0f;
	disp1color_printf(1, 48, FONTID_6X8M, "I-LOAD =  %0.2f A", Temp_adcI_float_B);	
}

void display_ADC(void)
{
	uint16_t adcIP48, adcCON, adcTerm, adcI;
	float Temp_adcIP48_float_B = 0;
	float Temp_adcCON_float_B = 0;
	float Temp_adcI_float_B = 0;
	float Temp_adcTerm_float_B = 0;
	
	disp1color_printf(1, 0, FONTID_6X8M, "АЦП, вольт");
	EncoderMode[Disp_ADC] = Encoder_get_position();
	
	adcIP48 = getADCresult(0);
	adcCON = getADCresult(3);
	adcTerm = getADCresult(2);
	adcI = getADCresult(1);
	
	Temp_adcIP48_float_B = (float)adcIP48 * 3.3f/4096.0f;
	Temp_adcCON_float_B = (float)adcCON * 3.3f/4096.0f;
	Temp_adcTerm_float_B = (float)adcTerm * 3.3f/4096.0f;
	Temp_adcI_float_B = (float)adcI * 3.3f/4096.0f;
	
	disp1color_printf(1, 12, FONTID_6X8M, "АЦП I-P48 =  %0.2f V", Temp_adcIP48_float_B);
	disp1color_printf(1, 24, FONTID_6X8M, "АЦП CON-IN =  %0.2f V", Temp_adcCON_float_B);
	disp1color_printf(1, 36, FONTID_6X8M, "АЦП TEMP =  %0.2f V", Temp_adcTerm_float_B);
	disp1color_printf(1, 48, FONTID_6X8M, "АЦП I-LOAD =  %0.2f V", Temp_adcI_float_B);
}

void display_CAN(void)
{
	float iSin = 0, iSinCor = 0;
	uint16_t adcTerm;
	int32_t Temp_cels;
	uint16_t adcI;	
	float Temp_adcI_float_B = 0;
	uint16_t Temp_pwm;
	float Temp_PWM_proc;
	
	if(CanMaster == 1)
	{
			PWM_set(0);
			DAC_set_level(1,0);
		
		  EncoderMode[Disp_CAN] = Encoder_get_position();			
		  Sin = (uint16_t)((float)(EncoderMode[Disp_CAN] * U2_5V) / (float)ENCODER_MAX);
			disp1color_printf(1, 10, FONTID_6X8M, "CAN Slave");
		  disp1color_printf(1, 21, FONTID_6X8M, "Задание =  %0.2f %%", (float)Sin * 100.0f / (float)U2_5V);
			iSin = (float)Sin * 20.0f / (float)U2_5V;
			adcTerm = getADCresult(2);
			Temp_cels = Temperature_Compute(adcTerm);
			iSinCor = (float)CorrectTemperature(Temp_cels) * 20 / (float)U2_5V;	
		  disp1color_printf(1, 31, FONTID_6X8M, "Задание =  %0.2f A ", iSin);
			disp1color_printf(1, 41, FONTID_6X8M, "Темп. корр. =  %0.2f A ", iSinCor);		
			adcI = getADCresult(1);
			Temp_adcI_float_B = (float)adcI * 31.0f/4096.0f;
			disp1color_printf(1, 51, FONTID_6X8M, "I-LOAD =  %0.2f A", Temp_adcI_float_B);
	  
	}
	else
	{
		disp1color_printf(1, 0, FONTID_6X8M, "CAN Master");
		if(!Error_CAN)
		{			
			DAC_set_level(1,DAC_MAX);
			EncoderMode[Disp_ControlDAC1] = ENCODER_MAX;
			EncoderMode[Disp_CAN] = Encoder_get_position();
			Temp_pwm = (uint16_t)((float)(EncoderMode[Disp_CAN] * 100.0f) / (float)ENCODER_MAX);
			PWM_set(Temp_pwm);
			Temp_PWM_proc = (float)Temp_pwm;
			disp1color_printf(1, 11, FONTID_6X8M, "PWM = %0.0f %%", Temp_PWM_proc);			
			
			iSin = (float)Sin * 20.0f / (float)U2_5V;
			adcTerm = getADCresult(2);
			Temp_cels = Temperature_Compute(adcTerm);
			iSinCor = (float)CorrectTemperature(Temp_cels) * 20 / (float)U2_5V;
			disp1color_printf(1, 21, FONTID_6X8M, "Reg=%0.0f PWR=%0.0f STB=%0.0f ", (float)RegOn, (float)PWR_ON, (float)STB_ON);
			disp1color_printf(1, 31, FONTID_6X8M, "Задание =  %0.2f A ", iSin);
			disp1color_printf(1, 41, FONTID_6X8M, "Темп. корр. =  %0.2f A ", iSinCor);
			adcI = getADCresult(1);
			Temp_adcI_float_B = (float)adcI * 31.0f/4096.0f;
			disp1color_printf(1, 51, FONTID_6X8M, "I-LOAD =  %0.2f A", Temp_adcI_float_B);
		}
		else 
		{
			disp1color_printf(1, 11, FONTID_6X8M, "ERROR, NO DATA IN");
		}
	}	
}


void display_Temp1(void)
{
	disp1color_printf(1, 1, FONTID_10X16F, "TEST 1");
}

void display_Temp2(void)
{
	disp1color_printf(1, 1, FONTID_10X16F, "TEST 2");
}

void display_Temp3(void)
{
	disp1color_printf(1, 1, FONTID_10X16F, "TEST 3");
}

void display_Err(void)
{
	disp1color_printf(1, 1, FONTID_10X16F, "ERROR");
}


void run_testModeInit(void)
{
		TestMode_ = 1;
		DisplayControlMode_ = Disp_Temp1;
		Encoder_set_position(0);
}

uint16_t dysplayTestPwm;


void display_TestMode1(void)
{
			CLR_STB_OUT_PORT;
			SET_VOFF_OUT_PORT;

		disp1color_printf(1, 0, FONTID_6X8M, "Test Mode");
	  dysplayTestPwm = Encoder_get_position();
	  if(dysplayTestPwm > 0xFF) dysplayTestPwm = 0xFF;
		disp1color_printf(1, 11, FONTID_6X8M, "PW-EN  %u", PwrEn);
		disp1color_printf(1, 21, FONTID_6X8M, "Задание =  %0.2f %%", (float)dysplayTestPwm * 100.0f / (float)ENCODER_MAX);
    disp1color_printf(1, 31, FONTID_6X8M, "ШИМ  %u, %u, %u, %u, %u, %u", tPWM1,tPWM2,tPWM3,tPWM4,tPWM5,tPWM6);		
}

void display_TestMode2(void)
{	
			CLR_STB_OUT_PORT;
			SET_VOFF_OUT_PORT;

	  if(!Error_CAN)
		{
			disp1color_printf(1, 0, FONTID_6X8M, "Test Mode, CAN OK");
			disp1color_printf(1, 11, FONTID_6X8M, "VL = %0.0f VA = %0.2f", ((float)ProcPWM * 100.0f / 255.0f), ((float)UprADC * 3.3f / 255.0f));		
			disp1color_printf(1, 21, FONTID_6X8M, "Temper = %0.2f", ((float)TemperatureADC * 3.3f / 255.0f));				
			disp1color_printf(1, 31, FONTID_6X8M, "VOFF=%0.0f STB=%0.0f ", (float)VOFF_IN_PORT, (float)STB_IN_PORT);
			disp1color_printf(1, 41, FONTID_6X8M, "MASTER=%0.0f ERR=%0.0f ", (float)MASTER_IN_PORT, (float)ERR_IN_PORT);
		}
		else 
		{
			disp1color_printf(1, 11, FONTID_6X8M, "ERROR CAN, NO DATA IN");
		}	
}

uint16_t DisplayAutomsticTestMode = 0;


void display_TestMode3(void)
{	
	  if(!Error_CAN)
		{			
			  DisplayAutomsticTestMode += Encoder_get_position()/4;
				Encoder_set_position(0);
				if(DisplayAutomsticTestMode >= 5)
				{
					DisplayAutomsticTestMode = 0;
				}
				
				switch(DisplayAutomsticTestMode)
				{
					case 0:
							SET_VOFF_OUT_PORT;
							CLR_STB_OUT_PORT;
							SET_ERR_OUT_PORT;			
							disp1color_printf(1, 1, FONTID_6X8M, "VOFF=ERR=1,STB=0");
							disp1color_printf(1, 11, FONTID_6X8M, "принятые значения:");
							disp1color_printf(1, 21, FONTID_6X8M, "VOFF=%0.0f STB=%0.0f ", (float)VOFF_IN_PORT, (float)STB_IN_PORT);
							disp1color_printf(1, 31, FONTID_6X8M, "MASTER=%0.0f ERR=%0.0f ", (float)MASTER_IN_PORT, (float)ERR_IN_PORT);			
							disp1color_printf(1, 41, FONTID_6X8M, "Вращайте ручку для");
							disp1color_printf(1, 51, FONTID_6X8M, "следующего теста.");
						break;
					case 1:
							CLR_VOFF_OUT_PORT;
							SET_STB_OUT_PORT;
							CLR_ERR_OUT_PORT;	
							disp1color_printf(1, 1, FONTID_6X8M, "VOFF=ERR=0,STB=1");
							disp1color_printf(1, 11, FONTID_6X8M, "принятые значения:");
							disp1color_printf(1, 21, FONTID_6X8M, "VOFF=%0.0f STB=%0.0f ", (float)VOFF_IN_PORT, (float)STB_IN_PORT);
							disp1color_printf(1, 31, FONTID_6X8M, "MASTER=%0.0f ERR=%0.0f ", (float)MASTER_IN_PORT, (float)ERR_IN_PORT);	
							disp1color_printf(1, 41, FONTID_6X8M, "Вращайте ручку для");
							disp1color_printf(1, 51, FONTID_6X8M, "следующего теста.");				
						break;
					case 2:
							PWM_set(20);
							DAC_set_level(1,U1V);
#ifdef DAC2_INVERSION
							DAC_set_level(2,(4095 - U1V));
#else
							DAC_set_level(2,U1V);
#endif
							disp1color_printf(1, 1, FONTID_6X8M, "ADC1=ADC2=1, PWM=20,");		
							disp1color_printf(1, 11, FONTID_6X8M, "принятые значения:");						
							disp1color_printf(1, 21, FONTID_6X8M, "VL = %0.0f VA = %0.2f", ((float)ProcPWM * 100.0f / 255.0f), ((float)UprADC * 3.3f / 255.0f));		
							disp1color_printf(1, 31, FONTID_6X8M, "Temper = %0.2f", ((float)TemperatureADC * 3.3f / 255.0f));		
							disp1color_printf(1, 41, FONTID_6X8M, "Вращайте ручку для");
							disp1color_printf(1, 51, FONTID_6X8M, "следующего теста.");						
						break;
					case 3:
							PWM_set(50);
							DAC_set_level(1,U2_5V);
#ifdef DAC2_INVERSION
							DAC_set_level(2,(4095 - U2_5V));
#else
							DAC_set_level(2,U2_5V);
#endif
							disp1color_printf(1, 1, FONTID_6X8M, "ADC1=ADC2=2.5, PWM=50,");
							disp1color_printf(1, 11, FONTID_6X8M, "принятые значения:");					
							disp1color_printf(1, 21, FONTID_6X8M, "VL = %0.0f VA = %0.2f", ((float)ProcPWM * 100.0f / 255.0f), ((float)UprADC * 3.3f / 255.0f));		
							disp1color_printf(1, 31, FONTID_6X8M, "Temper = %0.2f", ((float)TemperatureADC * 3.3f / 255.0f));	
							disp1color_printf(1, 41, FONTID_6X8M, "Вращайте ручку для");
							disp1color_printf(1, 51, FONTID_6X8M, "следующего теста.");				
						break;
					case 4:
							PWM_set(80);
							DAC_set_level(1,0);
#ifdef DAC2_INVERSION
							DAC_set_level(2,(4095 - 0));
#else
							DAC_set_level(2,0);
#endif
							disp1color_printf(1, 1, FONTID_6X8M, "ADC1=ADC2=0, PWM=80,");	
							disp1color_printf(1, 11, FONTID_6X8M, "принятые значения:");						
							disp1color_printf(1, 21, FONTID_6X8M, "VL = %0.0f VA = %0.2f", ((float)ProcPWM * 100.0f / 255.0f), ((float)UprADC * 3.3f / 255.0f));		
							disp1color_printf(1, 31, FONTID_6X8M, "Temper = %0.2f", ((float)TemperatureADC * 3.3f / 255.0f));		
							disp1color_printf(1, 41, FONTID_6X8M, "Вращайте ручку для");
							disp1color_printf(1, 51, FONTID_6X8M, "следующего теста.");									
						break;
					
				}
		}
		else 
		{
			disp1color_printf(1, 11, FONTID_6X8M, "ERROR CAN, NO DATA IN");
			DisplayAutomsticTestMode = 0;
		}	
}

void display_TestMode(void)
{	
		DisplayTestMode += buttons_counter();
		if(DisplayTestMode > 2) DisplayTestMode = 0;
		buttons_counterClr();

		switch(DisplayTestMode)
		{
					case 0: display_TestMode1();
						break;
					case 1: display_TestMode2();
						break;
					case 2: display_TestMode3();
						break;
					default: display_Err();
		}		
}


void display_NormalMode(void)
{
TDispMode Num_encoder;
	
			if(CanMaster == 1)
			{
					PWM_set(0);
					DAC_set_level(1,0);
			}
	
			TestMode_ = 0;
	
	    DisplayControlMode += buttons_counter();
			if(DisplayControlMode > Disp_CAN) DisplayControlMode = Disp_ControlPWM;
			buttons_counterClr();
			
			Num_encoder = DisplayControlMode;
//			if(Num_encoder == Disp_CAN) Num_encoder = Disp_ControlPWM;
	
			if(DisplayControlMode_ != DisplayControlMode) 
			{
				  if(DisplayControlMode == Disp_ControlPWM)
					{
							PWM_set(0);
							EncoderMode[Disp_ControlPWM] = 0;
					}
					if(DisplayControlMode == Disp_ControlDAC1)
					{
							DAC_set_level(1,0);
							EncoderMode[Disp_ControlDAC1] = 0;						
					}
					Encoder_set_position(EncoderMode[Num_encoder]);
			}
			DisplayControlMode_ = DisplayControlMode;
				
			switch(DisplayControlMode)
			{
					case Disp_ControlPWM: display_ControlPWM();
						break;
					case Disp_ControlDAC1: display_ControlDAC1();
						break;
					case Disp_ControlDAC2: display_ControlDAC2();
						break;
					case Disp_ADC: display_ADC();
						break;
					case Disp_CAN: display_CAN();						
						break;
					case Disp_Temp1: display_Temp1();						
						break;
					case Disp_Temp2: display_Temp2();						
						break;
					case Disp_Temp3: display_Temp3();						
						break;
					default: display_Err();
			}	
}


void Disp_run(void)
{	
			disp1color_FillScreenbuff(0);
	    if(!TestMode) display_NormalMode();
			else display_TestMode();				
			disp1color_UpdateFromBuff();
			
}


