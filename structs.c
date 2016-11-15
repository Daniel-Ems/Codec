#include "structs.h"

char *decode_message(int total, FILE *decode_file)
{
		char *message = malloc(total - zerg_header_length);
		fread(message, total-zerg_header_length, 1, decode_file);
		return message;
}
