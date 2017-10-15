#ifndef HUFFMANTREE_H

#include "node.h"

#define HUFFMANTREE_H


typedef struct _huffmanTree huffmanTree_t;


huffmanTree_t *createBinaryTree();


void destroyBinaryTree(huffmanTree_t **);


short int numberOfNodes(huffmanTree_t *);


node_t *root(huffmanTree_t *);


void add(huffmanTree_t *, node_t *);


void forest(huffmanTree_t *);


node_t *getMin(huffmanTree_t *);


void setLeaf(huffmanTree_t *);


void saveHuffmanTree(huffmanTree_t *, FILE *);

#endif
