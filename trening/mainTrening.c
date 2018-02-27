#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LENGTH_STRING 256


main(int argc,char*argv[])
{
	
	argc = 2;
	argv[1] = "C:\\git\\work7\\trening\\file with 101.txt";//it need for debag
	int lengthInputName;
	char *nameFile;
	if (argc == 1)
	{
		puts("ERROR: not file");
		return 1;
	}
	lengthInputName = 0;
	lengthInputName = strlen(argv[1]);
	
	nameFile = 0x0;
	while(nameFile==NULL)
		nameFile = (char*)calloc(lengthInputName + 2, sizeof(char));

	strncpy(nameFile, argv[1], lengthInputName);
	printf("%s",nameFile);


	
	return 0;
}