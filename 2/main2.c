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
	
	unsigned int i;
	if ((fp==NULL || fpsearch==NULL))
	{
		perror("File: ");
		return 1;
	}

	for (i = 0; (fscanf(fp, "%s", buf) == 1);i++)
	{
		if (i == 0)
		{
			char *word = chomp(buf);
			while (root == NULL)
			{
				root = (TSYM*)calloc(1, sizeof(TSYM));
			}
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
	if(fp!=NULL)
		fclose(fp);
	fclose(fpsearch);
	return 0;
}


/*Написать программу, которая анализирует исходный код файла на языке Си и 
выводит таблицу встречаемости ключевых слов языка. Ключевые слова хранятся в отдельном файле.
Пояснение

Работа программы осуществляется в несколько этапов:

Вручную создается файл с ключевыми словами языка С.
Открывается файл с ключевыми словами и строится бинарное дерево с упорядоченными данными для всех слов.
Открывается анализируемый файл с текстом программы и читается по словами (или символам);
Полученные строки (слова) ищутся в бинарном дереве;
Если слово совпадает с хранящимся в дереве,увеличиваем счётчик встречаемости данного слова;
Состав

Программа должна включать в себя следующие функции:

chomp - удаление символа конца строки.
makeTree - создание дерева ключевых слов.
searchTree - поиск в дереве текущей комбинации символов.
printTree - печать списка ключевых слов и их количества.
main - главная функция программы.
Создаются три файла: task2.h,task2.c,main2.c.
*/