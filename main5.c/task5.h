#include<stdio.h>
#include<stdlib.h>
typedef unsigned long long int ULL;
typedef unsigned long int BASE_TYPE;
typedef unsigned char UC;
struct SYM//representation of the character
{
	unsigned char ch;// ASCII-code
	BASE_TYPE count;
	float freq;// frequemcy of occurrency of the symbol in the file as a result dividing the number of this symbol by the total number of symbol. The range is from 0.0 to 1.0
	char code[256];//array for a new code - character array for stroning prefix code as a string from 0 and 1
	struct SYM *moreNode;// the left node in the tree
	struct SYM *lessNode;// the right node in the tree
};
typedef struct SYM TSYM;
typedef TSYM* PSYM;
union CODE {
	unsigned char ch;
	struct {
		unsigned short b1 : 1;
		unsigned short b2 : 1;
		unsigned short b3 : 1;
		unsigned short b4 : 1;
		unsigned short b5 : 1;
		unsigned short b6 : 1;
		unsigned short b7 : 1;
		unsigned short b8 : 1;
	} byte;
};
typedef union CODE TCODE;