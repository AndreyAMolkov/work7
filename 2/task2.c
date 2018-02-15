#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "task2.h"
#include<ctype.h>
FILE *fpOut; 
void chomp(UC*p)
{
	while (isalpha(*(p++)))
		*(p-1)=tolower(*(p-1));

	*(--p) = NULL;
}
PNODE searchTree(PNODE root, UC *word,UC condition)
{
	
	if (root == NULL)
		return root;
	else if (strcmp(root->word, word) == 0)
		root->count++;
	else if ((*(root->word) - condition)>0)
		root->left=searchTree(root->left, word, condition / 2);
	else 
		root->right=searchTree(root->right, word, condition / 2);
	return root;
}
PNODE makeTree(PNODE root, UC *word,UC condition)
{
	
	if (root == NULL)
	{
		root = (PNODE)malloc(sizeof(TNODE));
		strcpy(root->word, word);
		root->count = 0;
		root->left = root->right = NULL;
		return root;
	}
	else if (strcmp(root->word, word) == 0)
	{
		return root;
	}
	else if ((*word - condition)>0)
			root->left= makeTree(root->left, word, condition/2);
		else
		root->right= makeTree(root->right, word, condition/2);

	return root;
	
}

void printTree(PNODE root)
{
	
	if (root->left)
		printTree(root->left);
	printf("%s-%lu\n", root->word,root->count);
	fprintf(fpOut, "%s\n", root->word);
	if (root->right)
		printTree(root->right);
}

