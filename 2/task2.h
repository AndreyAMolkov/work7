typedef unsigned char UC;
struct NODE
{
	UC word[256];
	unsigned long count;
	struct NODE *left;
	struct NODE *right;
};
typedef struct NODE TNODE;
typedef TNODE* PNODE;
PNODE makeTree(PNODE root, UC *word, UC condition);
PNODE searchTree(PNODE root, UC *word, UC condition);
void printTree(PNODE root);
void chomp(UC*p);