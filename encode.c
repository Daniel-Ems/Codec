#define _GNU_SOURCE
#include <stdio.h>
#include <sysexits.h>
#include <sys/stat.h>
#include <string.h>
#include <ctype.h>
#include "structs.h"
#include "encode_function.h"
#include "encode_structs.c"


int main (int argc, char *argv[])
{
	FILE *encodeFile;
	FILE *writeFile;

	if(argc < 3)
	{
		printf("Please provide a file to be encoded, and to be written too\n");
		return EX_USAGE;
	}
	else
	{ 
		encodeFile = fopen(argv[1], "rb");
		writeFile = fopen(argv[2], "wb");
	}

	fseek(encodeFile, 0, SEEK_END);
	size_t fileEnd= ftell(encodeFile);
	rewind(encodeFile);

	char *tmpBuff = calloc(1, fileEnd+1);
	char *buffPointer = tmpBuff;

	char *payload = calloc(1, fileEnd+1);
	char *payloadPointer = payload;

	for(size_t count = 0; count < fileEnd ; count++)
	{
		tmpBuff[count] = fgetc(encodeFile);
	}

	int headerValues[4];
	const char *headerFields[4] = {"Version", "Sequence","From", "To" };

	for(int a = 0; a < 4; a++)
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

		int typeCase = type;
		switch(typeCase){
			case(0):
				printf("Its a message\n");
				break;
			case(1):
				printf("Its a stat\n");
				break;
			case(2):
				printf("Its a Comm\n");
				break;
			case(3):
				printf("Its a gps\n");
				break;
		}
	printf("%d\n", type);

	free(packetPointer);
	free(payloadPointer);
	free(buffPointer);
	fclose(encodeFile);
	fclose(writeFile);
}
