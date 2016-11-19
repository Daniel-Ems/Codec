#include <stdio.h>
#include <sysexits.h>

#include "structs.h"
#include "pay_functions.h"

int main(int argc, char *argv[])
{

	FILE *decodeFile;

	if(argc < 2)
	{
		printf("Please provide a file to be decoded\n");
		return EX_USAGE;
	}else{ 
		decodeFile = fopen(argv[1], "rb");
	}

	fseek(decodeFile, 0, SEEK_END);
	int lastPos = ftell(decodeFile);
	rewind(decodeFile);

	struct FileHeader fh;
	fread(&fh, sizeof(fh), 1, decodeFile);

	//size_t f_check;
	int padding;
	int nextPos;

	do{

	struct PcapHeader ph;
	fread(&ph, sizeof(ph), 1, decodeFile);

	struct EthernetFrame eh;
	fread(&eh, sizeof(eh), 1, decodeFile);

	struct Ipv4Header ip;
	fread(&ip, sizeof(ip), 1, decodeFile);

	struct UdpHeader udp;
	fread(&udp, sizeof(udp), 1, decodeFile);

	struct ZergHeader zh;
	fread(&zh, sizeof(zh), 1, decodeFile);

	int total = zh.version >> 24;
	padding = (ph.captureLength - headerLength - total);
	union PayloadStructs *zerged;

	int type = zh.version & 0x0f;

	ip.version = ip.version >> 4;

	print_zerg_header(zh);

	zerged = struct_init(total, decodeFile);

	int zerg_header = type;
		switch(zerg_header){
			case(0):
				messFunction(zerged);
				break;
			case(1):
				statFunction(zerged);
				break;
			case(2):
				commFunction(zerged);
				break;
			case(3):
				gpsFunction(zerged);
				break;
		}

	fseek(decodeFile, padding, SEEK_CUR);
	nextPos = ftell(decodeFile);

	}while(nextPos != lastPos); 

	fclose(decodeFile);
}


