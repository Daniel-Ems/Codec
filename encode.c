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



	for(int count = 0; count < fileEnd ; count++)
	{
		tmpBuff[count] = fgetc(encodeFile);
	}
	fileHeader(writeFile);

while(tmpBuff)
{

	char *payload = calloc(1, fileEnd+1);
	char *payloadPointer = payload;

	int headerValues[4];
	const char *headerFields[4] = {"Version", "Sequence","From", "To" };
	int a;
	for( a = 0; a < 4; a++)
	{
		headerValues[a] = getVal(&tmpBuff, headerFields[a]);
	}

	char *packetCapture = getPacket(tmpBuff, payload, fileEnd);
	char *packetPointer = packetCapture;

	int type = getType(packetCapture);
	getPayload(&packetCapture,type);

	printf("TMpBuff %s\n", tmpBuff);
	printf("packetCapture:%s\n", packetCapture);

	a = 0;


	struct EncodeZerg *ez = malloc(sizeof (*ez));
	ez -> version = (headerValues[0]);
	ez -> type  = (type);
	ez -> source = htons(headerValues[2]);
	ez -> dest = htons(headerValues[3]);
	ez -> id = htonl(headerValues[1]);

	printf("packetCapture%s\n", packetCapture);
	puts("\n");
		int typeCase = type;
		switch(typeCase){
			case(0):
				MessagePayload(packetCapture, writeFile, ez);
				break;
			case(1):
				StatusPayload(packetCapture, writeFile,ez);
				break;
			case(2):
				CommandPayload(packetCapture, writeFile,ez);
				break;
			case(3):
				GpsPayload(packetCapture, writeFile, ez);
				break;

		}
	free(packetPointer);
	free(payloadPointer);
	free(ez);
	tmpBuff = strcasestr(tmpBuff, "Version");
}

	free(buffPointer);
	free(buf);
	fclose(encodeFile);
	fclose(writeFile);
}
