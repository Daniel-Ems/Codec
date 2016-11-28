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
			type = 4;
		}
		else 
		{
			type = 3;
		}
		return type;
	}

char *getPayload(char *tmpBuff,char *payload)
	{	
		int a = 0;
		while(!isalpha(*tmpBuff))
		{
			tmpBuff++;
		}
		while(isalpha(*tmpBuff))
		{
			payload[a] = *tmpBuff;
			a++;
			tmpBuff++;
		}
		while(!isalnum(*tmpBuff))
		{
			tmpBuff++;
		}
		return tmpBuff;
	}
