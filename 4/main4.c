#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include "task4.h"
#define MAXSYMB 256
//xtern FILE *fpOut;
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
	int countGap;
	long int result;// need for checks
	struct SYM *root;
	BASE_TYPE maxCount;
	FILE *fp;// input file
	FILE*fp101;//file with changing of data of input file. outcome - Must had the file with '1' and '0'; 
	FILE*fpMOL;// result of our work
	long int lengthFp101;
	long int lengthFpMOL;
	PSYM *psyms;
	PSYM *psymsCode;
	ULL numberLetter;
	TSYM* treeSym;
	int ch = ' ';
	char checkchar;
	int totalStructInfile;
	int positionEndHeader;
	fp = fopen("1.txt", READ);// The input file
	if (!fp)
	{
		puts("error opening file fp");
		return 1;// error opening  files 
	}
	for (treeSym = 0x0, numberLetter = 0;(ch = fgetc(fp)) != EOF;numberLetter++)// are creating a tree from an input file and the total quantity of letters
	{
		checkchar = ch;
		treeSym = makeTree(treeSym, ch, 128);//adress the first node

	}
	//fclose(fp);
	totalStructInfile = 0;//The quantity of structs in file
	countTotalStructInTree(treeSym, &totalStructInfile);
	if (treeSym == 0x0)
	{
		puts("ERROR check to create a tree");
		return 1;// error create tree
	}

	if (!check2Tree(treeSym, numberLetter))// check true of created tree
	{
		puts("ERROR; check to create a tree");
		return  1;
	}

	psyms = 0x0;
	while (!psyms)
		psyms = (PSYM*)calloc(totalStructInfile + 2, sizeof(PSYM));// add 2 cell for 
	copyTree2Parr(treeSym, psyms);////create array of pointers for structures
	maxlengthArray = 0;
	maxlengthArray = totalStructInfile;
	psyms[maxlengthArray] = NULL;
	if (!checkDataParray(psyms, numberLetter, treeSym))
	{
		puts("Error copy Tree to syms");
		return 1;
	}
	makeFrequencyForArray(psyms, numberLetter, maxlengthArray);//filling in the array of frequency of occurence

	if (!checkSumForFrequencyArray(psyms))
	{
		puts("ERROR: made frequency in the array");
		return 1;
	}
	if (!printArrayForCheck(psyms))
	{
		puts("Error: fall of print of the file for check");
		return 1;
	}
	
	maxCount = 0;
	Tree2max(treeSym, &maxCount);// search the maximum value for a single symbol

	if (!sort(psyms, maxCount))
	{
		puts("Error: data of psyms different from data the treeSym");
		return 1;
	}
	if (!checkDataParray(psyms, numberLetter, treeSym))
	{
		puts("Error: data of psyms different from data the treeSym");
		return 1;
	}
printArrayForScreen(psyms);


	psymsCode = 0x0;
	while (!psymsCode)
		psymsCode = (PSYM*)calloc(maxlengthArray + 2, sizeof(PSYM));

	copyParrToChange(psyms, psymsCode);
	brushAdresses(psymsCode);//preparation for the Assembly of the tree, do cleaning old addresses
	root = 0x0;
	root = buildTree(psymsCode, maxlengthArray);//

	makeCodes(root);
	countGap = 0;

	countGap = checkMadeCodesUsually(psyms);
	if (countGap > 0)
	{
		printf("Error makeCodes: structs have field not contained code of '0' or '1'  =%i ", countGap);
		return 1;
	}

	printArrayForScreen(psyms);
	

	fp101 = fopen("file with 101.txt", WRITE);
	long int pos = ftell(fp101);
	lengthFp101 = EMPTY;
	pos = ftell(fp);
	rewind(fp);
	lengthFp101 = createFile101(fp, psyms, fp101);// 
	if (lengthFp101 == EMPTY)
	{
		puts("ERROR create File101:length file equalty ZERO ");
		return 1;
	}
	fclose(fp101);// close for open for reading
	fp101 = fopen("file with 101.txt", READ);
	//pos = ftell(fp101);
	//pos = ftell(fp);
	fpMOL = fopen("result.txt", WRITE);
	if (fpMOL == NULL)
	{
		puts("ERROR opened thefinal file");
		return 1;
	}
	rewind(fp101);
	pos = ftell(fp101);
	number0LastBit = WRONGNEGATIVEVALUE;//initialisatioon wrong value 
	number0LastBit =SIZEPAK- lengthFp101 % SIZEPAK;// calculate how much it will take zeros in the tail
	result=creatHederInfinalFile(fpMOL,maxlengthArray,psyms,number0LastBit,numberLetter);
	if (result == CHECK_FALL)
		return 1;
	else
		puts("create header in the final file was OK\n");
	positionEndHeader = WRONGNEGATIVEVALUE;
	positionEndHeader = result;
	lengthFpMOL = 0;
	lengthFpMOL = createPak(fpMOL,fp101,  number0LastBit);// final
	if (lengthFpMOL == EMPTY)
	{
		printf("Error create final file. EXIT");
		return 1;
	}
	if (number0LastBit == WRONGNEGATIVEVALUE)
	{
		printf("ATTENTIION: number0LastBit: to check the final assignment");
	}

result = WRONGNEGATIVEVALUE;
result = lengthFp101 - ((lengthFpMOL * SIZEPAK)-number0LastBit);
if (result != 0)
{
	printf("ERROR: wrong creatPak or createFile101, different=%li.   Exit\n", result);
	return 1;
}
else
	printf("To coding was OK, different=%li\n", result);
	
 fclose(fp);
fclose(fp101);
fclose(fpMOL);
	return 0;
}