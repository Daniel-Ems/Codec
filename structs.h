#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <arpa/inet.h>
#define _GNU_SOURCE
#include <stdio.h>
#include <sysexits.h>
#include <sys/stat.h>
#include <string.h>
#include <ctype.h>




enum{zerg_header_length = 12};

enum{etherIpUdp = 14+20+8};


	struct FileHeader{ 

		uint32_t fileType;
		uint32_t majorVersion : 16;
		uint32_t minorVersion : 16;
		uint32_t gmtOffset;
		uint32_t accuracyDelta;
		uint32_t maximumLength;
		uint32_t linkLayer;
	};

	struct PcapHeader{
		uint32_t unixEpoch; 
		uint32_t epochMicroseconds;
		uint32_t captureLength;
		uint32_t packetLength;
	};

	
	struct __attribute__((packed)) EthernetFrame{
		uint64_t d_mac : 48;
		uint64_t s_mac : 48;
		uint32_t type : 16;
	};

	struct __attribute__((packed)) Ipv4Header{
		uint32_t version : 16;
		uint32_t total_length : 16;
		uint32_t id : 16;
		uint32_t offset : 16;
		uint32_t ttl : 8;
		uint32_t protocol : 8;
		uint32_t checksum : 16;
		uint32_t s_ip;
		uint32_t d_ip;
	};

	struct UdpHeader{
		uint32_t s_port : 16;
		uint32_t d_port : 16;
		uint32_t length : 16;
		uint32_t checksum : 16;
	};

	struct __attribute__((packed)) ZergHeader{
		uint32_t version;
		uint32_t source : 16;
		uint32_t dest : 16;
		uint32_t id;
	};

	struct __attribute__((packed)) EncodeZerg{
		uint32_t version : 4;
		uint32_t type : 4 ;
		uint32_t length : 24;
		uint32_t source : 16;
		uint32_t dest : 16;
		uint32_t id;
	};

	struct StatusPacket{
			uint32_t hit_armor;
			uint32_t max_type;
			uint32_t speed;
			char name[1];
		};

	struct __attribute__((packed)) EncodeStatusPacket{
		uint32_t hitPoints : 24;
		uint32_t armor : 8;
		uint32_t maxPoints : 24;
		uint32_t type : 8;
		uint32_t speed ;
	};

	struct MessagePacket{
			char message[1];
	};

	struct CommandPacket{
		uint32_t command : 16;
		uint32_t parameter_one : 16;
		uint32_t parameter_two;
	};

	struct GpsPacket{
		uint32_t long_first;
		uint32_t long_second;
		uint32_t lat_first;
		uint32_t lat_second;
		uint32_t altitude;
		uint32_t bearing;
		uint32_t speed;
		uint32_t accuracy;
	};

	union PayloadStructs {
		struct StatusPacket stat;
		struct MessagePacket mess;
		struct CommandPacket comm;
		struct GpsPacket gps;
	};

union PayloadStructs *struct_init(int total,FILE *decode_file);
double doub_converter(uint64_t *number);
uint64_t doub_flip(uint32_t *lat_long, uint32_t *long_lat);
void print_zerg_header(struct ZergHeader zerg);
float converter(uint32_t *thing);
const char *raceId(uint32_t type);
char *decode_message(int total, FILE *decode_file);
 
#endif

