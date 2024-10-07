#include "serialize.h"

#include <stdlib.h>

void serialize_line(FILE* f, char specifier, int32_t* args, uint32_t args_len) {
	fprintf(f, "%c", specifier);
	for(int i = 0; i < args_len - 1; i++) {
		fprintf(f, "%i ", args[i]);
	}
	fprintf(f, "%i\n", args[args_len - 1]); // fencepost
}

int deserialize_line(FILE* f, char* out_specifier, int32_t* out_args, uint32_t* out_args_len) {
	*out_specifier = fgetc(f);
	if(*out_specifier == EOF) {
		return EOF;
	}

	*out_args_len = 0;
	char c = 0;
	while(c != '\n') {
		char char_buf[16];
		int buf_index = 0;

		while((c = fgetc(f)) != ' ' && c != '\n') {
			char_buf[buf_index] = c;
			buf_index++;
		}
		char_buf[buf_index] = '\0';

		out_args[*out_args_len] = atoi(char_buf);
		(*out_args_len)++;
	}

	return 0;
}
