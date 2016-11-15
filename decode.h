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
 
	
	struct pcap_file_header values;
	fread(&values, sizeof(values), 1, decode_file);

	//TODO: Remove debugging pruint32_t statements
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
	printf("Source %x\n", frame.s_mac);
	printf("type %x\n", frame.type);



	struct ipv4_header contents;
	fread(&contents, sizeof(contents), 1, decode_file);

	printf("Ipv4 header, size:%zd\n", sizeof(contents));
	printf("version %x\n", contents.version);
	//printf("ihl %x\n", contents.ihl);
	printf("dscp %x\n", contents.dscp);
	//printf("ecn %x\n", contents.ecn);
	printf("total_length %x\n", contents.total_length);
	printf("id %x\n", contents.id);
	//printf("flags %x\n", contents.flags);
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
	printf("length %d\n", ntohs(udp.length));
	printf("checksum %x\n", udp.checksum);

	struct zerg_header message;
	fread(&message, sizeof(message), 1, decode_file);

	int type = message.version & 0x0f;
	int total = message.version >> 24;
	message.version = message.version >> 28; 
	//int version = message.type;
	printf("zerg header, size:%zd\n", sizeof(message));
	printf("Version %x\n", message.version);
	printf("type %d\n", type);
	printf("total %d\n", total);
	printf("source %x\n", message.source);
	printf("destination %x\n", message.dest);
	printf("id %x\n", ntohs(message.id));
	printf("payload %s\n", message.payload);
	//printf("version %d\n", version);
