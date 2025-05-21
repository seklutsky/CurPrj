
/*
%c				Символ
%d				Десятичное целое число со знаком
%i				Десятичное целое число со знаком
%e				Научный формат (строчная буква е)
%Е				Научный формат (прописная буква Е)
%f				Десятичное число с плавающей точкой
%g				В зависимости от того, какой формат короче, применяется либо %e, либо %f
%G				В зависимости от того, какой формат короче, применяется либо %E, либо %f
%o				Восьмеричное число без знака
%s				Строка символов
%u				Десятичное целое число без знака
%x				Шестнадцатеричное число без знака (строчные буквы)
%X				Шестнадцатеричное число без знака (прописные буквы)
%р				Указатель
%n				Указатель на целочисленную переменную. Спецификатор вызывает присвоение этой целочисленной переменной количества символов, выведенных перед ним
%%				Знак %
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



