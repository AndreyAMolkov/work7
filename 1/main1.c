#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include "task1.h"
#include<ctype.h>
#define CHECK_OK 0
#define CHECK_FALL 1
#define ERROR 0
#define POINTER_FALL  0
typedef long int LI;
int main()
{
	int result = CHECK_FALL;// unutialisation of negative
	PREGION listRegions=0x0;
	PREGION*listCountry;
	FILE* fp;
	unsigned int totalCountry;
	fp= fopen("fips10_4.csv ", "rt");
	if (!fp)// check open file
	{
		puts("Error: open file");
		return ERROR;
	}
	
	
	listRegions = createListRegions(fp);//creates a linked list with records of regions and their codes according to the content of the data file
	if (listRegions == POINTER_FALL)
	{
		puts("Error main: Created list of regions");
		return ERROR;
	}
	
	result = CHECK_FALL;
	if (checkCreateStructurs(listRegions, fp) == CHECK_FALL)// verify that the structure list is created correctly by comparring its length with the number of rows and displaing the result on the console
		;//	findErrorTreeFromFile(listRegions, fp);// need for search a problem, and print it (What is lost)
	else
		;// didn't use here
	
	listCountry = 0x0;
	totalCountry = 0;
	countTotalCountry(listRegions,&totalCountry);
	listCountry = (PREGION*)calloc(totalCountry+3, sizeof(PREGION));
	createListCountry(listCountry,listRegions);

	return 0;
}
//. To write a program that 
//a)generate a list based on file data.
//(b)Search and display all the data in the letter designation of the country.
//(c)Search for a specific region by name.