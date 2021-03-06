#include "pay_functions.h"
#include "structs.h"
#include <stdbool.h>

void
messFunction(union PayloadStructs *zerg)
{

    printf("Message : %s\n", zerg->mess.message);
    free(zerg);

}

void
statFunction(union PayloadStructs *zerg)
{
    uint32_t armor = ntohl(zerg->stat.hit_armor) & 0xf;

    zerg->stat.hit_armor = ntohl(zerg->stat.hit_armor) >> 8;
    int32_t type = ntohl(zerg->stat.max_type) & 0xf;

    zerg->stat.max_type = ntohl(zerg->stat.max_type) >> 8;

    float speedy = converter(&zerg->stat.speed);

    const char *race;

    race = raceId(type);

    printf("Name    : %s\n", zerg->stat.name);
    printf("HP      : %d/%d\n", zerg->stat.hit_armor, zerg->stat.max_type);
    printf("Type    : %s\n", race);
    printf("Armor   : %d\n", armor);
    printf("Maxspeed: %fm/s\n", speedy);
    free(zerg);
}

void
commFunction(union PayloadStructs *zerg)
{
    uint32_t command = ntohs(zerg->comm.command);

    switch (command)
    {
    case (0):
        printf("GET_STATUS\n");
        break;
    case (1):
        printf("GOTO\n");
        float location = converter(&zerg->comm.parameter_two);

        printf("Bearing: %f\n", location);
        printf("Distance: %dm\n", ntohs(zerg->comm.parameter_one));
        break;
    case (2):
        printf("GET_GPS\n");
        break;
    case (4):
        printf("RETURN\n");
        break;
    case (5):
        printf("SET_GROUP\n");
        if (zerg->comm.parameter_one)
        {
            printf("Add zerg to: %d\n", zerg->comm.parameter_two);
        }
        else
        {
            printf("Remove zerg from: %d\n", zerg->comm.parameter_two);
        }
        break;
    case (6):
        printf("STOP\n");
        break;
    case (7):
        printf("REPEAT %d\n", ntohl(zerg->comm.parameter_two));
        break;
    default:
        printf("Packet Corrupt");
        break;
    }
    free(zerg);
}

void
gpsFunction(union PayloadStructs *zerg)
{


    uint64_t lat = doub_flip(&zerg->gps.lat_first, &zerg->gps.lat_second);
    double latitude = doub_converter(&lat);

    if (latitude >= 1)
    {
        printf("latitude : %lf deg. N\n", latitude);
    }
    else
    {
        printf("latitude : %lf deg. S\n", latitude * (-1));
    }

    uint64_t lon = doub_flip(&zerg->gps.long_first, &zerg->gps.long_second);
    double longitude = doub_converter(&lon);

    if (longitude >= 1)
    {
        printf("longitude: %lf deg. E\n", longitude);
    }
    else
    {
        printf("longitude: %lf deg. W\n", longitude * (-1));
    }

    float altitude = converter(&zerg->gps.altitude);

    printf("altitude : %.1fm\n", altitude * 1.8288);

    float bearing = converter(&zerg->gps.bearing);

    printf("bearing  : %f deg.\n", bearing);

    float speed = converter(&zerg->gps.speed);

    printf("speed    : %.fkm/h\n", speed * 3.6);

    float accuracy = converter(&zerg->gps.accuracy);

    printf("accuracy : %.fm\n", accuracy);
    free(zerg);

}
