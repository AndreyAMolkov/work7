#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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
int checkCreateStructurs(TREGION*headStructere, FILE *fp);//verify that the structure list is created correctly
unsigned int countTotalUnitInTree(TREGION*headStructere);
unsigned int countTotalRowInFile(FILE*fp);
void findErrorTreeFromFile(TREGION*headStructere, FILE*fpcheck);// need for search a problem, and print it
int findLDataStructureInString(char*buf, TREGION*headStructere);//if all elements of one structure  were find then go to next loop, else print its line of text on the console
int compareString(char* sourseString, char* xString,int maxLenght);
void prepareForListCountry(PREGION*listCountry,PREGION listRegions);//create pointer to array of pointers
unsigned int countTotalRegions(TREGION *listRegions);
unsigned int createListCountry(PREGION*listCountry, int lengthArray);
int searchRegionsOfCountry(TREGION*listRegions, char*answer);
int checkCountryOrRegions(char*sourseString, char* Xstring);
char*smallLetter(char string[]);// make all the letters in the lines small
int searchListOfCountry(TREGION*listCountry[], char*string, TREGION*listRegions);
void printRegionsOfCountry(TREGION*listRegions);
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