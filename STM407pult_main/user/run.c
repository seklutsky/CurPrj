#include "include.h"



void run_testMode(void)
{
		if(!TestMode_) run_testModeInit();
		CAN_exchangeTest(dysplayTestPwm, TestPWM_Channel);	
}

void run_normalMode(void)
{
	if(CanMaster) 
	{
		if(!CanMaster_) 
		{
					can_send_counter = 0;
					can1_init(1);
					CanMaster_ = 1;
		}
		else	CAN_exchange();
	}
	else if(CanMaster_)		
	{
			can1_init(0);
			CanMaster_ = 0;
	}	
}


void Run(void)
{
	buttons_read();
//	if(!TestMode) buttons_tranfer();
	
	if(StartCounter >= START_TIME ) 
	{	
			if(testTimeDisp == Disp_process_start)
			{		
				Disp_run();
				testTimeDisp = Disp_process_ended;
			}
						
			if(!TestMode) run_normalMode();
			else run_testMode();
	}
}
