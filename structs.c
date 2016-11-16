#include "structs.h"
#include <arpa/inet.h>



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
		zerg -> zerg.hit_armor = zerg -> zerg.hit_armor >> 16;
		int32_t type = ntohl(zerg -> zerg.max_type) & 0xf;
		zerg -> zerg.max_type = ntohl(zerg -> zerg.max_type) >> 8;
		//zerg -> zerg.speed = zerg -> zerg.speed;

		//TODO: put in function, will need for longitude and latitude
 		union converter{
			float speed;
			uint32_t test;
		};
		union converter speed_test; 
		speed_test.test = ntohl(zerg->zerg.speed);
		float speedy = speed_test.speed;

		printf("Hit %x\n", zerg-> zerg.hit_armor);
		printf("type %x\n", type);
		printf("max %x\n", zerg-> zerg.max_type);
		printf("speed %f\n",speedy);
		printf("name %s\n", zerg-> zerg.name);
		free(zerg);
} 
