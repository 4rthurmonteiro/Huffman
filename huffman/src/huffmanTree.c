#include "inc/huffmanTree.h"



struct _huffmanTree {

	short int size;

	short int nodes;

	node_t *head;

	node_t *tail;
};

huffmanTree_t *createBinaryTree(){

	huffmanTree_t *new_huff = (huffmanTree_t *) malloc(sizeof(huffmanTree_t));


	new_huff->size = 0;
	new_huff->nodes = 0;

	new_huff->head = NULL;
	new_huff->tail = NULL;


	return new_huff;
}

void destroyBinaryTree(huffmanTree_t **tree){

	if ((*tree) != NULL) {

		node_t *tmp;


		while ((*tree)->head != NULL) {

			tmp = next((*tree)->head);

			destroyNode(&(*tree)->head);

			(*tree)->head = tmp;
		}


		free((*tree));

		(*tree) = NULL;
	}
}

short int numberOfNodes(huffmanTree_t *tree){

	if (tree != NULL) {

		return tree->nodes;
	} else {

		return -1;
	}
}

node_t *root(huffmanTree_t *tree){

	if (tree != NULL) {

		return tree->head;
	} else {

		return NULL;
	}
}

void add(huffmanTree_t *tree, node_t *to_add)
{

	if (tree != NULL && to_add != NULL) {

		if (tree->size == 0) {
			tree->head = to_add;
			tree->tail = to_add;
		} else {

			node_t *tmp = tree->head;


			while (tmp != NULL && frequency(tmp) < frequency(to_add)) {
				tmp = next(tmp);
			}


			nextSet(to_add, tmp);


			if (tmp != NULL) {

				previouSet(to_add, previous(tmp));


				if (tmp == tree->head) {

					tree->head = to_add;
				} else {

					nextSet(previous(to_add), to_add);
				}


				previouSet(next(to_add), to_add);
			} else {

				previouSet(to_add, tree->tail);

				nextSet(tree->tail, to_add);


				tree->tail = to_add;
			}
		}


		tree->size++;// vai dar pau
		tree->nodes++;//vai dar pau
	}
}

void forest(huffmanTree_t *tree){

	if (tree != NULL) {

		while (tree->size > 1) {

			node_t *left = getMin(tree);
			node_t *right = getMin(tree);

			if (left == NULL && right == NULL) {

				break;
			} else if (right == NULL) {

				add(tree,	createNode(AUX, frequency(left), left, right));
			} else {

				add(tree,	createNode(AUX, frequency(left) + frequency(right),	left, right));
			}
		}
	}
}

node_t *getMin(huffmanTree_t *tree){

	if (tree != NULL) {
		if (tree->size == 0) {

			return NULL;
		} else {

			node_t *tmp = tree->head;

			tree->head = next(tree->head);

			tree->size--;

			if (tree->size != 0) {

				previouSet(tree->head, NULL);
			} else {

				tree->tail = NULL;
			}


			nextSet(tmp, NULL);
			previouSet(tmp, NULL);


			return tmp;
		}
	} else {
		return NULL;
	}
}

void setLeaf(huffmanTree_t *tree){

	if (tree != NULL) {

		if (tree->nodes == 1) {

			representationSet(tree->head, "0");
		} else {

			char *code = (char *) calloc(height(tree->head), sizeof(char));//vai dar merdaaaa

			setNode(tree->head, code);

			free(code);
		}
	}
}

void saveHuffmanTree(huffmanTree_t *tree, FILE *dest){

	if (tree != NULL && dest != NULL) {

		saveNode(tree->head, dest);
	}
}
