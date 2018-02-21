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
PSYM makeTree(PSYM treeSym, UC ch, UC symbolPrevioyslyNode);
void countTotal2Tree(PSYM treeSym, ULL *totalCount, FILE*fpcheck);
void Tree2max(PSYM treeSym, BASE_TYPE *max);
int check2Tree(PSYM treeSym, ULL trueTotal);
void copyTree2Parr(PSYM treeSym, PSYM *syms);
int checkDataParray(PSYM *syms, ULL totalCount, PSYM treeSym);
int sort(PSYM *psyms, BASE_TYPE maxCount);
int findErrorCopy2psyms(PSYM treeSym, PSYM*syms);
int printArrayForCheck(PSYM*psyms);
void makeFrequencyForArray(PSYM *psyms, ULL totalCount, int maxlengthArray);
int checkSumForFrequencyArray(PSYM*psyms);
void printArrayForScreen(PSYM*psyms);
TSYM* buildTree(TSYM *psym[], int N);
void countTotalStructInTree(PSYM treeSym, int *totalStructInfile);

//struct SYM* buildTree(TSYM *psym[], int N);
void desiredPositionPSYM(PSYM*psym,int N ,TSYM*temp);
void makeCodes(TSYM *root);
long int  createFile101(FILE*fp_in, PSYM* syms, FILE*fp101);
void copyParrToChange(PSYM*psyms, PSYM*psymsCode);// copy pointer to arr of poiters for build tree
unsigned char pack(unsigned char buf[]);
long int  createPak(FILE*in, FILE*out, int *number0LastBit);
char*readFileCh(FILE*fp,char*str);
int checkMadeCodesUsually(PSYM*psyms);
int creatHederInfinalFile(FILE*fpMOL, int maxlengthArray, PSYM* psyms, int number0LastBit, ULL numberLetter);
int recordPSYMtoString(int maxlengthArray, PSYM* psyms, FILE*fpMOL);
UC*createStringChar(int maxlengthArray, PSYM* psyms);
float*createStringFloat(int maxlengthArray, PSYM* psyms);