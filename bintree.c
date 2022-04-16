#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "huffman.h"

struct treeNode {
    char c;
    struct treeNode *left, *right;
};

TreeNode *createTreeNode(char c, TreeNode *left, TreeNode *right) {
    TreeNode *p;

    p = malloc(sizeof(TreeNode));
    p->c = c;
    p->left = left;
    p->right = right;
    return p;
}

void getHuffmanCodes(TreeNode *node, char codes[CHARSIZE][MAX_CODE_LEN], char *code) {
    char codeleft[MAX_CODE_LEN], coderight[MAX_CODE_LEN];

    if (node->left != NULL) {
        strcpy(codeleft, code);
        strcat(codeleft, "0");
        getHuffmanCodes(node->left, codes, codeleft);
    }
    if (node->right != NULL) {
        strcpy(coderight, code);
        strcat(coderight, "1");
        getHuffmanCodes(node->right, codes, coderight);
    }
    if ((node->right == NULL) && (node->left == NULL)) {
        strcpy(codes[node->c],code);
    }
}

int getDepth(TreeNode *root) {
    int leftDepth, rightDepth, depth;

    if (root == NULL)
        return 0;
    leftDepth = 1 + getDepth(root->left);
    rightDepth = 1 + getDepth(root->right);
    depth = leftDepth > rightDepth ? leftDepth : rightDepth;
    return depth;
}

void printDepth(TreeNode *root, int depth) {
    if (root != NULL) {
        if (depth == 0) {
            switch (root->c) {
                case '\n':
                    printf("\\n ");
                    break;
                case ' ':
                    printf("\\s ");
                    break;
                default:
                    printf("%c ", root->c);
            }
        } else {
            printDepth(root->left, depth-1);
            printDepth(root->right, depth-1);
        }
    }
}

TreeNode *getLeft(TreeNode *node) {
    return node->left;
}

TreeNode *getRight(TreeNode *node) {
    return node->right;
}

char getChar(TreeNode *node) {
    return node->c;
}

void printTree(TreeNode *root) {
    int i, depth;

    depth = getDepth(root);
    for (i=0; i<depth; i++) {
        printDepth(root, i);
        printf("\n");
    }
}

