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

int StatusPayload(char *packetCapture, FILE *writeFile, struct EncodeZerg *ez)
	{
	int exit = 0;
	int fCheck;

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

	struct EncodeStatusPacket esp;

	a=0;
	packetCapture = strcasestr(packetCapture, "hp");

	notDigit(&packetCapture);
	int number = htonl(strtol(packetCapture, NULL, 10));
	esp.hitPoints = number >> 8;

	while(isalnum(*packetCapture))
	{
		packetCapture++;
	}
	a=0;
	notDigit(&packetCapture);
	number = htonl(strtol(packetCapture, NULL, 10));
	esp.maxPoints = number >> 8;

	const char *typeField[16] = {"Overmind", "Larva", "Cerebrate", "Overlord", "Queen", "Drone", "Zergling", "Lurker", "Broodling", "Hydralisk", "Guardian", "Scourge", "Ultralisk", "Mutalisk", "Defiler", "Devourer"}; 

	int z = 0;
	while(strcasestr(packetCapture, typeField[z])== NULL)
	{
		z++;
	}

	packetCapture = strcasestr(packetCapture, typeField[z]);
	esp.type = z;

	packetCapture = strcasestr(packetCapture, "Armor");
	notDigit(&packetCapture);
	esp.armor = strtol(packetCapture, NULL, 10);

	float tmpNum;
	packetCapture = strcasestr(packetCapture, "maxspeed");
	notDigit(&packetCapture);
	tmpNum = strtof(packetCapture, NULL);
	esp.speed = convertInt(tmpNum);

	int size = (sizeof(esp) + strlen(name));

	ez -> length = ntohl((12 + size)) >> 8;

	writeHeaders(writeFile, size); 
	if(exit)
	{
		return exit;
	}

	fCheck = fwrite(ez, sizeof(*ez), 1, writeFile);
	exit = writeCheck(fCheck);
	if(exit)
	{
		return exit;
	}

	fCheck = fwrite(&esp,sizeof(esp),1, writeFile);
	exit = writeCheck(fCheck);
	if(exit)
	{
		return exit;
	}

	fCheck = fwrite(name, strlen(name),1,writeFile);
	exit = writeCheck(fCheck);
	if(exit)
	{
		return exit;
	}

	free(newName);
	return exit;
	}

int CommandPayload(char *packetCapture, FILE *writeFile, struct EncodeZerg *ez)
	{
		int a = 0;
		int exit = 0;
		int fCheck;
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

			ez -> length = ntohl((12 + size)) >> 8;

			exit = writeHeaders(writeFile, size);
			if(exit)
			{
				return exit;
			}

			fCheck = fwrite(ez, sizeof(*ez), 1, writeFile);
			exit = writeCheck(fCheck);
			if(exit)
			{
				return exit;
			}

			fCheck = fwrite(&cp, 2, 1, writeFile); 
			exit = writeCheck(fCheck);
			if(exit)
			{
				return exit;
			}
		}
		else if(command == 1)
		{
			cp.command = htons(command);
			packetCapture = strcasestr(packetCapture, "Bearing");
			notDigit(&packetCapture);
			float tmpNum = strtof(packetCapture, NULL);

			cp.parameter_two = convertInt(tmpNum);
			notDigit(&packetCapture);
			packetCapture = strcasestr(packetCapture, "Distance");
			notDigit(&packetCapture);
			cp.parameter_one = htons(strtol(packetCapture, NULL, 10));

			ez -> length = ntohl((12 + size)) >> 8;

			exit = writeHeaders(writeFile, size);
			if(exit)
			{
				return exit;
			}

			fCheck = fwrite(ez, sizeof(*ez), 1, writeFile);
			exit = writeCheck(fCheck);
			if(exit)
			{
				return exit;
			}

			fCheck = fwrite(&cp, sizeof(cp), 1, writeFile);
			exit = writeCheck(fCheck);
			if(exit)
			{
				return exit;
			}

		}
		else if(command == 5)
		{
			a = 0;
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

			ez -> length = ntohl((12  + size)) >> 8;

			exit = writeHeaders(writeFile, size);
			if(exit)
			{
				return exit;
			}

			fCheck = fwrite(ez, sizeof(*ez), 1, writeFile);
			exit = writeCheck(fCheck);
			if(exit)
			{
				return exit;
			}

			fCheck = fwrite(&cp, sizeof(cp), 1, writeFile);
			exit = writeCheck(fCheck);
			if(exit)
			{
				return exit;
			}

		}
		else if(command == 7)
		{
			cp.command = htons(command);
			notDigit(&packetCapture);
			cp.parameter_two = htonl(strtol(packetCapture,NULL,10));
			cp.parameter_one = 0x0000;

			ez -> length = ntohl((12 + size)) >> 8;

			exit = writeHeaders(writeFile, size);
			if(exit)
			{
				return exit;
			}

			fCheck = fwrite(ez, sizeof(*ez), 1, writeFile);
			exit = writeCheck(fCheck);
			if(exit)
			{
				return exit;
			}

			fCheck = fwrite(&cp, sizeof(cp), 1, writeFile);
			exit = writeCheck(fCheck);
			if(exit)
			{
				return exit;
			}

		}
		else
		{
			printf("Packet Corrupt");
			exit = 1;
			return exit;
		}
	return exit;
	}

int GpsPayload(char *packetCapture, FILE *writeFile, struct EncodeZerg *ez)
	{
		int exit = 0;
		int fCheck;
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

		ez -> length = htonl((12 + size))>> 8;

		exit = writeHeaders(writeFile, size);
		if(exit)
		{
			return exit;
		}
 
		fCheck = fwrite(ez, sizeof(*ez), 1, writeFile);
		exit = writeCheck(fCheck);
		if(exit)
		{
			return exit;
		}

		fCheck = fwrite(&eg, sizeof(eg), 1, writeFile);
		exit = writeCheck(fCheck);
		if(exit)
		{
			return exit;
		}
		
		return exit;
	}

int MessagePayload(char *packetCapture, FILE *writeFile, struct EncodeZerg *ez)
	{
		int exit = 0;
		int fCheck;
		while(!isalnum(*packetCapture))
		{
			packetCapture++;
		}

		int size = strlen(packetCapture) -1;

		ez -> length = htonl((12 + size)) >> 8;

		exit = writeHeaders(writeFile, size);
		if(exit)
		{
				return exit;
		}

		fCheck = fwrite(ez, sizeof(*ez), 1, writeFile);
		exit = writeCheck(fCheck);
		if(exit)
		{
			return exit;
		}

		fCheck = fwrite(packetCapture, strlen(packetCapture) -1 , 1, writeFile);
		exit = writeCheck(fCheck);
		if(exit)
		{
			return exit;
		}

		return exit;
	}


