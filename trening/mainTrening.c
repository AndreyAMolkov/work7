#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

char *foundFullName(FILE*fp)
{
	fp = (char*)fp;
	char *name = (char*)calloc(256,sizeof(char));
	char *string=0x0;
	string = fp;
	
	for (int i = 0;string[i] != '\0';i++)
		name[i] = string[i];

	return name;
}

main()
{

	char *name =0x0;
	FILE*fp = fopen("file with 101.txt", "rt");
	if (fp == NULL)
	{
		puts("error opened file");
		return 1;
	}
	printf("%p  %s", fp,((char*)fp));
	name = foundFullName(fp);

	return 0;
}