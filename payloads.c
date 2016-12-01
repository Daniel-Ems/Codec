#define _GNU_SOURCE
#include <stdio.h>
#include <sysexits.h>
#include <sys/stat.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "structs.h"
#include "encode_function.h"
#include "payloads.h"

void StatusPayload(char *packetCapture, FILE *writeFile, struct EncodeZerg *ez)
	{
	char *name = calloc(1, 6 );
	char *newName = name;

	int a = 0;
	while(!isalnum(*packetCapture))
	{
		packetCapture++;
	}
	while(isalnum(*packetCapture))
	{
		name[a] = *packetCapture;
		packetCapture++;
		a++;
	}

	printf("Name:%s\n", name);
	struct EncodeStatusPacket esp;

	a=0;
	packetCapture = strcasestr(packetCapture, "hp");

	notDigit(&packetCapture);
	int number = htonl(strtol(packetCapture, NULL, 10));
	esp.hitPoints = number >> 8;
	printf("hitPoints: %d\n", esp.hitPoints);
	while(isalnum(*packetCapture))
	{
		packetCapture++;
	}
	a=0;
	notDigit(&packetCapture);
	number = htonl(strtol(packetCapture, NULL, 10));
	esp.maxPoints = number >> 8;
	printf("maxPoints: %d\n", esp.maxPoints);

	const char *typeField[16] = {"Overmind", "Larva", "Cerebrate", "Overlord", "Queen", "Drone", "Zergling", "Lurker", "Broodling", "Hydralisk", "Guardian", "Scourge", "Ultralisk", "Mutalisk", "Defiler", "Devourer"}; 

	int z = 0;
	while(strcasestr(packetCapture, typeField[z])== NULL)
	{
		z++;
	}

	packetCapture = strcasestr(packetCapture, typeField[z]);
	esp.type = z;
	printf("type: %x\n", z);

	packetCapture = strcasestr(packetCapture, "Armor");
	notDigit(&packetCapture);
	esp.armor = htons(strtol(packetCapture, NULL, 10));
	printf("armor: %x\n", esp.armor);

	float tmpNum;
	packetCapture = strcasestr(packetCapture, "maxspeed");
	notDigit(&packetCapture);
	tmpNum = strtof(packetCapture, NULL);
	esp.speed = convertInt(tmpNum);

	printf("converted speed %x\n", esp.speed);

	int size = (sizeof(esp) + strlen(name));

	writeHeaders(writeFile, size); 
	ez -> length = ntohl((12 + size)) >> 8;
	fwrite(ez, sizeof(*ez), 1, writeFile);
	fwrite(&esp,sizeof(esp),1, writeFile);
	fwrite(name, strlen(name),1,writeFile);

	free(newName);
	}

