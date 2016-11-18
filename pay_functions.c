#include "pay_functions.h"
#include "structs.h"

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

		float speedy = converter(&zerg->status.speed);

		const char *test;
		test = race(type);

		printf("HP      : %d/%d\n", zerg -> status.hit_armor,
				zerg-> status.max_type);
		printf("type    : %s\n", test);
		printf("Armor   : %d\n", armor);
		printf("speed   : %fm/gs\n",speedy);
		printf("name    : %s\n", zerg-> status.name);
		free(zerg);
}

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

void gps(union payload *zerg)
{


	uint64_t lat = doub_flip(&zerg->gps.lat_first, &zerg->gps.lat_second);
	double latitude = doub_converter(&lat);
	if(latitude >= 1)
	{
		printf("latitude : %lf deg. N\n", latitude);
	}else{
		printf("latitude : %lf deg. S\n", latitude * (-1));
	}

	uint64_t lon = doub_flip(&zerg->gps.long_first, &zerg->gps.long_second);
	double longitude = doub_converter(&lon);
	if(longitude >= 1)
	{
		printf("longitude: %lf deg. E\n", longitude);
	}else{
		printf("longitude: %lf deg. W\n", longitude * (-1));
	}

	float altitude = converter(&zerg->gps.altitude);
	printf("altitude : %.1fm\n", altitude * 1.8288);

	float bearing = converter(&zerg->gps.bearing);
	printf("bearing  : %f deg.\n", bearing );

	float speed = converter(&zerg->gps.speed);
	printf("speed    : %.fkm/h\n", speed * 3.6);

	float accuracy = converter(&zerg->gps.accuracy);
	printf("accuracy : %.fm\n", accuracy);

}


