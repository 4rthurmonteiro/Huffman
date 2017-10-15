#include "inc/hashTable.h"



struct _hashTable {

	node_t **table;
};

hashTable_t *createHash(){

	hashTable_t *new_hash = (hashTable_t *) malloc(sizeof(hashTable_t));


	new_hash->table = (node_t **) calloc(256, sizeof(node_t *));


   short int i;
	for (i = 0; i < 256; i++) {
		new_hash->table[i] = NULL;
	}


	return new_hash;
}

void destroyHash(hashTable_t **hash){

	if ((*hash) != NULL) {

		free((*hash)->table);

		free((*hash));

		(*hash) = NULL;
	}
}

void put(hashTable_t *hash, unsigned char item){

	if (hash != NULL) {

		if (hash->table[item] == NULL) {
			hash->table[item] = createNode(item, 1, NULL, NULL);
		} else {

			freqPP(hash->table[item]);
		}
	}
}

node_t *get(hashTable_t *hash, unsigned char item){

	if (hash != NULL) {

		return hash->table[item];
	} else {

		return NULL;
	}
}
