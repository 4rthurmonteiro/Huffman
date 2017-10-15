#ifndef COMPRESS_H

#include "hashTable.h"
#include "huffmanTree.h"

#define COMPRESS_H

/*  Codifica os bytes de um arquivo para um novo arquivo com o mesmo nove adicionado o .huff no final.
    Entrada: O nome (char *) do arquivo a ser comprimido.
*/
void compress(char *);

/*  Pega a frequência de cada byte do arquivo e salva na tabela hash.
    Entrada: O arquivo (FILE *) e a tabela hash a ser salva as frequências (hashTablet_t *);
*/
void getFrequency(FILE *, hashTable_t *);

/*  Pega cada item da tabela hash e transforma em uma árvore estritamente binária.
    Entrada: A árvore binária (binaryTree_t *) onde os nós serão postos e a tabela hash (hashTablet_t *) onde os nós estão.
*/
void hashTree(huffmanTree_t *, hashTable_t *);

/*  Salva o arquivo usando a nova codificação para cada byte.
    Entrada: O arquivo original (FILE *), o arquivo final (FILE *), onde será salvo, a tabela hash (hashTablet_t *) que tem a nova codificação e por fim a árvore usada para gerar a nova codificação (binaryTree_t *).
*/
void saveCompress(FILE *, FILE *, hashTable_t *, huffmanTree_t *);

/* Mostra se o byte escolhido está setado.
  Entrada: tipo do byte (unsigned char) e a position do bit (int t).
*/
unsigned char bitSet(unsigned char, short int t);

#endif
