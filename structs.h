#ifndef SORT_H
#define SORT_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <arpa/inet.h>


	//TODO: Make this as a typdef and move to a header file
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
		uint32_t version : 8;
		//uint32_t ihl : 4;
		uint32_t dscp : 8;
		uint32_t total_length : 16;
		uint32_t id : 16;
		//uint32_t flags : 4;
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
		//uint32_t type : 4;
		//uint32_t total : 24;
		uint32_t source : 16;
		uint32_t dest : 16;
		uint32_t id;
		char payload[64];
	};
 
#endif