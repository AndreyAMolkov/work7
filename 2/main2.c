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


/*Написать программу, которая анализирует исходный код файла на языке Си и 
выводит таблицу встречаемости ключевых слов языка. Ключевые слова хранятся в отдельном файле.
Пояснение

Работа программы осуществляется в несколько этапов:

Вручную создается файл с ключевыми словами языка С.
Открывается файл с ключевыми словами и строится бинарное дерево с упорядоченными данными для всех слов.
Открывается анализируемый файл с текстом программы и читается по словами (или символам);
Полученные строки (слова) ищутся в бинарном дереве;
Еслисловосовпадаетсхранящимсявдереве,увеличиваемсчётчиквстре- чаемости данного слова;
Состав

Программа должна включать в себя следующие функции:

chomp - удаление символа конца строки.
makeTree - создание дерева ключевых слов.
searchTree - поиск в дереве текущей комбинации символов.
printTree - печать списка ключевых слов и их количества.
main - главная функция программы.
Создаются три файла: task2.h,task2.c,main2.c.
*/