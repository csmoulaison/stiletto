#ifndef serialize_h_INCLUDED
#define serialize_h_INCLUDED

#include <stdint.h>
#include <stdio.h>

void serialize_line(FILE* f, char specifier, int32_t* args, uint32_t args_len);
int deserialize_line(FILE* f, char* out_specifier, int32_t* out_args, uint32_t* out_args_len);

#endif // serialize_h_INCLUDED
