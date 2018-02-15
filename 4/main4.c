#include<stdio.h>
#include<stdlib.h>
#define CHECK_OK 0
#define CHECK_FALL 1
#define MAX_LENGHT_STRING 20
int conditionRecordInline(char charSymbol)
{
	int symbol = charSymbol;
	switch (symbol)
	{
	case 44:// for ',' - ASCII
		break;
	case 34:// for ' " ' - ASCII
		break;
	case 92://for '\ ' - ASCII
		break;
	default:
	{return CHECK_FALL;}
	}
	return CHECK_OK;
}
char*fillBox(char*from, char* to)
{
	int iFrom;
	int iTo;

	for (iFrom = 0, iTo = 0; from[iFrom] != '\0' || iFrom > MAX_LENGHT_STRING;iFrom++)// if caught NULL  then go to from fillBox
	{
		if (conditionRecordInline(from[iFrom]) == CHECK_FALL)// if symbol found go to next loop
			if (to[iTo] == '\0')// the field conteined only NULL
				to[iTo++] = from[iFrom];
			else
			{
				to[iTo] = '\0';// close string's field
				return to;// exit from fillBox, because fild is full
			}
	}
	if (iFrom == 0)
	{
		printf("Attention: trying to write to an information's structure the empty data %s", from);
	}
	return *to;
}

main()
{

	char*from = "gather";
	char*to=(char*)calloc(3,sizeof(char));
	to=fillBox(from, to);

	return 0;
}