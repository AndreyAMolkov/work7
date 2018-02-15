#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "task2.h"
extern FILE *fpOut;

//int main(int argc, UC *argv)
int main()
{
	UC *p = 0x0;
	FILE *fp, *fpsearch;
	extern FILE *fpOut;
	UC buf[256];
	PNODE root = NULL;
	//fp = fopen(argv[1], "rt");
	 fp = fopen("begine.txt", "rt");
	fpOut=fopen("result.txt", "w");
	fpsearch = fopen("The C.txt", "rt");
	if (!fp || !fpOut) {
		perror("File: ");
		return 1;
	}
	while (fscanf(fp, "%s", buf) == 1)
	{
		chomp(buf);
		if (!buf)
			p=buf;
		root = makeTree(root, buf, 'Z');
	}
	while (fscanf(fpsearch, "%s", buf) == 1)
	{
		chomp(buf);
		root = searchTree(root, buf, 'Z');
	}
	printTree(root);
	fclose(fp);
	fclose(fpOut);

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
������������������������������������,�����������������������- �������� ������� �����;
������

��������� ������ �������� � ���� ��������� �������:

chomp - �������� ������� ����� ������.
makeTree - �������� ������ �������� ����.
searchTree - ����� � ������ ������� ���������� ��������.
printTree - ������ ������ �������� ���� � �� ����������.
main - ������� ������� ���������.
��������� ��� �����: task2.h,task2.c,main2.c.
*/