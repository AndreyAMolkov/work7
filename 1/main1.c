#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include "task1.h"
#include<ctype.h>
#define CHECK_OK 0
#define CHECK_FALL 1
#define ERROR 0
typedef long int LI;
int main()
{
	int rezult = CHECK_FALL;// unutialisation of negative
	PREGION listRegions=0x0;
	FILE* fp;
	fp= fopen("fips10_4.csv ", "rt");
	if (!fp)// check open file
	{
		puts("Error: open file");
		return ERROR;
	}
	
	
	rezult= createListRegions(fp,listRegions);//creates a linked list with records of regions and their codes according to the content of the data file
	if (rezult==CHECK_FALL) 
	{
		puts("Error: Created list of regions");
		return ERROR;
	}


	return 0;
}
//. To write a program that 
//a)generate a list based on file data.
//(b)Search and display all the data in the letter designation of the country.
//(c)Search for a specific region by name.