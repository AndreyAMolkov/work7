#define _CRT_SECURE_NO_WARNINGS
#define CHECK_FALL 0
#define CHECK_OK 1
#include "task4.h"
#include<string.h>
#define MAXSYMB 256
#define SIZEPAK 8
#define GARBAGE 9
#define ERRORPointer NULL
#define WRONGNEGATIVEVALUE -100
#define EMPTY 0
void copyParrToChange(PSYM*psyms, PSYM*psymsCode)
{
	//int count;
	int i;
	for (i = 0;psyms[i] != NULL;i++)
	{
		psymsCode[i] = psyms[i];
		//count = i;
	}
	psymsCode[i] = NULL;
}
struct SYM* buildTree(TSYM *psym[], int N)
{
	// creation temporary node
	struct SYM *temp = (struct SYM*)malloc(sizeof(struct SYM));
	// In frequency field records the sum of frequencies of the last and penultimate elements of the psym array
	temp->freq = psym[N - 2]->freq + psym[N - 1]->freq;
	// associate the created node with the last two nodes
	temp->moreNode = psym[N - 1];
	temp->lessNode = psym[N - 2];
	temp->ch = -1;// initilisation negative number(a wrong value)
	temp->count = 0;
	temp->code[0] = '\0';
	if (N == 2) // We have created a root elements with a frequency of 1.0
		return temp;
	 desiredPositionPSYM(psym,N-1, temp);
	// add tempt to the desired position psym
	// the preservation of the decreasing order of frequency
	return buildTree(psym, N - 1);
}
void desiredPositionPSYM(PSYM*psym, int N, TSYM *temp)
{

	int destination=N;
	int i = 0;
	PSYM pfound = 0x0;
	PSYM pbuf = 0x0;
	for (i = N;i >= 0;i--)
	{
		if(psym[i]->freq < temp->freq ) 
		destination=i;
	} 
		
	pfound = psym[destination];//for check	
	for (i = N;i > destination;i--)
	{
		psym[i] = psym[i - 1];
	}
	psym[i] = temp;
	//psym[N] = NULL;
}

void makeCodes(TSYM *root)
{
	if (root->moreNode!=NULL)
	{
		strcpy(root->moreNode->code, root->code);
		strcat(root->moreNode->code, "0");
		makeCodes(root->moreNode);
	}
	if (root->lessNode!=NULL)
	{
		strcpy(root->lessNode->code, root->code);
		strcat(root->lessNode->code, "1");
		makeCodes(root->lessNode);
	}
	

}

void checkMadeCodesRecurs(TSYM*root,int *countGap)
{
	char checkSymbol = '/0';
	

	if (root->moreNode)
	{
		if (*(root->code) == checkSymbol)// if in didn't find 
		{
			*countGap += 1;
			printf("%i\n", root->ch);
		}
		checkMadeCodesRecurs(root->moreNode, countGap);
	}
	else if (root->lessNode)
	{
		if (*(root->code) == checkSymbol)
		{
			*countGap += 1;
			printf("%i\n", root->ch);
		}
		checkMadeCodesRecurs(root->lessNode,countGap);
	}
	

	//return countGap;
}
long int createFile101(FILE*fp_in,PSYM* psyms, FILE*fp101)
{
	int ch=0; // the code of symbol from input file
	unsigned int count=0;
	int i=0;
	if (fp_in == NULL)
	{
		puts("EROR createFile101: don't input file");
			return EMPTY;// error
	}
	while ((ch = fgetc(fp_in)) != -1)
		{
			for (i = 0;psyms[i]!=NULL;i++)
				if (psyms[i]->ch == (unsigned char)ch)
				{ 
					fputs(psyms[i]->code, fp101); // displaid string with the code
					count+=strlen(psyms[i]->code);
					break; //stop searching
				}
		}
		return count;
}
long int createPak(FILE*in,FILE*out,int number0LastBit)
{
	
	char *bufChar=(char*)calloc(SIZEPAK+2, sizeof(char));
	unsigned char charTemp= GARBAGE;
	unsigned int count = 0;
	int len=0;
	long int pos = ftell(in);
	//fseek(in, 0, SEEK_); ;// need for return to first symbol 
	do{
int posBegine = ftell(out);// need for check
		fread(bufChar, sizeof(char), SIZEPAK, out);
		//bufChar = readFileCh(in, bufChar);
		if (bufChar == ERRORPointer)
		{
			printf("ERROR createPak: return to calling function incorrect EMPTY, stop at created %u letter ",count);
			return EMPTY;
		}
		len = strlen(bufChar);
		
		charTemp = pack(bufChar);
		 int pos3 = ftell(out);
		fwrite(&charTemp, sizeof(unsigned char), 1, in);
		int posRecord = ftell(in);
		brushString(bufChar);/// fill wrong value
		*bufChar='\0',//for safety we put a pointer to '\0'
		charTemp = GARBAGE;
		count++;
	} while (len== SIZEPAK);// check the condition equality lenght  to SIZE f one char (in current event it is 8 bit)
	
/*	23.02 check wrong pack
if (len == SIZEPAK)
		*number0LastBit = EMPTY;
	else
		*number0LastBit = SIZEPAK-len;
		*/
	// free(bufChar);
	 return count;
}
void brushString(char *string)
{
	for (int i = 0;string[i] != '\0';i++)
		string[i] = '\0';
}
unsigned char pack(unsigned char buf[])
{
	union CODE code;

	code.byte.b1 = buf[0] - '0';
	code.byte.b2 = buf[1] - '0';
	code.byte.b3 = buf[2] - '0';
	code.byte.b4 = buf[3] - '0';
	code.byte.b5 = buf[4] - '0';
	code.byte.b6 = buf[5] - '0';
	code.byte.b7 = buf[6] - '0';
	code.byte.b8 = buf[7] - '0';
	return code.ch;
}

