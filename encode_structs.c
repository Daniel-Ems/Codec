
//#include "structs.h"
/*
struct FileHeader fh;
	fh.fileType = 0xa1b2c3d4;
	fh.majorVersion = 2;
	fh.minorVersion = 4;
	fh.gmtOffset = 0;
	fh.accuracyDelta = 0;
	fh.maximumLength = 0;
	fh.linkLayer = 1;

	printf("%zd", sizeof(struct FileHeader));
	fwrite(&fh, sizeof(struct FileHeader), 1, writeFile);

	struct PcapHeader ph;
	ph.unixEpoch = 0x00000000;
	ph.epochMicroseconds = 0x00000000;
	ph.captureLength = 0x11111111; //not good
	ph.packetLength = 0x00000000;

	fwrite(&ph, sizeof(ph), 1, writeFile);

	struct EthernetFrame ef;
	ef.d_mac = 0x000000000000;
	ef.s_mac = 0x111111111111;
	ef.type = 0x0008; 

	fwrite(&ef, sizeof(ef), 1, writeFile);

	struct Ipv4Header ih;
	ih.version = 0x45; 
	ih.total_length = 0x1234; //not good
	ih.id = 0x00000000;
	ih.offset = 0x000016;
	ih.ttl = 0x0011;
	ih.protocol = 0x11; //not good
	ih.checksum = 0x1234;
	ih.s_ip = 0x87654321;
	ih.d_ip = 0x12345678;

	fwrite(&ih, sizeof(ih), 1, writeFile);

	struct UdpHeader uh;
	uh.s_port = 0x1111;
	uh.d_port = 0x2222; //not good
	uh.length = 0x3333; //not good
	uh.checksum = 0x4444;

	fwrite(&uh, sizeof(uh), 1, writeFile);
*/
	
/*
	struct ZergHeader zh;
	zh.version = values[0];
	zh.type = type;
	zh.length = 0x123456;
	zh.source = htons(values[2]);
	zh.dest = htons(values[3]);
	zh.id = htonl(values[1]);

	fwrite(&zh,sizeof(zh),1, writeFile);

*/
