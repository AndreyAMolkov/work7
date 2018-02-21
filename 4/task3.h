#include<stdio.h>
#include<stdlib.h>
typedef unsigned long long int ULL;
typedef unsigned long int BASE_TYPE;

struct SYM//representation of the character
{
	BASE_TYPE ch;// ASCII-code
	BASE_TYPE count;
	float freq;// frequemcy of occurrency of the symbol in the file as a result dividing the number of this symbol by the total number of symbol. The range is from 0.0 to 1.0
	char code[256];//array for a new code - character array for stroning prefix code as a string from 0 and 1
	struct SYM *moreNode;// the left node in the tree
	struct SYM *lessNode;// the right node in the tree
};
typedef struct SYM TSYM;
typedef TSYM* PSYM;
PSYM makeTree(PSYM treeSym, BASE_TYPE ch, BASE_TYPE symbolPrevioyslyNode);
void countTotal2Tree(PSYM treeSym, ULL *totalCount,FILE*fpcheck);
void Tree2max(PSYM treeSym, BASE_TYPE *max);
int check2Tree(PSYM treeSym, ULL trueTotal);
void copyTree2Parr(PSYM treeSym, PSYM *syms);
int checkDataParray(PSYM *syms, ULL totalCount,PSYM treeSym);
int sort(PSYM *psyms,BASE_TYPE maxCount);
int findErrorCopy2psyms(PSYM treeSym, PSYM*syms);
int printArrayForCheck(PSYM*psyms);
void makeFrequencyForArray(PSYM *psyms, ULL totalCount);
int checkSumForFrequencyArray(PSYM*psyms);
void printArrayForScreen(PSYM*psyms);