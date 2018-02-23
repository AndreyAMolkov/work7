#define _CRT_SECURE_NO_WARNINGS
#define CHECK_FALL 0
#define CHECK_OK 1
#include "task5.h"
#include<string.h>
#define MAXSYMB 256
#define SIZEPAK 8
#define GARBAGE 9
#define ERRORPointer NULL
#define WRONGNEGATIVEVALUE -100
#define EMPTY 0

PSYM* readHederInfinalFile(FILE*fpMOL, int *maxlengthArray, TSYM* psyms[], int *number0LastBit, ULL *numberLetter)
{
	int i;
	int pos1 = ftell(fpMOL);//
	int posEndHeader;// position of end header
	char*signatureEtalon = "MOL";//signature. A set of multiple characters that allws you to set the file belongs to a specific format
	char signature[4] = {0};
						   //int maxlengthArray; the number of unique charactrs.Contains the numberof rows in the table occurences.
						   //PSYM* psyms //Table of occurence. Here stored records aboun symbols and frequencies. They need to be stored in binay without gaps.
						   //number0LastBit//The length tail. File size .101 not always a multiple of 8, so at the end you you may see 'tail' of several bits. We add them to full byte and keep the actual length
						   //numberLetter // The size of the sourse file.Need to control out of the box
						   //The original file extentision. If the compressor changes expansion the original fille must then be restored.

	fread(signature, sizeof(char), 3, fpMOL);
	i = 0;
	while(signatureEtalon[i]!='\0')
		if (signature[i] != signatureEtalon[i++])
		{
			printf("ERROR readHederInfinalFile: Signature =%s wrong. exit\n",signature);
			return CHECK_FALL;
		}
	
	fread(maxlengthArray, sizeof(int), 1, fpMOL);
	if ((psyms=recordStringtoPSYM(*maxlengthArray, psyms, fpMOL))==NULL)
	{
		printf("ERROR recordPSYMtoString: exit from creatHederInfinalFile\n");
		return CHECK_FALL;
	}
	//int posnaw = ftell(fpMOL);
	int *pint = (int*)calloc(2, sizeof(int));
	ULL *pULL = (ULL*)calloc(2, sizeof(ULL));
	char *pchar = (char*)calloc(2, sizeof(char));
	fread(number0LastBit, sizeof(int), 1, fpMOL);
	//posnaw = ftell(fpMOL);
	fread(numberLetter, sizeof(ULL), 1, fpMOL);
	posEndHeader = ftell(fpMOL);//
	return psyms;
}
PSYM* recordStringtoPSYM(int maxlengthArray, TSYM* psyms[], FILE*fpMOL)
{
	//int i;
	UC* stringChar = 0x0;
	while (!stringChar)
	stringChar = (UC*)calloc(maxlengthArray+2, sizeof(UC));
	float*stringFloat = 0x0;
	while(!stringFloat)
	stringFloat= (float*)calloc(maxlengthArray+2, sizeof(float));
	int pos1 = ftell(fpMOL);//
fread(stringChar, sizeof(UC), maxlengthArray, fpMOL);
	psyms=recordPsymsChar(maxlengthArray, psyms, stringChar);
	if(psyms==ERRORPointer)
	{
		printf("ERROR recordStringtoPSYM: fall recordPsymsChar. Exit from writeHederInfinalFile\n");
		return CHECK_FALL;
	}
fread(stringFloat, sizeof(float), maxlengthArray, fpMOL);
	psyms = recordPsymsFloat(maxlengthArray, psyms, stringFloat);
	if (psyms == ERRORPointer)
	{
		printf("ERROR recordFloattoPSYM: fall recordPsymsFloat. Exit from writeHederInfinalFile\n");
		return CHECK_FALL;
	}
	
	
	int pos2 = ftell(fpMOL);
	*psyms = *psyms;
	return psyms;
}
PSYM*recordPsymsChar(int maxlengthArray, TSYM* psyms[],UC*stringChar)
{
	int i;

	while (!psyms)
		psyms = (PSYM*)calloc(maxlengthArray + 2, sizeof(PSYM));
	for (i = 0;i < maxlengthArray;i++)
	{
		psyms[i] = (TSYM*)calloc(1, sizeof(TSYM));
		psyms[i]->ch = stringChar[i];
	}
	psyms[i] = NULL;
	return psyms;
}
PSYM*recordPsymsFloat(int maxlengthArray, TSYM* psyms[], float*stringFloat)
{
	int i;
	for (i = 0;i < maxlengthArray;i++)
	{
		psyms[i]->freq = stringFloat[i];
	}

	return psyms;
}

