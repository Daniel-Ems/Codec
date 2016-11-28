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

	for( int a = 0; a < 42; a ++)
	{
		tmpBuff++;
	}
	
	printf("%s\n", tmpBuff);
	char *payload;
	
	while(isalpha(tmpBuff))
	{
		*payload = *tmpBuff;
		payload++;
		tmpBuff++;
	}
	//TODO to lower function
	size_t i;
	int type;
	

	i = 0;
	if(strncmp(tmpBuff, "message",7))
	{
		type = 0;
		printf("%d\n", type);
	}
	else if(strncmp(tmpBuff, "name",4))
	{
		type = 1;
		printf("%x\n", type);
	}
	else if(strncmp(tmpBuff, "latitude",8))
	{
		type = 4;
		printf("%d\n", type);
	}
	else 
	{
		type = 3;
		printf("%d\n", type);
	}



	free(tmpBuff);
	fclose(encodeFile);
	fclose(writeFile);
}
