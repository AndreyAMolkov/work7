#include<stdio.h>


struct REGION
{
	char id_country[20];// id country (2letter)
	char id_region[20];
	char name[256];
	struct REGION* next;
};
typedef struct REGION TREGION;
typedef TREGION * PREGION;

TREGION *createListRegions(FILE*fp);
TREGION* makeListOfStructure(TREGION* Region, char *stringOfRegion);
char* readStringFromFile(FILE*InputFile, char*stringOfRegion);
int checkDataRegion(char*stringOfRegion);
TREGION*fillStruct(TREGION*Region, char*stringOfRegion);
char*fillBox(char*from, char* to);
int conditionRecordInline(char symbol);
char*prepareForLetter(char*from);
/*
. To write a program that creates a linked list with records of
regions and their codes according to the content of the data file
Comment:
File downloaded at: http://introcs.cs.princeton.edu/java/data/fips10_4.csv
The program should support the following functions:
(a) generate a list based on file data.
(b) Search and display all the data in the letter designation of the country.
(c) Search for a specific region by name.
*/