#include <stdio.h>
#include <sysexits.h>
#include <sys/stat.h>
#include <string.h>
#include <ctype.h>

int main (int argc, char *argv[])
{
	FILE *encodeFile;

	if(argc < 2)
	{
		printf("Please provide a file to be encoded\n");
		return EX_USAGE;
	}else{ 
		encodeFile = fopen(argv[1], "rb");
	}

	char tmpBuff [64];
	char values[64] = "\0";
	size_t i;
	size_t a = 0;
	for(size_t count = 0; count < 4; count++)
	{
		fgets(tmpBuff, sizeof(tmpBuff), encodeFile);
		for (i = 0; i < strlen(tmpBuff); i++)
		{
			if(isdigit(tmpBuff[i]))
			{
				values[a] = tmpBuff[i];
				a++;
			}
		}
		printf("%s\n", values);
		a = 0;
	}
}
