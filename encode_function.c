#include "encode_function.h"


int getVal(char *tmpBuff, const char *search)
	{
		int ver;

		tmpBuff = strcasestr(tmpBuff, search);
		while(!isdigit(*tmpBuff))
		{
			tmpBuff++;

		}
		ver = strtol(tmpBuff,NULL, 10);
		return ver;
	}

int getType(char *payload)
	{
		int type;
		if(strncmp(payload, "message",7)==0)
		{
			type = 0;
			printf("%d\n", type);
		}
		else if(strncmp(payload, "name",4)==0)
		{
			type = 1;
			printf("%x\n", type);
		}
		else if(strncmp(payload, "latitude",8)==0)
		{
			type = 4;
			printf("%d\n", type);
		}
		else 
		{
			type = 3;
			printf("%d\n", type);
		}
		return type;
	}

