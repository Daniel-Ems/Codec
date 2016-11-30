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

	tmpBuff = getPayload(tmpBuff, payload);

	int type = getType(payload);

	char *packetCapture = getPacket(tmpBuff, payload, fileEnd);
	char *packetPointer = packetCapture;

	struct FileHeader fh;
	fh.fileType = 0xa1b2c3d4;
	fh.majorVersion = 2;
	fh.minorVersion = 4;
	fh.gmtOffset = 0;
	fh.accuracyDelta = 0;
	fh.maximumLength = 0;
	fh.linkLayer = 1;

	printf("%zd", sizeof(struct FileHeader));
	fwrite(&fh, sizeof(struct FileHeader), 1, writeFile);

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


	struct EncodeZerg ez;
	ez.version = headerValues[0];
	ez.type = type;
	ez.length = 0x123456;
	ez.source = htons(headerValues[2]);
	ez.dest = htons(headerValues[3]);
	ez.id = htonl(headerValues[1]);

	fwrite(&ez,sizeof(ez),1, writeFile);
	//this is the end of your stat paylaod function
	puts("\n");
		int typeCase = type;
		switch(typeCase){
			case(0):
				
				break;
			case(1):
				StatusPayload(packetCapture, writeFile);
				printf("Error");
				break;
			case(2):
				printf("Its a Comm\n");
				break;
			case(3):
				printf("Its a gps\n");
				break;

		}

	
	free(packetPointer);
	free(payloadPointer);
	free(buffPointer);
	fclose(encodeFile);
	free(buf);
	fclose(writeFile);
}
