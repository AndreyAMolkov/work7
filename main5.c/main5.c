#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include "task5.h"
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
	//int number;
	ULL numberLetter;
	TSYM* treeSym;
	int ch = ' ';
	char checkchar;
	int totalStructInfile;
	int positionEndHeader;


	return 0;
}