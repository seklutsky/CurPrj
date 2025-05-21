

void display_NormalMode(void)
{
TDispMode Num_encoder;
	
			TestMode_ = 0;
	
	    DisplayControlMode += buttons_counter();
			if(DisplayControlMode > Disp_CAN) DisplayControlMode = Disp_ControlPWM;
			buttons_counterClr();
			
			Num_encoder = DisplayControlMode;
			if(Num_encoder == Disp_CAN) Num_encoder = Disp_ControlPWM;
	
			if(DisplayControlMode_ != DisplayControlMode) Encoder_set_position(EncoderMode[Num_encoder]);
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


