#include "save_data.h"

#include <stdio.h>
#include "serialize.h"

#define MAX_SAVE_DATA_ARGS 2

void save_data_serialize(SaveData* data, const char* path) {
	printf("Serializing save data...\n");

	FILE* file = fopen(path, "w");
	if(file == NULL) {
		printf("Save data file cannot be opened for serialization!\n");
		return;
	}

	int32_t args[2] = {data->ana_x, data->ana_y};
	serialize_line(file, 'a', args, 2);

	fclose(file);
}

void save_data_deserialize(SaveData* data, const char* path) {
	printf("Deserializing save data...\n");

	FILE* file = fopen(path, "r");
	if(file == NULL) {
		printf("Save data file cannot be opened for deserialization!\n");
		return;
	}

	char specifier;
	int32_t args[MAX_SAVE_DATA_ARGS];
	uint32_t args_len;

	int res = deserialize_line(file, &specifier, args, &args_len);
	if(res == EOF) {
		printf("Ana's position not in save data!\n");
	}

	data->ana_x = args[0];
	data->ana_y = args[1];
}
