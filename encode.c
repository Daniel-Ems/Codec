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
#include "encode_structs.c"


int main (int argc, char *argv[])
{
	FILE *encodeFile;
	FILE *writeFile;

	struct stat *buf = malloc( sizeof(*buf));
	stat(argv[1], buf);

	off_t fileEnd = buf->st_size;
	if(fileEnd ==0)
	{
		return EX_USAGE;
	}

	printf("fileEnd %zd\n", fileEnd); 

	if(argc < 3)
	{
		printf("Please provide a file to be encoded, and to be written too\n");
		return EX_USAGE;
	}
	else
	{ 
		encodeFile = fopen(argv[1], "rb");
		if(!encodeFile)
		{
			return EX_USAGE;
		}
		writeFile = fopen(argv[2], "wb");
		if(!writeFile)
		{
			return EX_USAGE;
		}
	}

	char *tmpBuff = calloc(1, fileEnd+1);
	char *buffPointer = tmpBuff;


	char *payload = calloc(1, fileEnd+1);
	char *payloadPointer = payload;

	for(int count = 0; count < fileEnd ; count++)
	{
		tmpBuff[count] = fgetc(encodeFile);
	}

	int headerValues[4];
	const char *headerFields[4] = {"Version", "Sequence","From", "To" };
	int a;
	for( a = 0; a < 4; a++)
	{
		headerValues[a] = getVal(&tmpBuff, headerFields[a]);
		printf("%d\n", headerValues[a]);
	}

	//TODO: this gets you to the beginning value of your payload.
	tmpBuff = getPayload(tmpBuff, payload);

	int type = getType(payload);

	char *packetCapture = getPacket(tmpBuff, payload, fileEnd);
	char *packetPointer = packetCapture;

	printf("packetCapture %s\n", packetCapture);

	char *name = calloc(1, strlen(packetCapture) + 1);
	char *newName = name;

		a = 0;
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
	esp.name = calloc(1, strlen(name)+1);
	strncpy(esp.name, name, strlen(name));
	printf("esp.name:%s:\n", esp.name);

	memset(name, 0, strlen(name));

	int tmpNum;
	printf("cleared name: %s\n", name);
	a=0;
		packetCapture = strcasestr(packetCapture, "hp");
			while(!isdigit(*packetCapture))
			{
				packetCapture++;
			}
			while(isdigit(*packetCapture))
			{
				name[a] = *packetCapture;
				packetCapture++;
				a++;
			}
			tmpNum = strtol(name, NULL, 10);
			esp.hitPoints = tmpNum;
			printf("hitPoints%d\n", esp.hitPoints);
			a=0;
			while(!isdigit(*packetCapture))
			{
				packetCapture++;
			}
			tmpNum = strtol(packetCapture, NULL, 10);
			esp.maxPoints = tmpNum;
			printf("maxPoints%d\n", esp.maxPoints);
		printf("packetCapture: %s\n", packetCapture);

		const char *typeField[16] = {"Overmind", "Larva", "Cerebrate", "Overlord", "Queen", "Drone", "Zergling", "Lurker", "Broodling", "Hydralisk", "Guardian", "Scourge", "Ultralisk", "Mutalisk", "Defiler", "Devourer"}; 

		int z = 0;
		while( strcasestr(packetCapture, typeField[z])== NULL)
		{
			z++;

		}
		packetCapture = strcasestr(packetCapture, typeField[z]);
		for(size_t b = 0; b < strlen(typeField[z]); b++)
		{
			name[b] = *packetCapture;
			packetCapture++;
		}
		printf("name :%s\n", name);


	puts("\n");
	printf("packet: %s\n", packetCapture);
		int typeCase = type;
		switch(typeCase){
			case(0):
				
				break;
			case(1):
				break;
			case(2):
				printf("Its a Comm\n");
				break;
			case(3):
				printf("Its a gps\n");
				break;
		}
	printf("%d\n", type);

	free(newName);
	free(buf);
	free(packetPointer);
	free(payloadPointer);
	free(buffPointer);
	fclose(encodeFile);
	fclose(writeFile);
}
