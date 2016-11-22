#include <stdio.h>
#include <sysexits.h>
#include <sys/stat.h>
#include <string.h>
#include <ctype.h>
#include "structs.h"

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

//This handles the first four lines of the file
//TODO: put in a four loop and clean
	char tmpBuff [64];
	for(size_t count = 0; count < 4; count++)
	{
		fgets(tmpBuff, sizeof(tmpBuff), encodeFile);
		strtok(tmpBuff, " ");
		char *token = strtok(NULL, "\n");
		printf("%d\n", *token);
	}


	struct FileHeader fh;
	fh.fileType = 0xa1b2c3d4; 
	fh.majorVersion = 0x0002;
	fh.minorVersion = 0x0004;
	fh.gmtOffset = 0x00000000;
	fh.accuracyDelta = 0x00000000;
	fh.maximumLength = 0x00000000;
	fh.linkLayer = 0x00000001;

	fwrite(&fh, sizeof(fh), 1, writeFile);

	struct PcapHeader ph;
	ph.unixEpoch = 0x00000000;
	ph.epochMicroseconds = 0x00000000;
	ph.captureLength = 0x11111111;
	ph.packetLength = 0x00000000;

	fwrite(&ph, sizeof(ph), 1, writeFile);

	struct EthernetFrame ef;
	ef.d_mac = 0x000000000000;
	ef.s_mac = 0x111111111111;
	ef.type = 0x0008;

	fwrite(&ef, sizeof(ef), 1, writeFile);






















	fgets(tmpBuff, sizeof(tmpBuff), encodeFile);
	strtok(tmpBuff, ":");

	//TODO to lower function
	size_t i;
	int type;
	for( i = 0; i < strlen(tmpBuff); i++)
 	{
		tmpBuff[i]=tolower(tmpBuff[i]);
	}

	i = 0;
	if(strcmp(tmpBuff, "message")==0)
	{
		type = 0;
		printf("%d\n", type);
	}
	else if(strcmp(tmpBuff, "name") ==0)
	{
		type = 1;
		printf("%x\n", type);
	}
	else if(strncmp(tmpBuff, "get",3) == 0)
	{
		type = 3;
		printf("%d\n", type);
	}
	else if(strcmp(tmpBuff, "latitude") == 0)
	{
		type = 4;
		printf("%d\n", type);
	}
}


