#ifndef HASHTABLE_H

#include "node.h"

#define HASHTABLE_H


typedef struct _hashTable hashTable_t;


hashTable_t *createHash();


void destroyHash(hashTable_t **);


void put(hashTable_t *, unsigned char);


node_t *get(hashTable_t *, unsigned char);

#endif
