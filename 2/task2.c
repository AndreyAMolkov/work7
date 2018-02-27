#define _CRT_SECURE_NO_WARNINGS
#include "task2.h"
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

int searchTree(TSYM *treeSym, UC *word,UC node)
{
	word = chomp(word);
	UC*treeCh = 0x0;
	
	
	while (treeSym != NULL)
	{
		treeCh = treeSym->ch;
		if (strcmp(word, treeCh) == CHECK_OK)
		{
			++treeSym->count;
			return 0;
		}

	else if ((*word-node) > 0)
		treeSym = treeSym->moreNode;
	else
		treeSym = treeSym->lessNode;
		node = *treeCh;
	}
}
int compareString(char* sourseString, char* xString, int maxLenght)
{
	int iSourse, iXstring;
	iSourse =0;
	int lengthXstring = strlen(xString);
	int lengthSourse = strlen(sourseString);
	
		if (sourseString[iSourse] == *xString)
			for (iXstring = 0;iXstring < maxLenght;iXstring++, iSourse++)
			{
				if (xString[iXstring] == '\0')// condition for succsessfuly
					return CHECK_OK;
				if (xString[iXstring] != sourseString[iSourse])// condition for fall
					break;// search next in this string
			}

	return CHECK_FALL;
}
TSYM *makeTree(TSYM *treeSym, UC *word, UC Node)
{
	if (word == NULL)
		return POINTER_FALL;
	long int rezult = 0;
	word = chomp(word);
	UC*treeCh = 0x0;
	treeCh=treeSym->ch;
	if (treeSym == NULL)
	{
		while(treeSym==NULL)
		treeSym = (TSYM*)calloc(1,sizeof(TSYM));

		strcpy(treeSym->ch, word);
		treeSym->count = 0;
		treeSym->moreNode = NULL;
		treeSym->lessNode = NULL;
		return treeSym;
	}
	else if (compareString(treeCh, word, MAX_LENGHT_STRING) == CHECK_OK)
		return treeSym;
	else if ((rezult = (*word - Node))>0)
			treeSym->moreNode = makeTree(treeSym->moreNode, word, *treeCh);
		 else
			treeSym->lessNode = makeTree(treeSym->lessNode, word, *treeCh);

	return treeSym;

}

void printTree(TSYM *root)
{
	
	if (root->moreNode)
		printTree(root->moreNode);
	printf("%s-%u\n", root->ch, root->count);

	if (root->lessNode)
		printTree(root->lessNode);
	//printf("%s-%u\n", root->ch, root->count);

}
char*chomp(char from[])
{

	int lenFrom = strlen(from);
	int i;
	if (from == POINTER_FALL)
	{
		printf("Error prepareForLetter: error movi pointer to letter for %s", from);
		return POINTER_FALL;// error error
	}
	for (i = 0;i < lenFrom;i++)
		if (conditionRecordInline(from[i]) == CHECK_OK)//didn't find characters other than letters or numbers
			from[i] = '\0';
	return from;
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

