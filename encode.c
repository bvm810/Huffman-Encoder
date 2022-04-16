#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "huffman.h"

// init vector with probabilities of each char
void countChars(int *count, FILE *fp) {
    int c, i;

    // initialize count array
    for (i = 0; i < CHARSIZE; i++)
        count[i] = 0;
    // count chars in file
    while((c = getc(fp)) != EOF) {
        count[c]++;
    }
}

void createCharHeap(int *count, HeapElement **heap, unsigned *heapSize, unsigned capacity) {
    int c;

    for (c = 0; c < CHARSIZE; c++) {
        if (count[c] > 0) insertHeapElement(count[c], (char) c,NULL, heap, heapSize, capacity);
    }
}

void writeHuffmanByte(FILE *fp, char codes[CHARSIZE][MAX_CODE_LEN], char c, unsigned char *buffer, char *bufferSize) {
    char *code;

    for (code = codes[c]; *code != '\0'; code++) {
        *buffer = *buffer | (*code - '0');
        (*bufferSize)++;
        if (*bufferSize == 8) {
            putc(*buffer, fp);
            *buffer = 0;
            *bufferSize = 0;
        }
        *buffer = *buffer << 1;
    }
}

double getAvgCodeLen(int count[CHARSIZE], char codes[CHARSIZE][MAX_CODE_LEN]) {
    double charCount = 0, avg = 0, reduction = 0;
    int i;

    for (i = 0; i < CHARSIZE; i++) {
        if (count[i] != 0) {
            charCount += count[i];
            avg += (double) count[i] * (double) strlen(codes[i]);
        }
    }
    avg = avg / charCount;
    reduction = 100 * (8 - avg)/8;
    printf("Average code length: %f --- reduction of %f%%\n", avg, reduction);
    return avg;
}

void encode(char *ogFilename, char *encFilename) {
    int count[CHARSIZE];
    int capacity = CHARSIZE;
    unsigned heapSize = 0;
    HeapElement *heap[CHARSIZE];
    TreeNode *huffmanTree;
    FILE *ogFile, *encFile;
    char bufferSize, c;
    unsigned char buffer;
    char codes[CHARSIZE][MAX_CODE_LEN];

    if ((ogFile = fopen(ogFilename, "r")) == NULL)
        exit(INPUT_FILE_ERROR);
    if ((encFile = fopen(encFilename, "wb")) == NULL)
        exit(ENC_FILE_ERROR);
    countChars(count, ogFile);
    createCharHeap(count, heap, &heapSize, capacity);
    writeHeap(encFile, heap, heapSize);
    huffmanTree = createTreeFromHeap(heap, &heapSize, capacity);
    getHuffmanCodes(huffmanTree, codes, "\0");
    getAvgCodeLen(count, codes);
    fseek(ogFile, 0, SEEK_SET);
    buffer = 0;
    bufferSize = 0;
    while ((c = (char) getc(ogFile)) != EOF)
        writeHuffmanByte(encFile, codes, c, &buffer, &bufferSize);
    fclose(ogFile);
    fclose(encFile);
}

//int main() {
//    clock_t begin, end;
//    double delta;
//    char *ogFilename = "biblia.txt", *encFilename = "biblia-cod.txt";
//
//    begin = clock();
//    encode(ogFilename, encFilename);
//    end = clock();
//    delta = (double) (end - begin) / CLOCKS_PER_SEC;
//    printf("Coding time: %f seconds\n", delta);
//
//    return 0;
//}