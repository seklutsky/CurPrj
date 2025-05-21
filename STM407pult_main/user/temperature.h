
#define TN										(273+25)
#define B_TEMP								3380			
#define RAZ_BASE							16
#define RAZ_D 								25
#define RAZ_Tn 								10	
#define B_T 									((1<<RAZ_D)/B_TEMP)
#define	TN_F16								((1<<(RAZ_BASE+RAZ_Tn))/TN)
#define KELV   								(273<<RAZ_BASE)


#define I0										-3.000// 0 to -50
#define m											-0.00929// 0 to -0,5
#define D0										2.1429// 0,1 to 20
#define tmf										20.0// 10 to 60
#define Ieq										12.00// 1 to 12

int32_t Temperature_Compute(uint16_t F_trm__);
uint16_t CorrectTemperature (int32_t  t_cels);
