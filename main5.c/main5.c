#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
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
int main()
{
	int number0LastBit;//number added zerros in the last bit
	int maxlengthArray;//the number of unique charactrs.Contains the numberof rows in the table occurences.
	//int countGap;
	//long int result;// need for checks
	struct SYM *root;
	//BASE_TYPE maxCount;
	FILE *fp;// output file
	FILE*fp101;//file with changing of data of input file. outcome - Must had the file with '1' and '0'; 
	FILE*fpMOL;// result of our work
	//long int lengthFp101;
	long int lengthFpMOL;
	PSYM *psyms;
	PSYM *psymsCode;
	ULL numberLetter;
	//TSYM* treeSym;
	int ch = ' ';
	//char checkchar;
	//int totalStructInfile;
	//int positionEndHeader;

	fpMOL = fopen("result.txt", READ);
	if (fpMOL == NULL)
	{
		puts("ERROR opened thefinal file");
		return 1;
	}
	number0LastBit = -1;// WRONGNEGATIVEVALUE;//initialisatioon wrong value 
	numberLetter = EMPTY;
	psyms = 0x0;
	maxlengthArray = WRONGNEGATIVEVALUE;

	psyms = readHederInfinalFile(fpMOL, &maxlengthArray, psyms, &number0LastBit, &numberLetter);
	if (psyms == NULL)
		return 1;
	else
		puts("create header in the final file was OK\n");
	printArrayForScreen(psyms);
	psymsCode = 0x0;
	while (!psymsCode)
		psymsCode = (PSYM*)calloc(maxlengthArray + 2, sizeof(PSYM));

	copyParrToChange(psyms, psymsCode);
	root = 0x0;
	root = buildTree(psymsCode, maxlengthArray);
	printArrayForScreen(psyms);
	if (!printArrayForCheck(psyms))
	{
		puts("Error: fall of print of the file for check");
		return 1;
	}
	makeCodes(root);
	printArrayForScreen(psyms);
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
	
fclose(fp101);// close for open for reading

fp101 = fopen("file with 101.txt", READ);
rewind(fp101);
fp = fopen("output.txt", WRITE);
if (CHECK_FALL == createFp(fp101, root, fp))
{
	printf("ERROR create file Fp");
	return 1;
}




	fclose(fp101);
	fclose(fpMOL);
	return 0;
}