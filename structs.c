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

		printf("Message : %s\n", zerg -> name.message);
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
		printf("HP      : %d/%d\n", zerg -> status.hit_armor,
				zerg-> status.max_type);
		printf("type    : %d\n", type);
		printf("Armor   : %d\n", armor);
		printf("speed   : %f\n",speedy);
		printf("name    : %s\n", zerg-> status.name);
		free(zerg);
} 

//TODO: if time, find a way to clean code
void com_payload(union payload *zerg)
{
	uint32_t command = zerg->command.command;
		switch(command){
			case (0):
				printf("GET_STATUS\n");
				break;
			case (1):
				printf("GOTO\n");
				float location = converter(&zerg->command.parameter_two);
				printf("location %f\n", location);
				printf("%x m\n", zerg->command.parameter_one);
				break;
			case (2):
				printf("GET_GPS\n");
				break;
			case (4):
				printf("RETURN\n");
				break;
			case (5):
				printf("SET_GROUP\n");
				if(zerg->command.parameter_one)
				{
					printf("Add zerg to %x\n", zerg->command.parameter_two);
				}else{
					printf("Remove zerg from %x\n", zerg->command.parameter_two);
				}
				break;
			case (6):
				printf("STOP\n");
				break;
			case (7):
				printf("REPEAT %x\n", zerg->command.parameter_two);
				break;
		}
	free(zerg);
}

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

void print_zerg_header(struct zerg_header zerg)
{

	zerg.version = (zerg.version &0x10) >> 4;

	printf("Version : %d\n", zerg.version);
	printf("Sequence: %d\n", ntohl(zerg.id));
	printf("From    : %d\n", ntohs(zerg.source));
	printf("To      : %d\n", ntohs(zerg.dest));
}


//compliments of DOW 
uint64_t doub_flip(uint32_t *most, uint32_t *least)
{

		uint64_t flipped_double;
		*most = ntohl(*most);
		*least = ntohl(*least);

		flipped_double = *most;
		flipped_double = flipped_double << 32;
		flipped_double = flipped_double + *least;

		return flipped_double;
}

double doub_converter(uint64_t *number)
{
	union doub_converter{
		double place_holder;
		uint64_t old_number;
	};
	union doub_converter conversion;
	conversion.old_number = *number;
	double new_number = conversion.place_holder;
	return new_number;
}



