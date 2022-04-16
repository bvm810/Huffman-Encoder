#include <stdio.h>
#include <time.h>
#include "huffman.h"

int main() {
    clock_t begin, end;
    double delta;
    char *ogFilename = "biblia.txt", *encFilename = "biblia-cod.txt", *decFilename = "biblia-dec.txt";

    begin = clock();
    encode(ogFilename, encFilename);
    end = clock();
    delta = (double) (end - begin) / CLOCKS_PER_SEC;
    printf("Coding time: %f seconds\n", delta);

    begin = clock();
    decode(encFilename, decFilename);
    end = clock();
    delta = (double) (end - begin) / CLOCKS_PER_SEC;
    printf("Decoding time: %f seconds", delta);

    return 0;
}