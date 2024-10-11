#ifndef save_data_h_INCLUDED
#define save_data_h_INCLUDED

#include <stdint.h>

struct {
	int16_t ana_x;
	int16_t ana_y;
	int16_t checkpoint;
} typedef SaveData;

void save_data_serialize(SaveData* data, const char* path);
void save_data_deserialize(SaveData* data, const char* path);

#endif // save_data_h_INCLUDED
