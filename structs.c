#include "structs.h"
#include "pay_functions.h"

union payload *struct_init(int total, FILE *decode_file)
{
		union payload *memory = calloc((total - zerg_header_length +1 ),1);
		if(!memory){
			printf("NO MALLOC");
			}
		fread(memory, total-zerg_header_length , 1, decode_file);
		return memory;
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

const char *race(uint32_t type)
{
	const char *race = "No type";
	switch(type){
		case(0):
			race = "Overmind";
			break; 
		case(1):
			race = "Larva";
			break;
		case(2):
			race = "Cerebrate";
			break;
		case(3):
			race = "Overlord";
			break;
		case(4):
			race = "Queen";
			break;
		case(5):
			race = "Drone";
			break;
		case(6):
			race = "Zergling";
			break;
		case(7):
			race = "Lurker";
			break;
		case(8):
			race = "Brooding";
			break;
		case(9):
			race = "Hydralisk";
			break;
		case(10):
			race = "Guardian";
			break;
		case(11):
			race = "Scourge";
			break;
		case(12):
			race = "Ultralisk";
			break;
		case(13):
			race = "Mutalisk";
			break;
		case(14):
			race = "Defiler";
			break;
		case(15):
			race = "Devourer";
			break;
		default:
			return race;
			break;
	
	}
return race;
}