void CommandPayload(char *packetCapture, FILE *writeFile, struct EncodeZerg *ez)
	{
		int a = 0;
		const char *commandGroups[8] = {"GET_STATUS", "GOTO", "GET_GPS", "RESERVED",
		"RETURN", "SET_GROUP", "STOP", "REPEAT"}; 

		const char *addRemove[2] = {"Remove", "Add" };

		struct CommandPacket cp;
		a = 0;
		int size = 8;
		while(strcasestr(packetCapture, commandGroups[a]) == NULL)
		{
			a++;
		}

		int command = a;
		if(command % 2 == 0 || command == 3 )
		{
			cp.command = htons(command);
			int size = 2;
			writeHeaders(writeFile, size);
			ez -> length = ntohl((12 + size)) >> 8;
			fwrite(ez, sizeof(*ez), 1, writeFile);
			fwrite(&cp, 2, 1, writeFile); 
		}
		else if(command == 1)
		{
			cp.command = htons(command);
			packetCapture = strcasestr(packetCapture, "Location");
			notDigit(&packetCapture);
			float tmpNum = strtof(packetCapture, NULL);
			cp.parameter_two = convertInt(tmpNum);
			notDigit(&packetCapture);
			while(isdigit(*packetCapture))
			{
				packetCapture++;
			}
			notDigit(&packetCapture);
			while(isdigit(*packetCapture))
			{
				packetCapture++;
			}
			cp.parameter_one = htons(strtol(packetCapture, NULL, 10));

			writeHeaders(writeFile, size);
			ez -> length = ntohl((12 + size)) >> 8;
			fwrite(ez, sizeof(*ez), 1, writeFile);
			fwrite(&cp, sizeof(cp), 1, writeFile);
		}
		else if(command == 5)
		{
			a = 0;
			printf("packetCapture %s\n", packetCapture);
			cp.command = htons(command);
			while(strcasestr(packetCapture, addRemove[a]) == NULL)
			{
				a++;
			}
			cp.parameter_one = htons(a);
			packetCapture = strcasestr(packetCapture, "to");
			while(isalpha(*packetCapture))
			{
				packetCapture++;
			}
			packetCapture++;
			cp.parameter_two = strtol(packetCapture,NULL,10);

			writeHeaders(writeFile, size);
			ez -> length = ntohl((12  + size)) >> 8;
			fwrite(ez, sizeof(*ez), 1, writeFile);
			fwrite(&cp, sizeof(cp), 1, writeFile);
		}
		else if(command == 7)
		{
			cp.command = htons(command);
			notDigit(&packetCapture);
			cp.parameter_two = htonl(strtol(packetCapture,NULL,10));
			cp.parameter_one = 0x0000;

			writeHeaders(writeFile, size);
			ez -> length = ntohl((12 + size)) >> 8;
			fwrite(ez, sizeof(*ez), 1, writeFile);
			fwrite(&cp, sizeof(cp), 1, writeFile);
		}
		else
		{
			printf("Packet Corrupt");
		}
	}

void GpsPayload(char *packetCapture, FILE *writeFile, struct EncodeZerg *ez)
	{
		struct EncodeGps eg;
	//const char *gpsFields[5] = {"Longitude", "Altitude", "Bearing", "Speed", 	//"Accuracy"};

		double latitude = strtod(packetCapture, NULL);
		if(strstr(packetCapture, "deg. S"))
		{
			latitude = -latitude;
		}
		eg.latitude = convertDoub(latitude);

		packetCapture = strcasestr(packetCapture, "Longitude");
		notDigit(&packetCapture);

		double longitude = strtod(packetCapture, NULL);
		if(strstr(packetCapture, "deg. W"))
		{
			longitude = -longitude;
		}
		eg.longitude = convertDoub(longitude);

		packetCapture = strcasestr(packetCapture, "Altitude");
		notDigit(&packetCapture);
		float altitude = strtof(packetCapture, NULL);
		eg.altitude = convertInt((altitude/1.8288));

		packetCapture = strcasestr(packetCapture, "Bearing");
		notDigit(&packetCapture);
		float bearing = strtof(packetCapture, NULL);
		eg.bearing = convertInt(bearing);

		packetCapture = strcasestr(packetCapture, "Speed");
		notDigit(&packetCapture);
		float speed = strtof(packetCapture, NULL);
		eg.speed = convertInt((speed / 3.6));

		packetCapture = strcasestr(packetCapture, "Accuracy");
		notDigit(&packetCapture);
		float accuracy = strtof(packetCapture,NULL);
		eg.accuracy = convertInt(accuracy);

		int size = sizeof(eg);
		printf("sizeof%d",size);

		writeHeaders(writeFile, size);
		ez -> length = htonl((12 + size))>> 8;

		printf("length %x\n", ez->length); 
		fwrite(ez, sizeof(*ez), 1, writeFile);
		fwrite(&eg, sizeof(eg), 1, writeFile);
	}

void MessagePayload(char *packetCapture, FILE *writeFile, struct EncodeZerg *ez)
	{
		while(!isalnum(*packetCapture))
		{
			packetCapture++;
		}

		int size = strlen(packetCapture) -1;
		writeHeaders(writeFile, size);
		ez -> length = htonl((12 + size)) >> 8;
		printf("Length %x\n", ez->length);
		fwrite(ez, sizeof(*ez), 1, writeFile);
		fwrite(packetCapture, strlen(packetCapture) -1 , 1, writeFile);
	}


