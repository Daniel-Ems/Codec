#include "encode_function.h"


int getVal(char **tmpBuff, const char *search)
	{
		int ver;

		*tmpBuff = strcasestr(*tmpBuff, search);
		while(!isdigit(**tmpBuff))
		{
			(*tmpBuff)++;

		}
		ver = strtol(*tmpBuff,NULL, 10);
		while(isdigit(**tmpBuff))
		{
			(*tmpBuff)++;
		}
		return ver;
	}

int getType(char *packetCapture)
	{
		int type;
		if(strcasestr(packetCapture, "message"))
		{
			type = 0;
		}
		else if(strcasestr(packetCapture, "name"))
		{
			type = 1;
		}
		else if(strcasestr(packetCapture, "latitude"))
		{
			type = 3;
		}
		else 
		{
			type = 2;
		}
		return type;
	}

void getPayload(char **packetCapture, int type)
	{
		if(type == 2)
		{
			while(!isalpha(**packetCapture))
			{
				(*packetCapture)++;
			}
		}
		else
		{
			while(!isalpha(**packetCapture))
			{
				(*packetCapture)++;
			}
			while(isalpha(**packetCapture))
			{
				(*packetCapture)++;
			}
			while(!isalnum(**packetCapture))
			{
				(*packetCapture)++;
			}
		}
	}

char *getPacket(char *tmpBuff, char *payload, off_t fileEnd)
	{
		char *tmpCapture = calloc(1, fileEnd + 1);
		int a;
		if((payload = strcasestr(tmpBuff, "Version")))
		{
			int remainder = payload - tmpBuff;

			for(a = 0; a < remainder; a++)
			{
				tmpCapture[a] = *tmpBuff;
				tmpBuff++;
			}
		}
		else
		{
			memcpy(tmpCapture, tmpBuff, strlen(tmpBuff));
		}
		return tmpCapture;
	}

void notdigit(char **packetCapture)
	{
	while(!isdigit(**packetCapture))
		{
			(*packetCapture)++;
		}
	}

uint32_t convertInt(float tmpNum)
	{
		union converter{
			float speed;
			uint32_t test;
	};

	union converter speed_test; 
	speed_test.speed =tmpNum;
	uint32_t maxSpeed = htonl(speed_test.test);
	return maxSpeed;
	}

FILE *fileHeader(FILE *writeFile)
	{
		struct FileHeader fh;
		fh.fileType = 0xa1b2c3d4;
		fh.majorVersion = 2;
		fh.minorVersion = 4;
		fh.gmtOffset = 0;
		fh.accuracyDelta = 0;
		fh.maximumLength = 0;
		fh.linkLayer = 1;

		fwrite(&fh, sizeof(struct FileHeader), 1, writeFile);
		return writeFile;
	}

FILE *ethernetHeader(FILE *writeFile)
	{
		struct EthernetFrame ef;
		ef.d_mac = 0x000000000000;
		ef.s_mac = 0x111111111111;
		ef.type = 0x0008; 

		fwrite(&ef, sizeof(ef), 1, writeFile);
		return writeFile;
	}

