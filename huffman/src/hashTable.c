#include "inc/hashTable.h"

/*
   A hash table with nodes.
*/
struct _hashTable {

	node_t **table;
};

/*
    Creates  a new hash table.

		MORE ABOUT THIS FUNCTION: open "hashTable.h" file.
*/
hashTable_t *createHash(){

	hashTable_t *new_hash = (hashTable_t *) malloc(sizeof(hashTable_t)); // Allocates memory to the new_hash

	new_hash->table = (node_t **) calloc(256, sizeof(node_t *)); // Allocates a table with 256 spaces, because its the max size of the hash.

  short int i; // loop aux
	for (i = 0; i < 256; i++) { // pointers all the 256 nodes to NULL.
		new_hash->table[i] = NULL;
	}

	return new_hash; // returns a hash table with 256 node_t "spaces" inside it.
}

/*
    Destroy the hash table, and sets to NULL.

		MORE ABOUT THIS FUNCTION: open "hashTable.h" file.
*/
void destroyHash(hashTable_t **hash){

	if ((*hash) != NULL) { // checks if the hash is not null.

		free((*hash)->table); // free memory.

		free((*hash)); // free memory hash.

		(*hash) = NULL; // at the end the fuction pointer the hash to NULL.
	}
}

/*
    Puts a item in the Hash.

		MORE ABOUT THIS FUNCTION: open "hashTable.h" file.
*/
void put(hashTable_t *hash, unsigned char item){

	if (hash != NULL) { // checks if the hash is not null.

		if (hash->table[item] == NULL) {  // If the item isn't in the hash table, it's create a new with frequency 1.
			hash->table[item] = createNode(item, 1, NULL, NULL); // creates a new node with frequency 1 and the children to NULL.
		} else {
			freqPP(hash->table[item]); // juts updates the frequency (adding 1).
		}
	}
}

/*
    Returns the node of a hash table.

		MORE ABOUT THIS FUNCTION: open "hashTable.h" file.
*/
node_t *get(hashTable_t *hash, unsigned char item){

	if (hash != NULL) { // checks if the hash is not null.

		return hash->table[item]; // return the item.
	} else {

		return NULL; // the hash is NULL.
	}
}
