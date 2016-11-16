#include "structs.h"




union payload *struct_init(int total, FILE *decode_file)
{
		union payload *memory = malloc(total - zerg_header_length);
		fread(memory, total-zerg_header_length, 1, decode_file);
		return memory;
}

void messages(union payload *zerg)
{
		printf("%s\n",zerg -> name.message);
		free(zerg);

}
