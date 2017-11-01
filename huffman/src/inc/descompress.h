#ifndef DESCOMPRESS_H

#include "huffmanTree.h"

#define DESCOMPRESS_H


/*
   Descompress the Bytes of a file and save it to a new file with the same name
   without ".huff" at the end.
   Input: The name (char *) of the file to be descompressed.
   Output: If the string passed is NULL or the file passed not exist, the function does nothing else
   the funciton will descompress the file with ".huff" extension and erase the ".huff" extension.
   Returns nothing because is a void function.
 */

void descompress(char *);

/*
    This function catch/build the tree which was created to compress the file.
    Input: The tree (huffmanTree_t *) to build and the source file (FILE *).
    Output: If one or more arguments passed is NULL, the function does nothing else
    the function will catch or build the binary tree.
    Returns nothing because is a void function.
 */
void getBinaryTree(huffmanTree_t *, FILE *, unsigned short int);

/*
    Saves the file using the standard codes.
    Input: The compress file (FILE *), the final file (FILE *) which will save and the tree with the huffman codes.
    Output: If one or more arguments passed is NULL, the function does nothing else
    the function will save the standard codes in the final file.
    Returns nothing because is a void function.
 */
void saveDecompress(FILE *, FILE *, huffmanTree_t *, unsigned short int);

/*
    Returns true if the i-th bit of a Byte is set and false otherwise.
    Input: The base byte (unsigned char) and the position of the bit that you want to
    know if it is set (short int), 0 for the first one on the right and 7 for the first one on the left.
    Output: true if is set and false if not.
 */
bool isBitSet(unsigned char, short int);

#endif
