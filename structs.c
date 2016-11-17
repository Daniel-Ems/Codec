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

		printf("Message:%s\n", zerg -> name.message);
		free(zerg);

}

void stat_payload(union payload *zerg)
{
		uint32_t armor = zerg -> status.hit_armor &0xf;
		zerg -> status.hit_armor = ntohl(zerg -> status.hit_armor) >> 8;
		int32_t type = ntohl(zerg -> status.max_type) & 0xf;
		zerg -> status.max_type = ntohl(zerg -> status.max_type) >> 8;
		//zerg -> status.speed = zerg -> status.speed;

		//TODO: put in function, will need for longitude and latitude
 		float speedy = converter(&zerg->status.speed);

		//TODO: make a switch case that determines the type of the zerg
		//(probably in a function)
		printf("HP :%x/%x\n", zerg -> status.hit_armor, zerg-> status.max_type);
		printf("type %x\n", type);
		printf("Armor :%x\n", armor);
		printf("speed %f\n",speedy);
		printf("name %s\n", zerg-> status.name);
		free(zerg);
} 

/*
void com_payload(union payload *zerg)
{
	uint32_t command = zerg->command.command;
		switch(command)
			case (0):
				printf("GET_STATUS");
				break;
			case (1):
				printf("GOTO")
				break;
			case (2):
				break;
			case (3):
				break;
			case (4):
				break;
			case (5):
				break;
			case (6):
				break;
			case (7):
				break;
}
*/
float converter(uint32_t *thing)
{
	union converter{
			float speed;
			uint32_t test;
		};
		union converter speed_test; 
		speed_test.test = ntohl(*thing);
		float speedy = speed_test.speed;
		return speedy;
}

