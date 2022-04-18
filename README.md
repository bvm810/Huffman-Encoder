# Huffman Encoder

## Description
This repo contains a simple implementation of a text Huffman encoder using C.
The encoder is created using a character based model, meaning that the 
frequencies of each char in the text file given as input are calculated
and used as the encoder's symbols.

This implementation depends only on the C standard library, and it offers
reasonable performance thanks to the tree structure that can be used for
Huffman encoding.

## Usage
As of today, the main function simply encodes and decodes an input text
file, and computes average code length and coding/decoding time.

The main function has not been adapted yet to accept command-line 
arguments using `argc` and `argv`, so the filenames are still hard coded
on `main.c`.
```
int main() {
    char *ogFilename = <original file name>; 
    char *encFilename = <encoded file name>; 
    char *decFilename = <decoded file name>;

    \\ rest of file 
```

After changing this, you should be able to compile the code and Huffman
encode the desired files with the resulting binary file.

## Implementation

Huffman coding can be implemented in O(n log n) using a min heap data 
structure, which is nothing more than a tree that satisfies the property
that the children C of any node P must have a *key* value smaller than or
equal to the *key* of P.

```
\\ example of min heap
                                    10
                                  /    \
                                17      13
                               /  \
                             20   50
```


The advantage of using this structure is that removing the smallest
element from the heap is a O(log n) operation, meaning that, once the 
alphabet is inserted into the heap, the procedure of grouping the less
likely elements to create the Huffman code can be done in O(n log n)
time.

In this implementation, first the input document is scanned to count the
number of occurences of each char, including `\n`, `\r`, and whitespaces.
Then, each one of the symbols present in the document in included in the
min heap, which is later used to create a Huffman tree from which all 
codes can be extracted.

The codes are stored in an array where the `char` value is used as an index, 
and each character in the file is then replaced by its Huffman code. In this
step, a buffer is used to group codes, once that there may be codes smaller
than a byte.

A header is also added with the count for each symbol, and the decoder
uses this information to recreate the min heap and Huffman tree that were
used by the encoder. 

After the tree is created in the receiving side, the
bits in the file are read incrementally: each `1` moves a pointer from 
the current node in the tree to the right, and each `0` moves this same
pointer to the left, until a leaf node is reached. When this happens, a
character is decoded and written into the decoded file.

The `pqueue.c`, and `bintree.c` files have generic implementations of a
heap and a binary tree, and have functions that are called by `encode.c`
and `decode.c` to encode and decode the input file. The latter two also 
have helper functions to read and write Huffman code bytes using bitwise
operations to go around the minimal variable size of a byte in C.

## Credits

This project is a part of the Image Compression course of PEE/Coppe and so
I would like to thank professor Eduardo A.B. da Silva.

## License 
This project is licensed under the GNU General Public License v3.0