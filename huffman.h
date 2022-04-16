#define CHARSIZE 256
#define MAX_CODE_LEN 256
#define INPUT_FILE_ERROR 1
#define ENC_FILE_ERROR 2
#define OUTPUT_FILE_ERROR 3
#define MAX_HEAPSIZE_ERROR 4
#define WRITE_ERROR 5
#define READ_ERROR 6

typedef struct heapElement HeapElement;
typedef struct treeNode TreeNode;

void printHeap(HeapElement **heap, unsigned int heapSize);
HeapElement *insertHeapElement(unsigned val, char c, TreeNode* node, HeapElement **heap, unsigned *heapSize, unsigned cap);
TreeNode *createTreeFromHeap(HeapElement **heap, unsigned int *heapSize, unsigned int cap);
void writeHeap(FILE *fp, HeapElement **heap, unsigned heapSize);
void readHeap(FILE *fp, HeapElement **heap, unsigned *heapSize, unsigned cap);

TreeNode *createTreeNode(char c, TreeNode *left, TreeNode *right);
void getHuffmanCodes(TreeNode *node, char codes[CHARSIZE][MAX_CODE_LEN], char *code);
TreeNode *getLeft(TreeNode *node);
TreeNode *getRight(TreeNode *node);
char getChar(TreeNode *node);
void printTree(TreeNode *root);

void encode(char *ogFilename, char *encFilename);

void decode(char *encFilename, char *decFilename);
