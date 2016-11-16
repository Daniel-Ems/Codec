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

	 union payload *zerg;

	int type = message.version & 0x0f;
	int total = message.version >> 24;
	message.version = message.version >> 28; 

	int ipv4_ihl = contents.version  & 0x0f;
	int dscp = contents.version >> 10;
	int ecn = contents.version >> 12;
	contents.version = contents.version >> 4;

	zerg = struct_init(total, decode_file);
	int zerg_header = type;
		switch(zerg_header){
			case(0):
				messages(zerg);
				break;
			case(1):
				printf("something");
				break;
			case(2):
				printf("Command Instruction\n");
				break;
			case(3):
				printf("GPS Data\n");
				break;
			}
	//TODO: Remove debugging pruint32_t statements
	printf("File Header -> size:%zd\n", sizeof(values));
	printf("%x\n", values.file_type);
	printf("%x\n", values.major_version);
	printf("%x\n", values.minor_version);
	printf("%x\n", values.gmt_offset);
	printf("%x\n", values.accuracy_delta);
	printf("%x\n", values.maximum_length);
	printf("%x\n", values.link_layer);

	printf("Pcap packet Header, size:%zd\n", sizeof(pcap_header));
	printf("epoch %x\n",pcap_header.unix_epoch);
	printf("microseconds %x\n", pcap_header.epoch_microseconds);
	printf("capture_length %x\n", pcap_header.capture_length);
	printf("packet_length %x\n", pcap_header.packet_length);

	printf("Ethernet Frame, size:%zd\n", sizeof(frame));
	printf("destination %x\n", frame.d_mac);
	printf("Source %x\n", frame.s_mac);
	printf("type %x\n", frame.type);

	printf("Ipv4 header, size:%zd\n", sizeof(contents));
	printf("version %x\n", contents.version);
	printf("ihl %d\n", ipv4_ihl);
	printf("dscp %x\n", dscp);
	printf("ecn %x\n", ecn);
	printf("total_length %x\n", contents.total_length);
	printf("id %x\n", contents.id);
	//printf("flags %x\n", contents.flags);
	printf("offset %x\n", contents.offset);
	printf("ttl %x\n", contents.ttl);
	printf("protocol %x\n", contents.protocol);
	printf("checksum %x\n", contents.checksum);
	printf("s_ip %x\n", contents.s_ip);
	printf("d_ip %x\n", contents.d_ip);

	printf("UDP Header, size:%zd\n", sizeof(udp));
	printf("s_port %x\n", udp.s_port);
	printf("d_port %x\n", udp.d_port);
	printf("length %d\n", ntohs(udp.length));
	printf("checksum %x\n", udp.checksum);



	//int version = message.type;
	printf("zerg header, size:%zd\n", sizeof(message));
	printf("Version %x\n", message.version);
	printf("type %d\n", type);
	printf("total %d\n", total);
	printf("source %x\n", message.source);
	printf("destination %x\n", message.dest);
	printf("id %x\n", ntohs(message.id));
	//printf("payload %s\n", zerg -> zerg.name);
	//printf("version %d\n", version);

	free(zerg);
	fclose(decode_file);
}


	//1) Add the ability to take two arguments (1."Encode" 2."Decode")
	//2) "Decode" will have one additional argument, a file to be 		//    decoded.
	//3) "Encode" Will have two additional arguments, a file to be 
	//    encoded, and a file to store the encoded file in.
	//4) Open a the first argument for reading. 
	//5) Identify the file contains pcaps (strstr for d4 c3 b2 a1)
	/* 
	Decoding guidelines, find a way to make it to the zerg 				packet. 
	-> 1st -> 4bits containing the version
			Version -> only uses version 1.
	-> 2nd -> 4bits containing the type
			Type -> defines the type of payload
					0) Message
					1) Status of Zerg
					3) Command Instruction
					4) GPS Data
	-> 3rd -> 3bytes containing the total length
			Total length -> length of the packet in bytes including
							fized header
	-> 4th -> 2bytes containing the Destination Zerg ID
	-> 5th -> 2bytes containing the source zerg ID
	-> 6th -> 4bytes containing the sequence ID
			Sequence ID -> a increment in number of packets passed
							between the same source and destination
	-> 7th -> from the 12byte on is the Message Payload
		Payload's
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


