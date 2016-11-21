#include <stdio.h>
#include <sysexits.h>
#include <sys/stat.h>
#include <string.h>
#include <ctype.h>

int main (int argc, char *argv[])
{
	FILE *encodeFile;
	char numCheck[20] = {'0','1','2','3','4','5','6','7','8','9'};
	if(argc < 2)
	{
		printf("Please provide a file to be decoded\n");
		return EX_USAGE;
	}else{ 
		encodeFile = fopen(argv[1], "rb");
	}

	char *value;
	char tmpBuff[64];
	for(size_t count = 0; count < 4; count ++);
	{
		fgets(tmpBuff, sizeof(tmpBuff), encodeFile);
		while(1)
		{
			for(size_t num = 0; num < sizeof(numCheck); num++)
			{
				value = strstr(numCheck[num], tmpBuff);
			}
		}

	printf("%s\n", value);

	}


}
