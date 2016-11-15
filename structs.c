#include "structs.h"

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


