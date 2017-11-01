#ifndef COMPRESS_H

#include "hashTable.h"
#include "huffmanTree.h"

#define COMPRESS_H

/*
    Compress the bytes of a file and save it in a file with the same name added the ".huff" extension.
    Input: The file name (char *) to be compressed.
    Output: If one or more arguments passed is NULL, the function does nothing else
    the function will compress the file and adds ".huff" extension.
    Returns nothing because is a void function.
*/
void compress(char *);

/*
    Catch the frequency of each byte of a file and saves it in a hash table.
    Input: The source file (FILE *) and the hash table to save the frequency.
    Output: If one or more arguments passed is NULL, the function does nothing else
    save the frequencies bytes in the hash.
    Returns nothing because is a void function.
*/
void getFrequency(FILE *, hashTable_t *);

/*
    Catch each item from the hash table and transforms it in a tree strictly binary tree.
    Input: The tree (huffmanTree_t *) to be used and the hash table (hashTable_t *) with the nodes.
    Output: If one or more arguments passed is NULL, the function does nothing else transforms the hash table elements
    in a strictly binary tree.
    Returns nothing because is a void function.
*/
void hashTree(huffmanTree_t *, hashTable_t *);

/*  Salva o arquivo usando a nova codificação para cada byte.
    Entrada: O arquivo original (FILE *), o arquivo final (FILE *), onde será salvo, a tabela hash (hashTablet_t *) que tem a nova codificação e por fim a árvore usada para gerar a nova codificação (binaryTree_t *).
    Saves the file with the new codes.
    Input: The source file (FILE *), the huffman file (FILE *),
    the hash table (hashTable_t *) that hash the new codes and the tree used to generate the new codes.
    Output: If one or more arguments passed is NULL, the function does nothing else save the new codes in the source file.
    Returns nothing because is a void function.
*/
void saveCompress(FILE *, FILE *, hashTable_t *, huffmanTree_t *);

/*
   Shows if the byte picked was set.
   Input: The byte type (unsigned char) and the position (short int).
   Output: Returns the bit int the position picked.
*/
unsigned char bitSet(unsigned char, short int t);

#endif
