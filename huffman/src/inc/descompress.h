#ifndef DESCOMPRESS_H

#include "huffmanTree.h"

#define DESCOMPRESS_H


void descompress(char *);

/*  Essa função pega ou forma a árvore que fou usada para codificar o arquivo.
    Entrada: A árvore binária (binaryTree_t *) para formar e o arquivo (FILE *) onde ela está.
 */
void getBinaryTree(huffmanTree_t *, FILE *, unsigned short int);

/*  Salva o arquivo usando os bytes original.
    Entrada: Arquivo codificado (FILE *), o arquivo final (FILE *), onde sera salvo e a árvore usada para gerar os códigos
    de cada byte codificado.
 */
void saveDecompress(FILE *, FILE *, huffmanTree_t *, unsigned short int);

/*  Retorna true se o bit está setado.
    Entrada: Um unsigned char e a posição a ser consultada.
 */
bool isBitSet(unsigned char, short int);

#endif
