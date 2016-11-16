#include "structs.h"

char *decode_message(int total, FILE *decode_file)
{
		char *message = malloc(total - zerg_header_length);
		fread(message, total-zerg_header_length, 1, decode_file);
		return message;
}


union payload *struct_init(int total, FILE *decode_file)
{
		union payload *memory = malloc(total - zerg_header_length);
		fread(memory, total-zerg_header_length, 1, decode_file);
		return memory;
}

