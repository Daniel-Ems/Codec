#define _GNU_SOURCE
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

	fseek(encodeFile, 0, SEEK_END);
	int fileEnd= ftell(encodeFile);
	rewind(encodeFile);

	//This mallocs for a tmpbuff and a permanent buff
	char *tmpBuff = calloc(1, fileEnd);
	char *values = calloc(1, fileEnd);
	char *tmpPoint = values;

	for(int count = 0; count < fileEnd ; count++)
	{
		tmpBuff[count] = fgetc(encodeFile);
	}

	//TODO: Turn into function in order to use as a get value ,fms
	char *Version = strcasestr(tmpBuff, "Version");

	printf("%s\n", Version);

	while(!isdigit(*Version))
	{
		Version++;
	}
	while(isdigit(*Version))
	{
		*values = *Version;
		values++;
		Version++;
	}
	values--;
	int ver = strtol(values, NULL, 10);
	printf("%d\n", ver);


	char *version = strcasestr(Version, "Version");
	if (!version)
	{
		printf("There is only one capture\n");
		
	}
	else
	{

		printf("second strstr, %s\n", version);
		while(!isdigit(*version))
		{
			version++;
		}
		while(isdigit(*version))
		{
			values++;
			*values = *version;
			values++;
			version++;
		}
	}
	values --;
	int ver2 = strtol(values, NULL, 10);
	printf("%d\n", ver2);

	struct FileHeader fh;
	fh.fileType = 0xa1b2c3d4;
	fh.minorVersion = 0x0004;
	fh.gmtOffset = 0x00000000;
	fh.accuracyDelta = 0x00000000;
	fh.maximumLength = 0x00000000;
	fh.linkLayer = 0x00000001;

	fwrite(&fh, sizeof(fh), 1, writeFile);

	struct PcapHeader ph;
	ph.unixEpoch = 0x00000000;
	ph.epochMicroseconds = 0x00000000;
	ph.captureLength = 0x11111111; //not good
	ph.packetLength = 0x00000000;

	fwrite(&ph, sizeof(ph), 1, writeFile);

	struct EthernetFrame ef;
	ef.d_mac = 0x000000000000;
	ef.s_mac = 0x111111111111;
	ef.type = 0x0008; 

	fwrite(&ef, sizeof(ef), 1, writeFile);

	struct Ipv4Header ih;
	ih.version = 0x45; 
	ih.total_length = 0x1234; //not good
	ih.id = 0x00000000;
	ih.offset = 0x000016;
	ih.ttl = 0x0011;
	ih.protocol = 0x11; //not good
	ih.checksum = 0x1234;
	ih.s_ip = 0x87654321;
	ih.d_ip = 0x12345678;

	fwrite(&ih, sizeof(ih), 1, writeFile);

	struct UdpHeader uh;
	uh.s_port = 0x1111;
	uh.d_port = 0x2222; //not good
	uh.length = 0x3333; //not good
	uh.checksum = 0x4444;

	fwrite(&uh, sizeof(uh), 1, writeFile);

/*
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
*/
/*
	struct ZergHeader zh;
	zh.version = values[0];
	zh.type = type;
	zh.length = 0x123456;
	zh.source = htons(values[2]);
	zh.dest = htons(values[3]);
	zh.id = htonl(values[1]);
*/
	//fwrite(&zh,sizeof(zh),1, writeFile);
	values--;
	free(tmpPoint);
	free(tmpBuff);
}
