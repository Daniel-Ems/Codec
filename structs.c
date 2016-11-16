#include "structs.h"




union payload *struct_init(int total, FILE *decode_file)
{
		union payload *memory = calloc((total - zerg_header_length )+1,1);
		if(!memory){
			printf("NO MALLOC");
			}
		fread(memory, total-zerg_header_length , 1, decode_file);
		return memory;
}

void messages(union payload *zerg)
{

		printf("%s\n", zerg -> name.message);
		free(zerg);

}

void status(union payload *zerg)
{
		printf("%x\n", zerg-> zerg.hit_armor);
		printf("%x\n", zerg-> zerg.max_type);
		printf("%x\n", zerg-> zerg.speed);
		printf("%s\n", zerg-> zerg.name);
		free(zerg);
} 
