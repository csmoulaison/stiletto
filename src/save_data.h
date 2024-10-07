#ifndef save_data_h_INCLUDED
#define save_data_h_INCLUDED

#include <stdint.h>

struct {
	int32_t ana_x;
	int32_t ana_y;
} typedef SaveData;

void save_data_serialize(SaveData* data, const char* path);
void save_data_deserialize(SaveData* data, const char* path);

#endif // save_data_h_INCLUDED
