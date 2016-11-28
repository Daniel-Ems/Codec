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
	char *payload = calloc(1, fileEnd+1);
	char *tmpPayload = payload;
	char *tmpPointer = tmpBuff;
	printf("%p\n", tmpBuff);
	for(size_t count = 0; count < fileEnd ; count++)
	{
		tmpBuff[count] = fgetc(encodeFile);
	}

	int headerValues[4];
	const char *headerFields[4] = {"Version", "Sequence","To", "From"};

	for(int a = 0; a < 4; a++)
	{
		headerValues[a] = getVal(tmpBuff, headerFields[a]);
		printf("%d\n", headerValues[a]);
	}

	for( int a = 0; a < 43; a++)
	{
		tmpBuff++;
	}
	
	printf("%s\n", tmpBuff);
	int a = 0;

	while(isalpha(*tmpBuff))
	{
		payload[a] = *tmpBuff;
		a++;
		tmpBuff++;
	}
	while(!isalnum(*tmpBuff))
	{
		tmpBuff++;
	}
	printf("%s\n", tmpBuff);
	//TODO to lower function

	int type;

	if(strncmp(payload, "message",7)==0)
	{
		type = 0;
		printf("%d\n", type);
	}
	else if(strncmp(payload, "name",4)==0)
	{
		type = 1;
		printf("%x\n", type);
	}
	else if(strncmp(payload, "latitude",8)==0)
	{
		type = 4;
		printf("%d\n", type);
	}
	else 
	{
		type = 3;
		printf("%d\n", type);
	}


	free(tmpPayload);
	free(tmpPointer);
	fclose(encodeFile);
	fclose(writeFile);
}
