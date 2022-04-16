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

## Credits

This project is a part of the Image Compression course of PEE/Coppe and so
I would like to thank professor Eduardo A.B. da Silva.

## License 
This project is licensed under the GNU General Public License v3.0