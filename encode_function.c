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
		return ver;
	}

int getType(char *payload)
	{
		int type;
		if(strncmp(payload, "message",7)==0)
		{
			type = 0;
		}
		else if(strncmp(payload, "name",4)==0)
		{
			type = 1;
		}
		else if(strncmp(payload, "latitude",8)==0)
		{
			type = 3;
		}
		else 
		{
			type = 2;
		}
		return type;
	}

char *getPayload(char *tmpBuff,char *payload)
	{	

		while(!isalpha(*tmpBuff))
		{
			tmpBuff++;
		}
		while(isalpha(*tmpBuff))
		{
			*payload = *tmpBuff;
			payload++;
			tmpBuff++;
		}
		
		while(!isalnum(*tmpBuff))
		{
			*payload = *tmpBuff;
			payload++;
			tmpBuff++;
		}
		
		return tmpBuff;
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

