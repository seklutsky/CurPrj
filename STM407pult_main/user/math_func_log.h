
typedef struct {
	int16_t Value16in;		// Нефильрованное значение
	int16_t Value16filtered;	// Фильрованное значение
	int32_t Value32;			// Конечное напряжение тренировки
	int16_t ShiftFilter;		// Filters
} Filtered;


uint32_t div_32(uint32_t x, uint32_t y);
int32_t fxlog(uint32_t x);
short median_filter (short* data_array, uint8_t array_size);
short median_filter_my (short* data_array, uint8_t array_size);
int16_t Filter(int16_t inValue, Filtered *Struct);





