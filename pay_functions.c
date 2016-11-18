#include "pay_functions.h"

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
