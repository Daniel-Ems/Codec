#include <stdio.h>
#include <sysexits.h>
#include <string.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
	const char *packet_id;
	FILE *decode_file;

	//TODO: Make this as a typdef and move to a header file
	struct pcap_file_header{ 
		int file_type;
		int major_version : 16 ;
		int minor_version : 16;
		int gmt_offset;
		int accuracy_delta;
		int maximum_length;
		int link_layer;
	};

	struct pcap_packet_header{
		int unix_epoch; 
		int epoch_microseconds;
		int capture_length;
		int packet_length;
	};

	struct ethernet_header{
		long unsigned int d_mac : 48;
		long unsigned int s_mac : 48;
		int type : 16;
	};

	struct ipv4_header{
		int version : 4;
		int ihl : 4;
		int dscp : 12;
		int ecn : 4;
		int total_length : 16;
		int id : 16;
		int flags : 4;
		int offset : 12;
		int ttl : 8;
		int protocol : 8;
		int checksum : 16;
		int s_ip;
		int d_ip;
	};

	struct udp_header{
		int s_port : 16;
		int d_port : 16;
		int length : 16;
		int checksum : 16;
	};

	struct zerg_header{
		int version : 4 ;
		int type : 4;
		int total : 32;
		int source : 16;
		int dest : 16;
		int id;
		char payload[64];
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

	//TODO: Remove debugging print statements
	printf("%x\n", values.file_type);
	printf("%x\n", values.major_version);
	printf("%x\n", values.minor_version);
	printf("%x\n", values.gmt_offset);
	printf("%x\n", values.accuracy_delta);
	printf("%x\n", values.maximum_length);
	printf("%x\n", values.link_layer);

	struct pcap_packet_header pcap_header;
	fread(&pcap_header, sizeof(pcap_header), 1, decode_file);

	printf("epoch %x\n",pcap_header.unix_epoch);
	printf("microseconds %x\n", pcap_header.epoch_microseconds);
	printf("capture_length %x\n", pcap_header.capture_length);
	printf("packet_length %x\n", pcap_header.packet_length);

	struct ethernet_header frame;
	fread(&frame, sizeof(frame), 1, decode_file);

	printf("destination %ld\n", frame.d_mac);
	printf("Source %ld\n", frame.s_mac);
	printf("type %x\n", frame.type);



	struct ipv4_header contents;
	fread(&contents, sizeof(contents), 1, decode_file);

	printf("version %x\n", contents.version);
	printf("ihl %x\n", contents.ihl);
	printf("dscp %x\n", contents.dscp);
	printf("ecn %x\n", contents.ecn);
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

	printf("s_port %x\n", udp.s_port);
	printf("d_port %x\n", udp.d_port);
	printf("length %x\n", udp.length);
	printf("checksum %x\n", udp.checksum);

	struct zerg_header message;
	fread(&message, sizeof(message), 1, decode_file);

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
		1) Status Payload -> 3bytes of Hit points
						  -> 1byte of Armor
						  -> 3bytes of Max hit points 
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


