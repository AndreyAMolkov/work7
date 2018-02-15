#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include "task1.h"
#include<ctype.h>
#include<string.h>
#define CHECK_OK 0
#define CHECK_FALL 1
#define GARBAGE '\0'  //selection is made for string
typedef long int LI;
#define MAX_LENGHT_STRING 255
#define POINTER_FALL  0
PREGION createListRegions(FILE*fp)//creates a linked list with records ofregions and their codes according to the content of the data file
{
	LI i;// the tempt value
	char *stringOfRegion;//The buffer are for reading the file "fp"
	char buf[MAX_LENGHT_STRING] = {0};
	TREGION*HeadOfRegions = 0x0;
	LI totalRegions;
	TREGION*region;
		if (!fp)// check open file
		{
			puts("ERROR: the transferred pointer to FILE*");
			return POINTER_FALL;
		}
	
		for (region = 0, totalRegions = 0, i = 0;(stringOfRegion = readStringFromFile(fp, buf)) != NULL;i++)// for will be work until didn't return -1
		{
			if (checkDataRegion(stringOfRegion) == CHECK_FALL)//check whether the line belongs to a region
			{
				printf(". The line number %li\n",i);
				continue;// The string containing the data of region includes ' " ', if not then go to the next iteration
			}
			
				region= makeListOfStructure(region, stringOfRegion);// create list of regions
				if (HeadOfRegions == 0) HeadOfRegions = region;
			if(region== POINTER_FALL)// check : if returned the empty pointer
			{
				puts("ERROR of makeListOfStructure: the transferred pointer to region was EMPTY");
				return POINTER_FALL;
			}

			totalRegions = i;
		 memset(buf, GARBAGE, sizeof(buf));// record garbge in "buf"
		}
		
return HeadOfRegions;
}
char* readStringFromFile(FILE*InputFile,char*buf)// the function record a string from a file to the buf 
{
	
	

	return fgets(buf, MAX_LENGHT_STRING, InputFile);//buf;
}
int checkDataRegion(char*stringOfRegion)
{
	char ch = '"';
	int lenString=CHECK_FALL;
	char *presult = 0x0;
	lenString = strnlen(stringOfRegion, MAX_LENGHT_STRING);
	presult=strchr(stringOfRegion, ch);
	if (((stringOfRegion+lenString)-presult)>lenString)//check out: the resulting value contained in the input string?
	{
		printf("in line ' %s '  didn't find signs ' %c ' belonging to the region.",stringOfRegion,ch);
			return CHECK_FALL;
	}

	return CHECK_OK;
}


TREGION* makeListOfStructure(TREGION* region, char *stringOfRegion)
{
	if (region == NULL)
	{
		if ((region = fillStruct(region, stringOfRegion)) == 0x0)// record data in a structure fall
			printf("Attention: makeListOfStructure: the gapin data records in Country - %s code of region - %s  name of region - %s", region->id_country, region->id_region, region->name);
	return region;
	}
	else
		while (region->next != NULL)
			region = region->next;
			region->next=makeListOfStructure(region->next,stringOfRegion);
}

TREGION*fillStruct(TREGION *Region, char*stringOfRegion)
{
	auto int i= 0;
	auto int lenghtString = 0;
	while (1)// check out string without '\0', if found then exit
	{
		if (stringOfRegion[i] == '\0')
		{
			lenghtString=i;
			break;
		}
		if (i++ > MAX_LENGHT_STRING)
		{
			printf("ERROR fillStuct: not data in stringOfRegion");
			return POINTER_FALL;// error Fall
		}
	}
			
	char*p = stringOfRegion;
	Region =(TREGION*) calloc(1, sizeof(TREGION));
	Region->next = NULL;
	p = fillBox(p, Region->id_country);
	p = fillBox(p, Region->id_region);
	p = fillBox(p , Region->name);
	
		return Region;
}
char*fillBox(char*from, char* to)
{
	

	int iFrom=0;
	int iTo=0;
	int limitField = 0;
	from = prepareForLetter(from);// move the pointer to the first letter or number
	if (from == POINTER_FALL)
	{
		printf("Error prepareForLetter: error movi pointer to letter for %s", from);
		return 0x0;// error error
	}

	//	for (iFrom = 0, iTo = 0; from[iFrom] != '\0' || iFrom > MAX_LENGHT_STRING;iFrom++)// if caught NULL  then go to from fillBox
//	{
		while (conditionRecordInline(from[iFrom]) == CHECK_FALL)//didn't find characters other than letters or numbers
				to[iTo++] = from[iFrom++];// may be error if input will be > quantity cell
	
//	}
	if (iFrom == 0)
	{
		printf("Attention: trying to write to an information's structure the empty data %s", from);
	}
	return &from[iFrom];
}

int conditionRecordInline(char charSymbol)
{
	int symbol = charSymbol;// need for check
	switch (symbol)
	{
	case 44:// for ',' - ASCII
		break;
	case 34:// for ' " ' - ASCII
		break;
	case 92://for '\ ' - ASCII
		break;
	case 10://for '\n ' - ASCII
		break;
	default:
	{return CHECK_FALL;}
	}
	return CHECK_OK;
}
char*prepareForLetter(char*from)
{
	int i;
	for (i=0;i < MAX_LENGHT_STRING|| from[i]=='\0';i++)
	{
		if (isalpha(from[i]) || isalnum(from[i]))// if it's not letter or number move pointer
			return &from[i];
		
	}
	return POINTER_FALL; // return Error
}
//a)generate a list based on file data.
//(b)Search and display all the data in the letter designation of the country.
//(c)Search for a specific region by name.