int checkMadeCodesUsually(PSYM*psyms)
{
	char ch = '\0';
	int i = 0;
	int countGap = 0;
	while (psyms[i] != NULL)
	{
		if(*(psyms[i]->code)==ch)
			countGap = i;
		i++;
	}

	return countGap;
}
int creatHederInfinalFile(FILE*fpMOL,int maxlengthArray,PSYM* psyms,int number0LastBit,ULL numberLetter)
{
	int pos1 = ftell(fpMOL);//
	int posEndHeader;// position of end header
	char*signature = "MOL";//signature. A set of multiple characters that allws you to set the file belongs to a specific format
	//int maxlengthArray; the number of unique charactrs.Contains the numberof rows in the table occurences.
	//PSYM* psyms //Table of occurence. Here stored records aboun symbols and frequencies. They need to be stored in binay without gaps.
	//number0LastBit//The length tail. File size .101 not always a multiple of 8, so at the end you you may see 'tail' of several bits. We add them to full byte and keep the actual length
	//numberLetter // The size of the sourse file.Need to control out of the box
	//The original file extentision. If the compressor changes expansion the original fille must then be restored.
	
	fwrite(signature, sizeof(char), 3, fpMOL);
	fwrite(&maxlengthArray, sizeof(int), 1, fpMOL);
	if( CHECK_FALL==recordPSYMtoString(maxlengthArray, psyms,fpMOL))
	{
		printf("ERROR recordPSYMtoString: exit from creatHederInfinalFile\n");
		return CHECK_FALL;
	}
	int pos = ftell(fpMOL);
	fwrite(&number0LastBit, sizeof(int), 1, fpMOL);
	pos1 = ftell(fpMOL);
	fwrite(&numberLetter, sizeof(ULL), 1, fpMOL);
	posEndHeader = ftell(fpMOL);//
	//fwrite(maxlengthArray, sizeof(int), 3, fpMOL);
	return posEndHeader;
}
int recordPSYMtoString(int maxlengthArray, PSYM* psyms,FILE*fpMOL)
{ 
	//int i;
	UC* stringChar=0x0;
	float*StringFloat=0x0;
	stringChar=createStringChar(maxlengthArray, psyms);
	StringFloat = createStringFloat(maxlengthArray, psyms);
	
	int pos1 = ftell(fpMOL);//
	fwrite(stringChar, sizeof(UC), maxlengthArray, fpMOL);
	fwrite(StringFloat, sizeof(float), maxlengthArray, fpMOL);
	int pos2 = ftell(fpMOL);

	return CHECK_OK;
}
UC*createStringChar(int maxlengthArray, PSYM* psyms)
{
	int i;
	UC* stringChar = 0x0;
	while (!stringChar)
	stringChar = (UC*)calloc(maxlengthArray+2, sizeof(UC));
for (i = 0;i < maxlengthArray;i++)
	{
		stringChar[i] = psyms[i]->ch;
	}
	stringChar[i] = '\0';
	return stringChar;
}
float*createStringFloat(int maxlengthArray, PSYM* psyms)
{
	int i;
	float* stringFloat = 0x0;
	char* stringChar = 0x0;
	while (!stringFloat)
		stringFloat = (float*)calloc(maxlengthArray + 2, sizeof(float));
	for (i = 0;i < maxlengthArray;i++)
	{
		stringFloat[i] = psyms[i]->freq;
	}
	stringFloat[i] = '\0';
	return stringFloat;
}
void brushAdresses(TSYM*psymsCode[])
{
	for (int i = 0;psymsCode[i] != NULL;i++)
	{
		psymsCode[i]->moreNode=NULL;
		psymsCode[i]->lessNode=NULL;
	}

}