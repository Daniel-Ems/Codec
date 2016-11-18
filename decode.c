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

	fseek(decode_file, 0, SEEK_END);
	int last_pos = ftell(decode_file);
	rewind(decode_file);

	struct pcap_file_header values;

	fread(&values, sizeof(values), 1, decode_file);

	//size_t f_check;
	int end_of_capture;
	int new_pos;

	do{

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
	

	int total = message.version >> 24;
	end_of_capture = (pcap_header.capture_length - header_length - total);
	 union payload *zerged;

	int type = message.version & 0x0f;

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
				gps(zerged);
				break;
		}

	fseek(decode_file, end_of_capture, SEEK_CUR);
	new_pos = ftell(decode_file);

	}while(new_pos != last_pos); 

	fclose(decode_file);
}


