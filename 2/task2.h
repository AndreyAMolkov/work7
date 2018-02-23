#include<stdio.h>
#include<stdlib.h>
typedef unsigned long long int ULL;
typedef unsigned long int BASE_TYPE;
typedef unsigned char UC;
#define CHECK_OK 0
#define CHECK_FALL 1
#define GARBAGE '\0'  //selection is made for string
#define MAX_LENGHT_STRING 255
#define POINTER_FALL  0

struct SYM//representation of the character
{
	UC ch[MAX_LENGHT_STRING];// ASCII-code
	unsigned int count;
	struct SYM *moreNode;// the left node in the tree
	struct SYM *lessNode;// the right node in the tree
};
typedef struct SYM TSYM;
typedef TSYM* PSYM;
TSYM *makeTree(TSYM *treeSym, UC *word, UC Node);
int searchTree(TSYM *treeSym, UC *word, UC node);
void printTree(TSYM *root);
char*chomp(char from[]);
int conditionRecordInline(char charSymbol);