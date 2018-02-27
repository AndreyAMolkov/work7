#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#include "task5.h"
#define MAXSYMB 256
#define successfully 1
#define fall 0
#define SIZEPAK 8
#define EMPTY 0
#define GARBAGE 9
#define ERRORPointer NULL
#define WRONGNEGATIVEVALUE -100
#define CHECK_FALL 0
#define CHECK_OK 1
#define WRITE "wb"
#define READ "rb"
int main(int argc,UC*argv[])
{
	/*
	UC *argv[256];
	argv[1] = "fp2.MOL";//it need for debug
	int argc = 2;

	*/
	if (argc == 1)
	{
		puts("ERROR: not file");
		return 1;
	}

	int number0LastBit;//number added zerros in the last bit
	int maxlengthArray;//the number of unique charactrs.Contains the numberof rows in the table occurences.
	struct SYM *root;
	FILE*fp101;//file with changing of data of input file. outcome - Must had the file with '1' and '0'; 
	FILE*fpMOL;// result of our work
	long int lengthFpMOL;
	PSYM *psyms;
	PSYM *psymsCode;
	ULL sizeInputFile;
	int ch = ' ';
	fpMOL = fopen(argv[1], READ);
	if (fpMOL == NULL)
	{
		puts("ERROR opened the first file");
		return 1;
	}
	number0LastBit = -1;// WRONGNEGATIVEVALUE;//initialisatioon wrong value 
	psyms = 0x0;
	maxlengthArray = WRONGNEGATIVEVALUE;
	sizeInputFile = 0;
	UC*extension=0x0;
	psyms = readHederInfinalFile(fpMOL, &maxlengthArray, psyms, &number0LastBit, &sizeInputFile, &extension);
	if (psyms == NULL)
		return 1;
	else
		;//puts("create header in the final file was OK\n");

	psymsCode = 0x0;
	while (!psymsCode)
		psymsCode = (PSYM*)calloc(maxlengthArray + 2, sizeof(PSYM));

	copyParrToChange(psyms, psymsCode);
	root = 0x0;
	root = buildTree(psymsCode, maxlengthArray);

	//	printArrayForScreen(psyms);
	makeCodes(root);
	//printArrayForScreen(psyms);
	fp101 = fopen("file with 101.txt", WRITE);
	if (fp101 == NULL)
	{
		puts("ERROR opened the file .101");
		return 1;
	}
	lengthFpMOL = readPak(fp101,fpMOL,number0LastBit);// final
	if (lengthFpMOL == EMPTY)
	{
		printf("Error create final file. EXIT");
		return 1;
	}
	
	fclose(fp101);// close, for open of reading

	fp101 = fopen("file with 101.txt", READ);
	rewind(fp101);

	FILE *fpOut=0x0;
	UC flagCopy[MAXSYMB] = {0};
	UC*newExtension = extension;
	UC* nameOutputFile = 0x0;
	do {
		nameOutputFile = createNameFile(argv[1], newExtension, flagCopy);

		if (nameOutputFile == NULL)
			return 1;
		fpOut = fopen(nameOutputFile, READ);
		if (fpOut != NULL)
		{
			UC*flagCopyNew = "_copy";//// add to the name if you want to notify the user about protecting an existing file
			int lengthCopyNew = strlen(flagCopyNew);
			strcat(flagCopy, flagCopyNew, lengthCopyNew);
			fclose(fpOut);
		}
	} while (fpOut != NULL);
	
	fpOut =fopen(nameOutputFile, WRITE);
	if(fpOut==NULL)
	{
		printf("ERROR opened the final for record-%s", nameOutputFile);
		return 1;
	}
	

if (CHECK_FALL == createFp(fp101, root, fpOut))
{
	printf("ERROR create file Fp");
	return 1;
}
else
printf("The file has benn successfuly unpacked \n The adress for the file - %s\n", nameOutputFile);
int result = 0;


	fclose(fpOut);
	fclose(fp101);
	fclose(fpMOL);

	if (extension != NULL)
		free(extension);

	if (root != NULL)
		free(root);
	if(nameOutputFile!=NULL)
		free(nameOutputFile);
	return 0;
}