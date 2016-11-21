

int main (int argc, char *argv[])
{
	FILE *encodeFile;

	if(argc < 2)
	{
		printf("Please provide a file to be decoded\n");
		return EX_USAGE;
	}else{ 
		encodeFile = fopen(argv[1], "rb");
	}

