#ifndef HASHTABLE_H

#include "node.h"

#define HASHTABLE_H

/*
   Define the hash table type.
*/
typedef struct _hashTable hashTable_t;

/*
   Creates  a new hash table.
*/
hashTable_t *createHash();

/*
    Destroy the hash table, and sets to NULL.
    Input: The hash table pointer pointer (hashTable_t **) to be destroyed.
    Output: If the hash passed is NULL, the function does nothing else the hash is destroyed.
*/
void destroyHash(hashTable_t **);

/*
    Puts a item in the Hash.
    Input: The hash table (hashTable_t *) and the item to be put.
    Only adds the frequency if the item has already been added.
    If one of the arguments passed is NULL, the function does nothing.
*/
void put(hashTable_t *, unsigned char);

/*
    Returns the node of a hash table.
    Input: The hash table (hashTable_t *) and the item to be get.
    Ouput:  If the hash is NULL or the item doesn't exist the funciton returns NULL
    else returns the node.
*/
node_t *get(hashTable_t *, unsigned char);

#endif
