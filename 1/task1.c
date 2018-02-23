#define _CRT_SECURE_NO_WARNINGS
#include "task1.h"
#include<stdio.h>
#include<stdlib.h>
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
				puts("ERROR of makeListOfStructure: the transferred pointer to region was EMPTY\n");
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
		printf("in line ' %s '  didn't find signs ' %c ' belonging to the region.\n",stringOfRegion,ch);
			return CHECK_FALL;
	}

	return CHECK_OK;
}


TREGION* makeListOfStructure(TREGION* region, char *stringOfRegion)
{
	if (region == NULL)
	{
		if ((region = fillStruct(region, stringOfRegion)) == 0x0)// record data in a structure fall
			printf("Attention: makeListOfStructure: the gap in data records in Country - %s code of region - %s  name of region - %s\n", region->id_country, region->id_region, region->name);
	}
	else
	{
		while (region->next != NULL)
			region = region->next;
		region->next = makeListOfStructure(region->next, stringOfRegion);
	}
	return region;
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
			printf("ERROR fillStuct: not data in stringOfRegion/n");
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


int checkCreateStructurs(TREGION*headStructere, FILE *fp)//verify that the structure list is created correctly
{
	unsigned int totalCountStruct=0;
	unsigned int totalCountFile = 0;
	long int result = 0;
	totalCountStruct =countTotalUnitInTree(headStructere);
	if (totalCountStruct == CHECK_FALL)//total structs  equally zero
	{
		printf("ERROR checkCreateStructurs: total structs  equally zero\n");
		return CHECK_FALL;
	}
	
	totalCountFile = countTotalRowInFile(fp);
	if (totalCountFile == CHECK_FALL)// total rows in file equally zero
	{
		printf("ERROR checkCreateStructurs: total rows in file equally zero\n");
		return CHECK_FALL;
	}
	result = totalCountFile - totalCountStruct;
	if (result==0)
		return CHECK_OK;
	else if(result>0)
		printf("ATTENTION:The number of lines in the file is greater than the number of structures by %li\n",result);
	else 
		printf("ATTENTION: The number of structures is greater than the number of lines in the file  by %li\n",result );
	return CHECK_FALL;
}
unsigned int countTotalUnitInTree(TREGION*headStructere)
{
	unsigned count = 0;
	while(headStructere->next!=NULL)// note:the first item is not calculation
	{
		headStructere = headStructere->next;
		count++;
	}
	if (count == CHECK_FALL)
		return CHECK_FALL;

	count++;//this need for compensation of first element
		return count;
}
unsigned int countTotalRowInFile(FILE*fp)
{
	unsigned int count = 0;
	char buf[MAX_LENGHT_STRING];
	rewind(fp);
	while (fgets(buf, MAX_LENGHT_STRING, fp) != NULL)
	{
		if (strlen(buf) == (MAX_LENGHT_STRING-1))
			printf("ATTENTION:possible loss of data in row. The string -' %s '- is longer than the allowed lenght. max= %u  \n", buf, MAX_LENGHT_STRING);
		count++;
	}
	return count;
}
void findErrorTreeFromFile(TREGION*headStructere, FILE*fpcheck)// need for search a problem, and print it
{
	puts("\n\n\n");//to indent 
	unsigned int count;
	char buf[MAX_LENGHT_STRING];
	rewind(fpcheck);
	for (count=0;(fgets(buf, MAX_LENGHT_STRING, fpcheck)) != NULL;count++) // take 1 line of text in buffer
	{
		if (strlen(buf) == (MAX_LENGHT_STRING-1))
		{
			printf("ATTENTION:The line was not compared because it is larger than the allowed size =%i.The number line in text =%u Line of text =%s\n",MAX_LENGHT_STRING, count, buf);
			continue;
		}
		if (findLDataStructureInString(buf, headStructere) == CHECK_FALL)//if all elements of one structure  were find then go to next loop, else print its line of text on the console
				printf("ATTENTION:The line of text not found in list of structure .The number line in text =%u Line of text =%s\n", count, buf);

	
	}
}
int findLDataStructureInString(char*buf, TREGION*headStructere)
{
	unsigned count;
	for (count=0;headStructere->next != NULL;headStructere = headStructere->next)// previosly this need will be make for last element,
	{
		if (compareString(buf,headStructere->id_country, MAX_LENGHT_STRING) == CHECK_OK)// in tis function if string 2 was find in string 1 will be return CHECK_OK
		{
			if (compareString(buf, headStructere->id_region,  MAX_LENGHT_STRING) == CHECK_OK)
				if (compareString(buf, headStructere->name,  MAX_LENGHT_STRING) == CHECK_OK)
					return CHECK_OK;
		}

			count++;
	}
	//  make for last element,
	
		if (compareString(buf, headStructere->id_country, MAX_LENGHT_STRING) == CHECK_OK)// in tis function if string 2 was find in string 1 will be return CHECK_OK
		{
			if (compareString(buf, headStructere->id_region, MAX_LENGHT_STRING) == CHECK_OK)
				if (compareString(buf, headStructere->name, MAX_LENGHT_STRING) == CHECK_OK)
					return CHECK_OK;
		}

	return CHECK_FALL;// this means that the condition is not met
}

int compareString(char* sourseString, char* xString, int maxLenght)
{
	int iSourse, iXstring;
	int lengthXstring = strlen(xString);
	int lengthSourse = strlen(sourseString);
	for (iXstring = 0, iSourse = 0;(lengthSourse>0 && iSourse < maxLenght);lengthSourse--,iSourse++ )
	{
		
		if (sourseString[iSourse]==*xString)
			for (iXstring = 0;iXstring < maxLenght;iXstring++,iSourse++)
			{
				if (xString[iXstring] == '\0')// condition for succsessfuly
					return CHECK_OK;
				if (xString[iXstring] != sourseString[iSourse])// condition for fall
					break;// search next in this string
			}

		
	}

	return CHECK_FALL;
}
void prepareForListCountry(PREGION*listCountry,PREGION listRegions )//create pointer to array of pointers  of countses
{
	for (int i = 0;listRegions != NULL;i++)
	{
		listCountry[i] = listRegions;
		listRegions = listRegions->next;
	}

}


unsigned int countTotalRegions(TREGION *listRegions)
{
	int count = 0;
	for (unsigned int i = 0;listRegions != NULL;i++)
	{
		listRegions = listRegions->next;
		count = i;
	}
	return count;
}

unsigned int createListCountry(PREGION*listCountry, int lengthArray)
{
	//cut the some Country
	int i;
	unsigned count;
	char*currentCountry = 0x0;
	currentCountry = listCountry[0]->id_country;

	
	for (i = 1;listCountry[i] != NULL;i++)
	{
		if (compareString(listCountry[i]->id_country, currentCountry, MAX_LENGHT_STRING) == CHECK_OK)//if Country found then cut from list,pointer to NULL
			listCountry[i] = NULL;
		else//record in currentCountry the new name Country
			currentCountry = listCountry[i]->id_country;
	}
	// sortihg of Country
	for (i = 0,count=0;i < lengthArray;i++)
	{
		if (listCountry[i] != NULL)
			continue;// search the empty position for sort of Countrys
		for (int j = i;j < lengthArray;j++)// search the Country for shift
		{
			if (listCountry[j]== NULL)
				continue;
			listCountry[i] = listCountry[j];// the pointer up the list
			listCountry[j] = NULL;
			count = i;
			break;// next loop
		}
		
	}

	return count;
}
int searchRegionsOfCountry(TREGION*listRegions, char*string)
{
	//printf("%s\t%s\t%s\n", "Country", "Id Region", "The Name of Region");
		int lengthAnswer = strlen(string);
	if (lengthAnswer == 0)
	{
		puts("Error serchRegionsOfCountry: input empty question, check the program");
		return CHECK_FALL;
	}
	char*answer = (char*)calloc(lengthAnswer+2,sizeof(char));
	strcpy(answer, string);
	answer = smallLetter(answer);
	char *currentRegion=(char*)calloc(MAX_LENGHT_STRING,sizeof(char));	
	int lengthRegion = 0;
	int i;
	for (i = 0;listRegions != NULL;i++)
	{
		strcpy(currentRegion,listRegions->name);
		currentRegion = smallLetter(currentRegion);
		if (compareString(currentRegion, answer, MAX_LENGHT_STRING) == CHECK_OK)
			printf("%s\t   %s\t    %s\n", listRegions->id_country, listRegions->id_region, listRegions->name);
		listRegions = listRegions->next;
		*currentRegion = '\0';// for safety
	}
	return CHECK_FALL;
}
char*smallLetter(char string[])
{
	for(int i=0;string[i]!='\0';i++)
		string[i] = tolower( string[i]);
	return string;
}


int searchListOfCountry(TREGION*listCountry[], char*string, TREGION*listRegions)
{
	//printf("%s\t%s\t%s\n", "Country", "Id Region", "The Name of Region");
	int lengthAnswer = strlen(string);
	if (lengthAnswer == 0)
	{
		puts("Error serchRegionsOfCountry: input empty question, check the program");
		return CHECK_FALL;
	}
	char*answer = (char*)calloc(lengthAnswer + 2, sizeof(char));
	strcpy(answer, string);
	answer = smallLetter(answer);
	char *currentCountry = (char*)calloc(MAX_LENGHT_STRING, sizeof(char));
	int lengthCountry = 0;
	int i;
	for (i = 0;listCountry[i] != NULL;i++)
	{
		strcpy(currentCountry, listCountry[i]->id_country);
		currentCountry = smallLetter(currentCountry);
		if (compareString(currentCountry, answer, MAX_LENGHT_STRING) == CHECK_OK)
			printRegionsOfCountry(listCountry[i]);
		
		*currentCountry = '\0';// for safety
	}
	return CHECK_FALL;
}
void printRegionsOfCountry(TREGION*listRegions)
{
	char *currentCountry = listRegions->id_country;

	for (int i = 0;listRegions != NULL;i++)
	{	if (compareString(listRegions->id_country, currentCountry, MAX_LENGHT_STRING) == CHECK_OK)
				printf("%s\t   %s\t    %s\n", listRegions->id_country, listRegions->id_region, listRegions->name);
		
		listRegions = listRegions->next;	
	}
}
//a)generate a list based on file data.
//(b)Search and display all the data in the letter designation of the country.
//(c)Search for a specific region by name.