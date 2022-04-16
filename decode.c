#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "huffman.h"

void readHuffmanByte(unsigned char byte, TreeNode *root, TreeNode **current, FILE *fp) {
    int i;
    unsigned char bit;

    for (i = 0; i < 8; i++){
        bit = (byte & 128) >> 7;
        if (bit == 1) {
            *current = getRight(*current);
        } else {
            *current = getLeft(*current);
        }
        byte = byte << 1;
        if ((getRight(*current) == NULL) && (getLeft(*current) == NULL)) {
            putc((int) getChar(*current), fp);
            *current = root;
        }
    }
}

void decode(char *encFilename, char *decFilename) {
    int capacity = CHARSIZE;
    int c;
    unsigned heapSize = 0;
    HeapElement *heap[CHARSIZE];
    TreeNode *huffmanTree, *current;
    FILE *encFile, *decFile;

    if ((encFile = fopen(encFilename, "rb")) == NULL)
        exit(ENC_FILE_ERROR);
    if ((decFile = fopen(decFilename, "w")) == NULL)
        exit(OUTPUT_FILE_ERROR);
    readHeap(encFile, heap, &heapSize, capacity);
    huffmanTree = createTreeFromHeap(heap, &heapSize, capacity);
    current = huffmanTree;
    while ((c = getc(encFile)) != EOF)
        readHuffmanByte((unsigned char) c, huffmanTree, &current, decFile);
    fclose(encFile);
    fclose(decFile);
}

//int main() {
//    clock_t begin, end;
//    double delta;
//    char *encFilename = "biblia-cod.txt", *decFilename = "biblia-dec.txt";
//
//    begin = clock();
//    decode(encFilename, decFilename);
//    end = clock();
//    delta = (double) (end - begin) / CLOCKS_PER_SEC;
//    printf("Decoding time: %f seconds", delta);
//
//    return 0;
//}