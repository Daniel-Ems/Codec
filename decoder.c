#include <stdio.h>
#include <sysexits.h>

#include "structs.h"
#include "structs.c"

int main(int argc, char *argv[])
{

	FILE *decode_file;
	//char *message_payload;

	if(argc < 2)
	{
		printf("Please provide a file to be decoded\n");
		return EX_USAGE;
	}else{ 
		decode_file = fopen(argv[1], "rb");
	}

	struct pcap_file_header values;
	fread(&values, sizeof(values), 1, decode_file);

	struct pcap_packet_header pcap_header;
	fread(&pcap_header, sizeof(pcap_header), 1, decode_file);

	struct ethernet_header frame;
	fread(&frame, sizeof(frame), 1, decode_file);

	struct ipv4_header contents;
	fread(&contents, sizeof(contents), 1, decode_file);

	struct udp_header udp;
	fread(&udp, sizeof(udp), 1, decode_file);

	struct zerg_header message;
	fread(&message, sizeof(message), 1, decode_file);

	 union payload *zerged;


	//TODO: Clean bit shifts and &'s perhaps put in a function
	int type = message.version & 0x0f;
	int total = message.version >> 24;

	contents.version = contents.version >> 4;

	print_zerg_header(message);
	zerged = struct_init(total, decode_file);
	int zerg_header = type;
		switch(zerg_header){
			case(0):
				messages(zerged);
				break;
			case(1):
				stat_payload(zerged);
				break;
			case(2):
				com_payload(zerged);
				break;
			case(3):
				printf("GPS Data\n");
				break;
			}


	//TODO: debugging print statments for output
	printf("type %x\n", type);
	printf("total %d\n", total);

	
	fclose(decode_file);
}


	//1) Add the ability to take two arguments (1."Encode" 2."Decode")
	//2) "Decode" will have one additional argument, a file to be 		//    decoded.
	//3) "Encode" Will have two additional arguments, a file to be 
	//    encoded, and a file to store the encoded file in.
	//4) Open a the first argument for reading. 
	//5) Identify the file contains pcaps (strstr for d4 c3 b2 a1)
	/* 
		0) Message -> just a message starting at the 12th byte
		1) Status Payload -> 3bytes of Hit pouint32_ts
						  -> 1byte of Armor
						  -> 3bytes of Max hit pouint32_ts 
						  -> 1byte of type
						  -> 4bytes of speed
						  -> the remainder is the name
		2) Command Payload -> 2bytes of command 
						   -> 2bytes of parameter 1
						   -> the reaminder is paramter 2
		3) GPS Data Payload -> 4bytes Longitude
							-> 4bytes Latitude
							-> Altitude
							-> Bearing
							-> Speed
							-> Accuracy
	*/


