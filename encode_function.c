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
