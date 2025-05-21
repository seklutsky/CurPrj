#include "include.h"


uint32_t div_32(uint32_t x, uint32_t y)	{
	
uint32_t x_l,res_h,res_l,result;
	
	if(y == 0) return 0xFFFFFFFF;
	else {

		    res_h = x/y;
		    x=x-res_h*y;

				x_l = ((int32_t)x)<<16;				

				res_l = x_l/y;
				result=res_l+(res_h<<16);
				return result;
	}
}


int32_t fxlog(uint32_t x) {
						uint32_t t,y;

						y=0xa65af;
						if(x<0x00008000) x<<=16,              y-=0xb1721;
						if(x<0x00800000) x<<= 8,              y-=0x58b91;
						if(x<0x08000000) x<<= 4,              y-=0x2c5c8;
						if(x<0x20000000) x<<= 2,              y-=0x162e4;
						if(x<0x40000000) x<<= 1,              y-=0x0b172;
						t=x+(x>>1); if((t&0x80000000)==0) x=t,y-=0x067cd;
						t=x+(x>>2); if((t&0x80000000)==0) x=t,y-=0x03920;
						t=x+(x>>3); if((t&0x80000000)==0) x=t,y-=0x01e27;
						t=x+(x>>4); if((t&0x80000000)==0) x=t,y-=0x00f85;
						t=x+(x>>5); if((t&0x80000000)==0) x=t,y-=0x007e1;
						t=x+(x>>6); if((t&0x80000000)==0) x=t,y-=0x003f8;
						t=x+(x>>7); if((t&0x80000000)==0) x=t,y-=0x001fe;
						x=0x80000000-x;
						y-=x>>15;
						return y;
}
 
short median_filter (short* data_array, uint8_t array_size)
{
	int16_t i, l;
	int16_t median, tmp_;
// bubble sort
	for (i = 0; i<array_size; i++)
	{
		for (l=(i+1); l<array_size; l++)
		if (data_array[i] < data_array[l]) 
			{
				tmp_ = data_array[i];
				data_array[i] = data_array[l];
				data_array[l] = tmp_; 
			}	
			
	}
median = data_array[array_size/2];
return median;
}
//==================================
short median_filter_my (short* data_array, uint8_t array_size)
{
	long int current_sum = 0;
	int16_t i;
	int16_t median;
	
	for (i = 0; i<array_size; i++)
	{
			current_sum += data_array[i];		
	}
median = current_sum/array_size;
return median;
}




// Фильтр сигнала
int16_t Filter(int16_t inValue, Filtered *Struct) {	
	(*Struct).Value16in = inValue;	
	(*Struct).Value32+=(int32_t)((*Struct).Value16in)-(int32_t)((*Struct).Value16filtered);
	(*Struct).Value16filtered =(int16_t)(((*Struct).Value32)>>((*Struct).ShiftFilter));
	return ((*Struct).Value16filtered);
}

