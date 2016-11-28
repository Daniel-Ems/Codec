#include "encode_function.h"


int getVal(char *tmpBuff, const char *search)
	{
		int ver;
		//char *values = NULL;
		tmpBuff = strcasestr(tmpBuff, search);
		while(!isdigit(*tmpBuff))
		{
			tmpBuff++;
		}
/*
		while(isdigit(*tmpBuff))
		{
			values =  tmpBuff;
			values++;
			tmpBuff++;
		}

		values--;
*/
		ver = strtol(tmpBuff, NULL, 10);
		return ver;
	}
