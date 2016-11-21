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


}
