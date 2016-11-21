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

//This handles the first four lines of the file
//TODO: put in a four loop and clean
	char tmpBuff [64];
	for(size_t count = 0; count < 4; count++)
	{
		fgets(tmpBuff, sizeof(tmpBuff), encodeFile);
		strtok(tmpBuff, " ");
		char *token = strtok(NULL, "\n");
		printf("%s\n", token);
	}

	fgets(tmpBuff, sizeof(tmpBuff), encodeFile);
	strtok(tmpBuff, ":");
	
	//TODO to lower function
	size_t i;
	int type;
	for( i = 0; i < strlen(tmpBuff); i++)
 	{
		tmpBuff[i]=tolower(tmpBuff[i]);
	}

	i = 0;
	if(strcmp(tmpBuff, "message")==0)
	{
		type = 0;
		printf("%d\n", type);
	}
	else if(strcmp(tmpBuff, "name") ==0)
	{
		type = 1;
		printf("%d\n", type);
	}
	else if(strncmp(tmpBuff, "get",3) == 0)
	{
		type = 3;
		printf("%d\n", type);
	}
	else if(strcmp(tmpBuff, "latitude") == 0)
	{
		type = 4;
		printf("%d\n", type);
	}
}


