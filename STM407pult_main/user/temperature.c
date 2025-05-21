#include "include.h"

const unsigned int ArrT = 12;
const unsigned int ArrS = 12;

float Array[ArrS][ArrT] = {
    {     0,    10,	  15,	  20,	  25,	  30,	  35,	  40,	  45,	  50,	  55,	    60 },
    {     0,	 161,	 209,	 257,	 304,	 352,	 400,	 447,	 495,	 543,	 590,	    638},
		{	 2517,	1605,	1707,	1809,	1911,	2013,	2116,	2218,	2320,	2422,	2525,	   2627},
		{	 4064,	2494,	2630,	2765,	2901,	3037,	3173,	3310,	3447,	3584,	3722,	   3860},
		{	 5353,	3243,	3407,	3571,	3735,	3900,	4067,	4234,	4404,	4576,	4750,	   4928},
		{	 6427,	3884,	4071,	4259,	4449,	4640,	4835,	5034,	5238,	5449,	5669,	   5899},
		{	 7322,	4441,	4649,	4858,	5070,	5286,	5509,	5742,	5986,	6246,	6523,	   6824},
		{	 8068,	4934,	5158,	5385,	5618,	5859,	6112,	6381,	6671,	6989,	7339,	   7730},
		{	 8690,	5373,	5611,	5855,	6107,	6371,	6655,	6964,	7306,	7690,	8126,	   8624},
		{	 9208,	5765,	6016,	6274,	6543,	6831,	7146,	7496,	7894,	8351,	8881,	   9499},
		{	 9640,	6115,	6377,	6647,	6933,	7244,	7589,	7982,	8436,	8968,	9597,	  10343},
		{	10000,	6426,	6697,	6979,	7280,	7612,	7986,	8420,	8931,	9539,	10268,	11142}
   
};

int32_t Temperature_Compute(uint16_t F_trm__) {		

int32_t  LnX,Ln_B;
int32_t  t_cels;
uint32_t X,TEMP,T_1;	
const uint32_t Tn_F16=TN_F16;	
const int32_t Kelv=KELV;

				//t_cels = 150*65536;
				if(F_trm__ > 150) {
				
										X = div_32(F_trm__,(U2_5V-F_trm__));
										LnX = fxlog(X);
										Ln_B = (((int)(LnX * B_T)) >> (RAZ_D-RAZ_Tn));				
										T_1 = Ln_B+Tn_F16;
										TEMP = div_32(((uint32_t)1<<(RAZ_BASE+RAZ_Tn)),T_1);

										t_cels = (TEMP-Kelv); // hight byte is kelvin
				}
				return t_cels;
}



uint16_t CorrectTemperature (int32_t  t_cels) {
	
float float_t_cels, float_Sout, float_Sin;	
char iii,it,is;	
float Tn=10,Tv=10,Sn=0,Sv=0,Snm,Svm,Snb,Svb,S1,S2;	
int32_t Result;	
uint16_t i_d;
	
									float_t_cels = ((float)t_cels)/((float)65536);
									float_Sin = ((float)Sin)/((float)U2_5V)*10000;
					
									iii=1;
									
									while(float_t_cels > Array[0][iii]) iii++;
									it = iii;
									Tn = Array[0][it-1];
									Tv = Array[0][it];
					
									iii=1;
									
									while(float_Sin > Array[iii][0]) iii++;
									is = iii;
									Sn = Array[is-1][0];
									Sv = Array[is][0];									
									
									Snm = Array[is-1][it-1];
									Svm = Array[is-1][it];
									Snb = Array[is][it-1];
									Svb = Array[is][it];
					
									S1 = Snm + (float_Sin - Sn)*(Snb - Snm)/(Sv-Sn);
									S2 = Svm + (float_Sin - Sn)*(Svb - Svm)/(Sv-Sn);
									float_Sout = S1 + (S2 - S1)*(float_t_cels - Tn)/(Tv - Tn);
									
									Result = (uint16_t)((float)I_20A*(float_Sout/10000));
									
									if(Result > I_MAX_CORRECT) i_d = I_MAX_CORRECT;
									else i_d = Result;
									return i_d;
}
