#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include "task1.h"
#include<ctype.h>
#include<string.h>
#define CHECK_OK 0
#define CHECK_FALL 1
#define GARBAGE '\0'  //selection is made for string
typedef long int LI;
#define MAX_LENGHT_STRING 255
int createListRegions(FILE*fp, PREGION listRegions)//creates a linked list with records ofregions and their codes according to the content of the data file
{
	LI i;// the tempt value
	char *stringOfRegion;//The buffer are for reading the file "fp"
	char buf[MAX_LENGHT_STRING] = {0};
	LI totalRegions;
	
	TREGION*headOfRegions;
		if (!fp)// check open file
		{
			puts("ERROR: the transferred pointer to FILE*");
			return CHECK_FALL;
		}
		if(listRegions!=0x0000000)// check initialisation list region, must had the matter = 0x0
		{
			puts("ERROR: the transferred pointer to listRegions DIDN'T EMPTY");
			return CHECK_FALL;
		}
	
		for (headOfRegions =0,totalRegions = 0,i = 0;(stringOfRegion=readStringFromFile(fp,buf))!= NULL;i++)// for will be work until didn't return -1
		{
			headOfRegions = makeListOfStructure(headOfRegions, stringOfRegion);
			if(headOfRegions== 0x0000000)// check : if returned the empty pointer
			{
				puts("ERROR: the transferred pointer to headOfRegions was EMPTY");
				return CHECK_FALL;
			}

			totalRegions = i;
		 memset(buf, GARBAGE, sizeof(buf));// record garbge in "buf"
		}
	return CHECK_FALL;
	return CHECK_OK;
}
char* readStringFromFile(FILE*InputFile,char*buf)// the function record a string from a file to the buf 
{
	
	fgets(buf, MAX_LENGHT_STRING, InputFile);

	return buf;
}
TREGION* makeListOfStructure(TREGION* headOfRegions, char *stringOfRegion)
{
	return 0x0;
	//return CHECK_OK;
}




//a)generate a list based on file data.
//(b)Search and display all the data in the letter designation of the country.
//(c)Search for a specific region by name.