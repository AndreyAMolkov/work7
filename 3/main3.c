#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include "task3.h"
#include<ctype.h>
#include<stdlib.h>
//typedef int BASE_TYPE;
#define MAXSYMB 256
extern FILE *fpOut;
#define successfully 1
#define fall 0
#define WRITE "wb"
#define READ "rb"
int main()
{
	//int totalSymbolInfile;
	BASE_TYPE maxCount;
	FILE *fp;
	PSYM *psyms;
	//int number;
	ULL numberLetter;
	TSYM* treeSym;
	int ch = ' ';
	int totalStructInfile;
	int maxlengthArray;
	fp = fopen("fp.doc", READ);// The input file
	if (!fp)
	{
		puts("error opening file fp");
		return 1;// error opening  files 
	}
	for (treeSym = 0x0,numberLetter = 0;(ch = fgetc(fp)) != EOF;numberLetter++)// are creating a tree from an input file and the total quantity of letters
		treeSym = makeTree(treeSym, ch, 128);//adress the first node
	fclose(fp);
	totalStructInfile = 0;//The quantity of structs in file
	countTotalStructInTree(treeSym, &totalStructInfile);
	if(treeSym ==0x0)
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
	while(!psyms) 
		psyms = (PSYM*)calloc(totalStructInfile+2, sizeof(PSYM));// add 2 cell for 
	copyTree2Parr(treeSym, psyms);////create array of pointers for structures
	maxlengthArray = 0;
	maxlengthArray = totalStructInfile;
	psyms[maxlengthArray] = NULL;
 if (!checkDataParray(psyms,numberLetter,treeSym))
 {
	 puts("Error copy Tree to syms");
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

  makeFrequencyForArray(psyms, numberLetter,maxlengthArray);//filling in the array of frequency of occurence

 if(!checkSumForFrequencyArray(psyms))
 {
	 puts("ERROR: made frequency in the array");
	 return 1;
 }
 if (!printArrayForCheck(psyms))
 {
	 puts("Error: fall of print of the file for check");
	 return 1;
 }
 printArrayForScreen(psyms);
 
 return 0;
}

/*Write a program that builds a character-occurrence table for an arbitrary file whose name is specified on the command line. 
The program should display a table of occurrence, sorted by descending frequency
Explanation

The program needs to determine the structural type SYM, in which you want to store the symbol code and frequency of occurrence 
(real number from 0 to 1).After reviewing the file, an array of SYM structures should be sorted by frequency.

Composition

Three files are created: task3.h, task3.c, main3.c.*/