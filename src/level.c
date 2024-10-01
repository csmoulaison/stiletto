#include "level.h"
#include <stdio.h>

void level_serialize(Level* level) {

}

void level_deserialize(Level* level) {
	FILE *file = fopen(PATH_LEVEL, "r");
	if(file == NULL) {
		printf("Level data file cannot be opened.");
	}

	char c;
	while((c = fgetc(file)) != EOF) {
		if(c == '\0' || c == '\n) {
			continue;
		}

		if(c == 'S') {
			while((c = f
		}
	}
}
