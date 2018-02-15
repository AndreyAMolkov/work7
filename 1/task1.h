#include<stdio.h>


struct REGION
{
	char id[3];// id country (2letter)
	char name[256];
	struct REGION* next;
};
typedef struct REGION TREGION;
typedef TREGION * PREGION;

int createListRegions(FILE*fp, PREGION listRegions);
TREGION* makeListOfStructure(TREGION* headOfRegions, char *stringOfRegion);
char* readStringFromFile(FILE*InputFile);

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