long int readPak(FILE*fileTo, FILE*fileFrom, int number0LastBit)
{
	int pos3 = ftell(fileFrom);
	//char *bufChar = (char*)calloc(SIZEPAK, sizeof(char));
	char charTemp = GARBAGE;
	unsigned int count = 0;
	int result = 0;
	
	do {
		long int pos = ftell(fileFrom);
		result=fread(&charTemp, sizeof(unsigned char), 1, fileFrom);
		if (result == 0)
		{
			fseek(fileTo, -number0LastBit, SEEK_CUR);// place the pointer in the desired position = -number0LastBit of numbers
			fputc(' ', fileTo);// cut the tail
			break;
		}
		unpack(charTemp, fileTo);
		 
			charTemp = GARBAGE;
		count++;
	} while (result != 0);// check the condition equality lenght  to SIZE f one char (in current event it is 8 bit)

	return count;
}

int unpack(char buf,FILE*fp)
{
	int count=0;
	union CODE code;
	
	code.ch = buf;
	char *bufChar = (char*)calloc(SIZEPAK, sizeof(char));
		bufChar[0]=code.byte.b1+'0';
		bufChar[1] = code.byte.b2 + '0';
		bufChar[2] = code.byte.b3 + '0';
		bufChar[3] = code.byte.b4 + '0';
		bufChar[4] = code.byte.b5 + '0';
		bufChar[5] = code.byte.b6 + '0';
		bufChar[6] = code.byte.b7 + '0';
		bufChar[7] = code.byte.b8 + '0';
		bufChar[8] = '\0';
		count = fwrite(bufChar, sizeof(char), SIZEPAK, fp);
	
	return count;
}
int createFp(FILE*fp101, TSYM*root, FILE*fp)
{
	TSYM*Beginner = root;
	char ch = ' ';
	UC letter = ' ';
	int pos = ftell(fp101);
	while (fread(&ch, sizeof(char), 1, fp101)==CHECK_OK)
	{
		letter = root->ch;// record value from the current structure in letter
		
		int posFile = ftell(fp101);//check position in file for check
			if (ch == '1')
			{
				root = root->lessNode;// go to intro tree
				if (root == NULL)// check the path is true or false
				{
					fwrite(&letter, sizeof(UC), 1, fp);// record the letter becouse after it there is no path
					//fputc(letter, stdout);// need for check
					root = Beginner;
					fseek(fp101, -1, SEEK_CUR);
					letter = GARBAGE;
				}
				
			}
			else if (ch == '0')
			{
				root = root->moreNode;// got to intro tree
				if (root == NULL)
				{
					fwrite(&letter, sizeof(UC), 1, fp);// found the letter becouse after it there is no path
					//fputc(letter, stdout);// need for check
					root = Beginner;
					fseek(fp101, -1, SEEK_CUR);// to pointer -1 position in file
					letter = GARBAGE;
				}
				
			}
			else
			{
				fwrite(&letter, sizeof(UC), 1, fp);// found the letter becouse after it there is no path
				//fputc(letter, stdout);// need for check
				//fputc('\n', stdout);
			return CHECK_OK; ;// becouse found ' ', this symbol haven't '1' or '0'
			}
	ch = GARBAGE;// for safe fill incorect value
	
	}
		

	
	return CHECK_OK;
}
