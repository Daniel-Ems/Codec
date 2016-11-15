#include <stdio.h>
#include <sysexits.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
int main(int argc, char *argv[])
{
	const char *packet_id;
	FILE *decode_file;

	//TODO: Make this as a typdef and move to a header file
	struct pcap_file_header{ 
		unsigned int file_type;
		unsigned int major_version : 16 ;
		unsigned int minor_version : 16;
		unsigned int gmt_offset;
		unsigned int accuracy_delta;
		unsigned int maximum_length;
		unsigned int link_layer;
	};

	struct pcap_packet_header{
		unsigned int unix_epoch; 
		unsigned int epoch_microseconds;
		unsigned int capture_length;
		unsigned int packet_length;
	};

	struct ethernet_header{
		char d_mac[6] ;
		char s_mac[6] ;
		uint2_t type;
	};

	struct ipv4_header{
		unsigned int version : 4;
		unsigned int ihl : 4;
		unsigned int dscp : 8;
		unsigned int total_length : 16;
		unsigned int id : 16;
		unsigned int flags : 4;
		unsigned int offset : 12;
		unsigned int ttl : 8;
		unsigned int protocol : 8;
		unsigned int checksum : 16;
		unsigned int s_ip;
		unsigned int d_ip;
	};

	struct udp_header{
		unsigned int s_port : 16;
		unsigned int d_port : 16;
		unsigned int length : 16;
		unsigned int checksum : 16;
	};

	struct zerg_header{
		unsigned int version : 4 ;
		unsigned int type : 4;
		unsigned int total : 24;
		unsigned int source : 16;
		unsigned int dest : 16;
		unsigned int id;
		char payload[32];
	};
 
	if(argc < 1)
	{
		printf("Please provide a file to be decoded\n");
		return EX_USAGE;
	}else{ 
		decode_file = fopen(argv[1], "rb");
	}

	struct pcap_file_header values;
	fread(&values, sizeof(values), 1, decode_file);

	//TODO: Remove debugging prunsigned int statements
	printf("File Header -> size:%zd\n", sizeof(values));
	printf("%x\n", values.file_type);
	printf("%x\n", values.major_version);
	printf("%x\n", values.minor_version);
	printf("%x\n", values.gmt_offset);
	printf("%x\n", values.accuracy_delta);
	printf("%x\n", values.maximum_length);
	printf("%x\n", values.link_layer);

	struct pcap_packet_header pcap_header;
	fread(&pcap_header, sizeof(pcap_header), 1, decode_file);

	printf("Pcap packet Header, size:%zd\n", sizeof(pcap_header));
	printf("epoch %x\n",pcap_header.unix_epoch);
	printf("microseconds %x\n", pcap_header.epoch_microseconds);
	printf("capture_length %x\n", pcap_header.capture_length);
	printf("packet_length %x\n", pcap_header.packet_length);

	struct ethernet_header frame;
	fread(&frame, sizeof(frame), 1, decode_file);

	printf("Ethernet Frame, size:%zd\n", sizeof(frame));
	printf("destination %x\n", frame.d_mac);
	printf("Source %s\n", frame.s_mac);
	printf("type %x\n", frame.type);



	struct ipv4_header contents;
	fread(&contents, sizeof(contents), 1, decode_file);

	printf("Ipv4 header, size:%zd\n", sizeof(contents));
	printf("version %x\n", contents.version);
	printf("ihl %x\n", contents.ihl);
	printf("dscp %x\n", contents.dscp);
	//printf("ecn %x\n", contents.ecn);
	printf("total_length %x\n", contents.total_length);
	printf("id %x\n", contents.id);
	printf("flags %x\n", contents.flags);
	printf("offset %x\n", contents.offset);
	printf("ttl %x\n", contents.ttl);
	printf("protocol %x\n", contents.protocol);
	printf("checksum %x\n", contents.checksum);
	printf("s_ip %x\n", contents.s_ip);
	printf("d_ip %x\n", contents.d_ip);

	struct udp_header udp;
	fread(&udp, sizeof(udp), 1, decode_file);

	printf("UDP Header, size:%zd\n", sizeof(udp));
	printf("s_port %x\n", udp.s_port);
	printf("d_port %x\n", udp.d_port);
	printf("length %x\n", udp.length);
	printf("checksum %x\n", udp.checksum);

	struct zerg_header message;
	fread(&message, sizeof(message), 1, decode_file);

	printf("zerg header, size:%zd\n", sizeof(message));
	printf("Version %x\n", message.version);
	printf("type %x\n", message.type);
	printf("total %x\n", message.total);
	printf("source %x\n", message.source);
	printf("destination %x\n", message.dest);
	printf("id %x\n", message.id);
	printf("payload %s\n", message.payload);

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
		1) Status Payload -> 3bytes of Hit pounsigned ints
						  -> 1byte of Armor
						  -> 3bytes of Max hit pounsigned ints 
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


