#include <stdlib.h>
#include <stdio.h>
#include "huffman.h"

struct heapElement {
    unsigned int val;
    char c;
    TreeNode *node;
};

HeapElement *createHeapElement(unsigned int val, char c, TreeNode *node) {
    HeapElement *p;

    p = malloc(sizeof(HeapElement));
    p->val = val;
    p->c = c;
    if (node == NULL) {
        p->node = createTreeNode(p->c, NULL, NULL);
    } else {
        p->node = node;
    }
    return p;
}

int parent(int i) {
    return (i-1)/2;
}

int leftChild(int i) {
    return (2 * i + 1);
}

int rightChild(int i) {
    return (2 * i + 2);
}

void swap(HeapElement **x, HeapElement **y) {
    HeapElement *temp = *x;
    *x = *y;
    *y = temp;
}

void printHeap(HeapElement **heap, unsigned int heapSize) {
    int i;

    for(i=0; i<heapSize; i++) {
        switch (heap[i]->c) {
            case '\n':
                printf("\\n:%d ", heap[i]->val);
                break;
            case ' ':
                printf("\\s:%d ", heap[i]->val);
                break;
            default:
                printf("%c:%d ", heap[i]->c, heap[i]->val);
                break;
        }
    }
    printf("\n");
}

// ensure heap property starting from root index
void adjust(int rootIdx, HeapElement **heap, unsigned int heapSize) {
    int left, right;
    int smallest = rootIdx;
    char done = 0;

    while(!done) {
        left = leftChild(rootIdx);
        right = rightChild(rootIdx);
        if ((left < heapSize) && (heap[left]->val < heap[smallest]->val))
            smallest = left;
        if ((right < heapSize) && (heap[right]->val < heap[smallest]->val))
            smallest = right;
        if (smallest != rootIdx) {
            swap(&heap[smallest], &heap[rootIdx]);
            rootIdx = smallest;
        } else {
            done = 1;
        }
    }
}

HeapElement *popMin(HeapElement **heap, unsigned int *heapSize) {
    HeapElement *root;

    if (*heapSize <= 0) // empty heap
        return NULL;
    root = heap[0];
    *heapSize = *heapSize - 1;
    if (*heapSize != 0) {
        heap[0] = heap[*heapSize];
        adjust(0, heap, *heapSize);
    }
    heap[*heapSize] = NULL;
    return root;
}

HeapElement *insertHeapElement(unsigned val, char c, TreeNode* node, HeapElement **heap, unsigned *heapSize, unsigned cap) {
    int i;

    // if heap is full return NULL pointer
    if (*heapSize == cap)
        return NULL;
    // else insert at the first available position then fix heap property
    heap[*heapSize] = createHeapElement(val, c, node);
    *heapSize = *heapSize + 1;
    i = (int) *heapSize - 1;
    while((i != 0) && (heap[parent(i)]->val > heap[i]->val)) {
        swap(&heap[i], &heap[parent(i)]);
        i = parent(i);
    }
    return heap[i];
}

TreeNode *createTreeFromHeap(HeapElement **heap, unsigned int *heapSize, unsigned int cap) {
    HeapElement *min1, *min2, *last;
    TreeNode *top, *root;

    while (*heapSize > 1) {
        min1 = popMin(heap, heapSize);
        min2 = popMin(heap, heapSize);
        top = createTreeNode('$', min1->node, min2->node);
        insertHeapElement(min1->val + min2->val, '$', top, heap, heapSize, cap);
        free(min1);
        free(min2);
    }
    last = popMin(heap, heapSize);
    root = last->node;
    free(last);
    return root;
}

// this function assumes that the maximum heapSize is 256, which equals a char
void writeHeap(FILE *fp, HeapElement **heap, unsigned heapSize) {
    int i;

    if (heapSize > CHARSIZE)
        exit(MAX_HEAPSIZE_ERROR);
    if (putc((int) heapSize, fp) == EOF)
        exit(WRITE_ERROR);
    for (i = 0; i < heapSize; i++) {
        if (putc(heap[i]->c, fp) == EOF)
            exit(WRITE_ERROR);
        if(fwrite(&heap[i]->val, sizeof(int), 1, fp) != 1)
            exit(WRITE_ERROR);
    }
}

// this function assumes that the maximum heapSize is 256, which equals a char
void readHeap(FILE *fp, HeapElement **heap, unsigned *heapSize, unsigned cap) {
    int i, c, val, finalHeapSize;

    if ((finalHeapSize = getc(fp)) == EOF)
        exit(READ_ERROR);
    if (finalHeapSize > CHARSIZE)
        exit(MAX_HEAPSIZE_ERROR);
    for (i = 0; i < finalHeapSize; i++) {
        if ((c = getc(fp)) == EOF)
            exit(READ_ERROR);
        if (fread(&val, sizeof(int), 1, fp) != 1)
            exit(READ_ERROR);
        if (insertHeapElement(val, (char) c, NULL, heap, heapSize, cap) == NULL)
            exit(READ_ERROR);
    }
    if (finalHeapSize != *heapSize)
        exit(READ_ERROR);
}