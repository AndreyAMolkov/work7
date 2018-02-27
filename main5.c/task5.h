
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

PSYM*readHederInfinalFile(FILE*fpMOL, int *maxlengthArray, TSYM* psyms[], int *number0LastBit, ULL*sizeInputFile, UC**extension);
PSYM*recordStringtoPSYM(int maxlengthArray, TSYM* psyms[], FILE*fpMOL);
PSYM*recordPsymsChar(int maxlengthArray, TSYM* psyms[], UC*stringChar);
PSYM*recordPsymsFloat(int maxlengthArray, TSYM* psyms[], float*stringFloat);
struct SYM* buildTree(TSYM *psym[], int N);
void desiredPositionPSYM(PSYM*psym, int N, TSYM*temp);
void makeCodes(TSYM *root);
long int readPak(FILE*in, FILE*out, int number0LastBit);
int unpack(char buf,FILE*fp);
int createFp(FILE*fp101, TSYM*root, FILE*fp);
void printArrayForScreen(PSYM*psyms);
int printArrayForCheck(PSYM*psyms);
void copyParrToChange(PSYM*psyms, PSYM*psymsCode);
ULL findSizeInputFile(FILE*fp);
UC*createNameFile(UC*string, UC*newExtension, UC*flagCopy);
int brushPointersArray(PSYM*parr[]);
ULL SizeFile(FILE*fp);