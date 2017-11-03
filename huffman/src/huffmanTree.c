#include "inc/huffmanTree.h"

/*
		The structure tree.

		IMPORTANT ISSUE!!!

		 Our tree at the beginnig is a linked list.
*/
struct _huffmanTree {

	void *size; // Number of items in the list.

	void *nodes; // Number of nodes in the list.

	node_t *head; // list head.

	node_t *tail; // list tail.
};

/*
    Creates a new tree.

		MORE ABOUT THIS FUNCTION: open "huffmanTree.h" file.
*/
huffmanTree_t *createBinaryTree(){

	huffmanTree_t *new_huff = (huffmanTree_t *) malloc(sizeof(huffmanTree_t));


	new_huff->size = malloc(sizeof(short int));
	short int aux = 0;
	memcpy(new_huff->size, &aux, sizeof(short int));

	new_huff->nodes = malloc(sizeof(short int));
  short int aux2 = 0;
	memcpy(new_huff->nodes, &aux2, sizeof(short int));

	new_huff->head = NULL;
	new_huff->tail = NULL;


	return new_huff;
}

/*
    Destroy the tree and sets to NULL.

		MORE ABOUT THIS FUNCTION: open "huffmanTree.h" file.
*/
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

/*
    Returns the number of nodes of a tree.

		MORE ABOUT THIS FUNCTION: open "huffmanTree.h" file.
*/
short int numberOfNodes(huffmanTree_t *tree){

	if (tree != NULL) {

		return (*(short int*)tree->nodes);
	} else {

		return -1;
	}
}

/*
    Returns the root of a tree.

		MORE ABOUT THIS FUNCTION: open "huffmanTree.h" file.
*/
node_t *root(huffmanTree_t *tree){

	if (tree != NULL) {

		return tree->head;
	} else {

		return NULL;
	}
}

/*
    Puts the node in the tree, AS LIST AND IN A ORDERED WAY.

		MORE ABOUT THIS FUNCTION: open "huffmanTree.h" file.
*/
void add(huffmanTree_t *tree, node_t *to_add)
{

	if (tree != NULL && to_add != NULL) {

		if ((*(int*)tree->size) == 0) {
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

		short int intSize = (*(short int*)tree->size);
		intSize++;

		memcpy(tree->size, &intSize, sizeof(short int));
		//tree->size++;// vai dar pau

		short int intNodes = (*(short int*)tree->nodes);
		intNodes++;
		memcpy(tree->nodes, &intNodes, sizeof(short int));
		//tree->nodes++;//vai dar pau
	}
}

/*
    Transform a "tree linked list" in a strictly binary tree, like the huffman algorithm demands.

		MORE ABOUT THIS FUNCTION: open "huffmanTree.h" file.
*/
void forest(huffmanTree_t *tree){

	if (tree != NULL) {

		while ((*(int*)tree->size) > 1) {

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

/*
		Returns the node of a tree, that still is a linked list, which the item has the lowest
		frequency and removes the node from the list.

		MORE ABOUT THIS FUNCTION: open "huffmanTree.h" file.
*/
node_t *getMin(huffmanTree_t *tree){

	if (tree != NULL) {
		if ((*(int*)tree->size) == 0) {

			return NULL;
		} else {

			node_t *tmp = tree->head;

			tree->head = next(tree->head);

			short int intSize = (*(short int*)tree->size);
			intSize--;

			memcpy(tree->size, &intSize, sizeof(short int));
//			tree->size--;

			if ((*(short int*)tree->size) != 0) {

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

/*
    Sets the string that are the new codes of the itens of each leaf.

		MORE ABOUT THIS FUNCTION: open "huffmanTree.h" file.
*/
void setLeaf(huffmanTree_t *tree){

	if (tree != NULL) {

		if ((*(short int*)tree->nodes) == 1) {

			representationSet(tree->head, "0");
		} else {

			char *code = (char *) calloc(height(tree->head), sizeof(char));//vai dar merdaaaa

			setNode(tree->head, code);

			free(code);
		}
	}
}

/*
    Saves the nodes items from a tree in preorder to a file.

		MORE ABOUT THIS FUNCTION: open "huffmanTree.h" file.
*/
void saveHuffmanTree(huffmanTree_t *tree, FILE *dest){

	if (tree != NULL && dest != NULL) {

		saveNode(tree->head, dest);
	}
}
