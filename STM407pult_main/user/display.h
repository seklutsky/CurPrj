
/*
%c				������
%d				���������� ����� ����� �� ������
%i				���������� ����� ����� �� ������
%e				������� ������ (�������� ����� �)
%�				������� ������ (��������� ����� �)
%f				���������� ����� � ��������� ������
%g				� ����������� �� ����, ����� ������ ������, ����������� ���� %e, ���� %f
%G				� ����������� �� ����, ����� ������ ������, ����������� ���� %E, ���� %f
%o				������������ ����� ��� �����
%s				������ ��������
%u				���������� ����� ����� ��� �����
%x				����������������� ����� ��� ����� (�������� �����)
%X				����������������� ����� ��� ����� (��������� �����)
%�				���������
%n				��������� �� ������������� ����������. ������������ �������� ���������� ���� ������������� ���������� ���������� ��������, ���������� ����� ���
%%				���� %
*/

#include "types.h"


extern TDispProcess testTimeDisp;
extern uint16_t dysplayTestPwm;

void Disp_preved(void); 
uint16_t display_getEncoderMode(TDispMode Mode);
void display_initControlDAC2(void);
void display_ControlPWM(void);
void display_ControlDAC1(void);
void display_ControlDAC2(void);
void display_ADC(void);
void display_CAN(void);
void display_Temp1(void);
void display_Temp2(void);
void display_Temp3(void);
void display_Err(void);
void run_testModeInit(void);
void display_TestMode1(void);
void display_TestMode2(void);
void display_TestMode3(void);
void display_TestMode(void);
void display_NormalMode(void);
void Disp_run(void);



