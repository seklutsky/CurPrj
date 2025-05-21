#include "include.h"

uint16_t CanMaster = 0, CanMaster_= 0;
uint16_t TestMode = 0, TestMode_= 0;
uint16_t PwrEn; 
uint16_t TestPWM_Channel;

uint16_t tPWM1,tPWM2,tPWM3,tPWM4,tPWM5,tPWM6;

uint16_t button_SW1;  
uint16_t button_SW2;  
uint16_t button_SW3;
uint16_t button_SW4;
uint16_t button_SW5; 
uint16_t button_SW6;  
uint16_t button_PWR_EN;
uint16_t button_SW8;

uint16_t button_SW13;  
uint16_t button_S_MASTER; 
uint16_t button_SW_TEST;
uint16_t button_SW_AUTO;

uint16_t button_ENC_BUTTON = 0xFFFF;

uint16_t buttonCounter = 0;


uint16_t buttons_counter(void)
{
	return buttonCounter;
}

void buttons_counterClr(void)
{
	buttonCounter = 0;
}


void buttons_tranfer(void)
{
	if(button_SW_AUTO == 0) 
	{		
		button_SW8 = button_SW8<<1;
		if(SW8) button_SW8 |= 1;		
		
		if(button_SW8 == 0xFFFF) 
		{
			CLR_STB_OUT_PORT;
		}
		else if(button_SW8 == 0)
		{
			SET_STB_OUT_PORT;
		}	
		
		button_PWR_EN = button_PWR_EN<<1;
		if(PWR_EN) button_PWR_EN |= 1;	
		
		if(button_PWR_EN == 0) 
		{
			PwrEn = 1;
			SET_VOFF_OUT_PORT;
		}
		else if(button_PWR_EN == 0xFFFF)
		{
			PwrEn = 0;
			CLR_VOFF_OUT_PORT;
		}	
  }
}


void buttons_read(void)
{
	
	button_SW1 = button_SW1<<1;  
	if(SW1) button_SW1 |= 1;
	button_SW2 = button_SW2<<1;   
	if(SW2) button_SW2 |= 1;
	button_SW3 = button_SW3<<1;
	if(SW3) button_SW3 |= 1;
	button_SW4 = button_SW4<<1;
	if(SW4) button_SW4 |= 1;
	button_SW5 = button_SW5<<1; 
	if(SW5) button_SW5 |= 1;	
	button_SW6 = button_SW6<<1;  
	if(SW6) button_SW6 |= 1;	

	button_SW13 = button_SW13<<1;  
	if(SW13) button_SW13 |= 1;	
	button_S_MASTER = button_S_MASTER<<1; 
	if(S_MASTER) button_S_MASTER |= 1;
	button_SW_TEST = button_SW_TEST<<1;
	if(SW_TEST) button_SW_TEST |= 1;	
	button_SW_AUTO = button_SW_AUTO<<1;
	if(SW_AUTO) button_SW_AUTO |= 1;
	
	
	
	button_ENC_BUTTON = button_ENC_BUTTON<<1;
	if(ENC_BUTTON) button_ENC_BUTTON |= 1;	
	
	if(button_ENC_BUTTON == 0x00FF) buttonCounter++;
		
	if(button_S_MASTER == 0xFFFF) 
	{
		CanMaster = 0;
	}
	else if(button_S_MASTER == 0)
	{
		CanMaster = 1;
	}
	
	if(button_SW_TEST == 0xFFFF) 
	{
		TestMode = 0;
	}
	else if(button_SW_TEST == 0)
	{
		TestMode = 1;
	}	

	if(TestMode)
	{
				if(button_SW1 == 0) {TestPWM_Channel |= 0x01; tPWM1 = 1;}
				else if(button_SW1 == 0xFFFF) {TestPWM_Channel &= ~0x01; tPWM1 = 0;}
				if(button_SW2 == 0) {TestPWM_Channel |= 0x02; tPWM2 = 1;}
				else if(button_SW2 == 0xFFFF) {TestPWM_Channel &= ~0x02; tPWM2 = 0;}				
				if(button_SW3 == 0) {TestPWM_Channel |= 0x04; tPWM3 = 1;}
				else if(button_SW3 == 0xFFFF) {TestPWM_Channel &= ~0x04; tPWM3 = 0;}					
				if(button_SW4 == 0) {TestPWM_Channel |= 0x08; tPWM4 = 1;}
				else if(button_SW4 == 0xFFFF) {TestPWM_Channel &= ~0x08; tPWM4 = 0;}							
				if(button_SW5 == 0) {TestPWM_Channel |= 0x10; tPWM5 = 1;}
				else if(button_SW5 == 0xFFFF) {TestPWM_Channel &= ~0x10; tPWM5 = 0;}
				if(button_SW6 == 0) {TestPWM_Channel |= 0x20; tPWM6 = 1;}
				else if(button_SW6 == 0xFFFF) {TestPWM_Channel &= ~0x20; tPWM6 = 0;}		
	}
}

