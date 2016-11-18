#ifndef SORT_H
#define SORT_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <arpa/inet.h>

enum{zerg_header_length = 12};
enum{header_length = 14+20+8};
	struct pcap_file_header{ 
		uint32_t file_type;
		uint32_t major_version : 16;
		uint32_t minor_version : 16;
		uint32_t gmt_offset;
		uint32_t accuracy_delta;
		uint32_t maximum_length;
		uint32_t link_layer;
	};

	struct pcap_packet_header{
		uint32_t unix_epoch; 
		uint32_t epoch_microseconds;
		uint32_t capture_length;
		uint32_t packet_length;
	};

	struct ethernet_header{
		char d_mac[6];
		char s_mac[6];
		uint16_t type;
	};

	struct ipv4_header{
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

	struct udp_header{
		uint32_t s_port : 16;
		uint32_t d_port : 16;
		uint32_t length : 16;
		uint32_t checksum : 16;
	};

	struct zerg_header{
		uint32_t version;
		uint32_t source : 16;
		uint32_t dest : 16;
		uint32_t id;
	};

	struct status_payload{
			uint32_t hit_armor;
			uint32_t max_type;
			uint32_t speed;
			char name[1];
		};

	struct message{
			char message[1];
	};

	struct command_payload{
		uint32_t command : 16;
		uint32_t parameter_one : 16;
		uint32_t parameter_two;
	};

	struct gps_data{
		uint32_t long_first;
		uint32_t long_second;
		uint32_t lat_first;
		uint32_t lat_second;
		uint32_t altitude;
		uint32_t bearing;
		uint32_t speed;
		uint32_t accuracy;
	};

	union payload {
		struct status_payload status;
		struct message name;
		struct command_payload command;
		struct gps_data gps;
	};

const char *race(uint32_t type);
double doub_converter(uint64_t *number);
uint64_t doub_flip(uint32_t *lat_long, uint32_t *long_lat);
void print_zerg_header(struct zerg_header header);
float converter(uint32_t *thing);
void com_payload(union payload *zerg);
void stat_payload(union payload *zerg);
void messages(union payload *zerg);
char *decode_message(int total, FILE *decode_file);
union payload *memory(int total,FILE *decode_file);
 
#endif

