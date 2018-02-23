#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "task2.h"
int main()
{
	FILE *fp, *fpsearch;
	UC buf[256];
	TSYM *root = NULL;
	 fp = fopen("begine.txt", "rt");
	fpsearch = fopen("The C.txt", "rt");
	root = (TSYM*)calloc(1, sizeof(TSYM));
	unsigned int i;
	if (!(fp || fpsearch))
	{
		perror("File: ");
		return 1;
	}

	for (i = 0; (fscanf(fp, "%s", buf) == 1);i++)
	{
		if (i == 0)
		{
			char *word = chomp(buf);
			strcpy(root->ch, word);
			root->count = 0;
			root->moreNode = NULL;
			root->lessNode = NULL;

		}
		else
			makeTree(root, buf, 50);

	}

	while (fscanf(fpsearch, "%s", buf) == 1)
	{
		searchTree(root, buf, 50);
	}
	printTree(root);
	fclose(fp);
	fclose(fpsearch);
	return 0;
}


/*�������� ���������, ������� ����������� �������� ��� ����� �� ����� �� � 
������� ������� ������������� �������� ���� �����. �������� ����� �������� � ��������� �����.
���������

������ ��������� �������������� � ��������� ������:

������� ��������� ���� � ��������� ������� ����� �.
����������� ���� � ��������� ������� � �������� �������� ������ � �������������� ������� ��� ���� ����.
����������� ������������� ���� � ������� ��������� � �������� �� ������� (��� ��������);
���������� ������ (�����) ������ � �������� ������;
���� ����� ��������� � ���������� � ������,����������� ������� ������������� ������� �����;
������

��������� ������ �������� � ���� ��������� �������:

chomp - �������� ������� ����� ������.
makeTree - �������� ������ �������� ����.
searchTree - ����� � ������ ������� ���������� ��������.
printTree - ������ ������ �������� ���� � �� ����������.
main - ������� ������� ���������.
��������� ��� �����: task2.h,task2.c,main2.c.
*/