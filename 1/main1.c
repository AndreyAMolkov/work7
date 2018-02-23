#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include "task1.h"
#include<ctype.h>
#define MAXLETTER 128
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
	unsigned int totalRegions;
	unsigned int totalCounties;
	char answer[MAXLETTER];
	//a)generate a list based on file data.
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
	
	
	totalRegions = 0;
	totalRegions=countTotalRegions(listRegions);
	listCountry = 0x0;
	while(listCountry==NULL)
		listCountry = (PREGION*)calloc(totalRegions+3, sizeof(PREGION));
	prepareForListCountry(listCountry,listRegions);
	totalCounties = 0;
	totalCounties =createListCountry(listCountry,totalRegions);
	//(b)Search and display all the data in the letter designation of the country.
	printf("Do You would search (Yes or No)\n");
	scanf("%s", answer);
	if (tolower(*answer) == 'n')
	{
		puts("You answer was: No\n Exit from the program");
		return 0;
	}
	printf("Do You would search regions of Country or Country ( input : Country or regions)\n");
	scanf("%s", answer);
	if (tolower(*answer) == 'r')
	{
		printf("Input the name of Region ( for example, Novgorod)\n");
		scanf("%s", answer);
		
		if(searchRegionsOfCountry(listRegions, answer)==CHECK_FALL)
					puts("The region not found\n");
	}
	if (tolower(*answer) == 'c')
	{
		printf("Input the name of Country ( for example, Zimbabve)\n");
		scanf("%s", answer);

		if (searchListOfCountry(listCountry, answer,listRegions) == CHECK_FALL)
			puts(" Country not found\n");
	}
	return 0;
}
//. To write a program that 
//a)generate a list based on file data.
//(b)Search and display all the data in the letter designation of the country.
//(c)Search for a specific region by name.