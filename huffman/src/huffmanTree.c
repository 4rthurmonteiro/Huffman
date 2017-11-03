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

	huffmanTree_t *new_huff = (huffmanTree_t *) malloc(sizeof(huffmanTree_t)); // Allocates memory to the new tree.

	new_huff->size = malloc(sizeof(short int)); // Allocates memory to the size value.

	short int aux = 0; // auxiliary short int, to save "0" to the new_huff->size.

	memcpy(new_huff->size, &aux, sizeof(short int)); // puts "0" in the new_huff->size.

	new_huff->nodes = malloc(sizeof(short int)); // Allocates memory to the nodes value.

  short int aux2 = 0; // auxiliary short int, to save "0" to the new_huff->nodes.

	memcpy(new_huff->nodes, &aux2, sizeof(short int));// puts "0" in the new_huff->nodes.

	new_huff->head = NULL; // pointer head to NULL.

	new_huff->tail = NULL; // pointer tail to NULL.

/*
		Returns the tree, but its important to remember that's still a linked list
		and will be transformed in a strictly binary tree when pass to the function forest.
*/
	return new_huff;
}

/*
    Destroy the tree and sets to NULL.

		MORE ABOUT THIS FUNCTION: open "huffmanTree.h" file.
*/
void destroyBinaryTree(huffmanTree_t **tree){

	if ((*tree) != NULL) { // check if the arguments are valid.

		node_t *tmp; // auxiliar node.

		while ((*tree)->head != NULL) { // loop checking if the node->head is still valid.

			tmp = next((*tree)->head); // save the next node.

			destroyNode(&(*tree)->head); // destroy the head node and puts do NULL.

			(*tree)->head = tmp; // now the head is the second node at the beginnig.
		}

		free((*tree)); // free memory.

		(*tree) = NULL; // and puts the tree to NULL.
	}
}

/*
    Returns the number of nodes of a tree.

		MORE ABOUT THIS FUNCTION: open "huffmanTree.h" file.
*/
short int numberOfNodes(huffmanTree_t *tree){

	if (tree != NULL) { // check if the arguments are valid.

		return (*(short int*)tree->nodes); // It's necessary make a cast in the variable because its *void type.
	} else {
		return -1; // logical error.
	}
}

/*
    Returns the root of a tree.

		MORE ABOUT THIS FUNCTION: open "huffmanTree.h" file.
*/
node_t *root(huffmanTree_t *tree){

	if (tree != NULL) { // check if the arguments are valid.

		return tree->head; // returns the root.
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

	if (tree != NULL && to_add != NULL) { // check if the arguments are valid.

		if ((*(int*)tree->size) == 0) { // checks if the tree is empty. It's necessary make a cast because size is a *void type.

			tree->head = to_add; // The tree (still is a list) is empty so the node added is the head of the list.

			tree->tail = to_add; // The tree (still is a list) is empty so the node added is the tail of the list.
		} else {

			node_t *tmp = tree->head; // auxiliary node.


			while (tmp != NULL && frequency(tmp) < frequency(to_add)) { // searches the first node with frequency higher.
				tmp = next(tmp); // it's not higher so go to the next node.
			}

			/*
				After the while the next node have frequency greater of the to_add (node_t).
			*/
			nextSet(to_add, tmp);  // Sets the next node.

			if (tmp != NULL) { // If that we are adding does not have the highest frequency so far.

				/*
					 We say that the previous Node to which we are
				   adding is the Node that was previous of the
				   one that has a higher frequency than the one
				   we are adding.
				 */
				previouSet(to_add, previous(tmp));


				if (tmp == tree->head) { // if is the lowest frequency so far.

					tree->head = to_add; // now is the head of the list.
				} else {

					/*
					  	If not, we say that the Node that
					   follow the one that has turn into the
					   one that is before to the one we are
					   adding is the one we are adding.
					 */
					nextSet(previous(to_add), to_add);
				}


				/*
						We say that the Node before to the Node that
				  	has turned into the next to the one we are
				  	adding is the one we are adding.
				 */
				previouSet(next(to_add), to_add);
			} else {
				/*
						If it has the highest frequency so far, we
				  	say the previous to the one we are adding is
				  	the list "Tail".
				 */
				previouSet(to_add, tree->tail);


				nextSet(tree->tail, to_add); // That the following to the list "tail" is the one we are adding.

				tree->tail = to_add; // the new list tail.
			}
		}

		short int intSize = (*(short int*)tree->size); // puts the tree->size with cast (*void type) into a auxiliary variable.
		intSize++; // adds "1" to the aux variable.

		memcpy(tree->size, &intSize, sizeof(short int)); // and puts into the tree->size this value updated.

		short int intNodes = (*(short int*)tree->nodes); // puts the tree->nodes with cast (*void type) into a auxiliary variable.
		intNodes++; // adds "1" to the aux variable.

		memcpy(tree->nodes, &intNodes, sizeof(short int)); // and puts into the tree->nodes this value updated.
	}
}

/*
    Transform a "tree linked list" in a strictly binary tree, like the huffman algorithm demands.

		MORE ABOUT THIS FUNCTION: open "huffmanTree.h" file.
*/
void forest(huffmanTree_t *tree){

	if (tree != NULL) { // check if the arguments are valid.

		while ((*(int*)tree->size) > 1) { // checks the loop until at least remains two elements in the tree.

		 /*
		 	 We remove the two nodes from the list whose item has
		   the lowest frequency.
		 */
			node_t *left = getMin(tree);
			node_t *right = getMin(tree);

			if (left == NULL && right == NULL) { // if the both are NULL the function stop. The list is empty.

				break;
   				/*
						If only the right is NULL, it means that
				   there was only one Node in the list, so the
				   frequency of the auxiliary Node we are going
				   to add will be the same as the left child. *
				 */
			} else if (right == NULL) { // Only the right is NULL so just one more node in the list.

				add(tree,	createNode(AUX, frequency(left), left, right)); // add the "*" node with te frequency equal with the left child.

				/*
					If neither is NULL, the frequency of the
			    auxiliary Node we are going to add will be
		      the sum of the left and right frequencies. *
				 */
			} else {

				add(tree,	createNode(AUX, frequency(left) + frequency(right),	left, right)); // add the "*" node with te frequency equal with the sum of the right and the left child.
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

	if (tree != NULL) { // check if the arguments are valid.
		if ((*(int*)tree->size) == 0) { // the list is empty so return NULL.

			return NULL;
		} else {

			node_t *tmp = tree->head; // takes the head, because the list is ordered so the HEAD HAS THE LOWEST FREQUENCY.

			tree->head = next(tree->head); // The list head is now the second element of the list.

			short int intSize = (*(short int*)tree->size); // puts the tree->size with cast (*void type) into a auxiliary variable.
			intSize--; // decreases "1".

			memcpy(tree->size, &intSize, sizeof(short int)); // and puts into the tree->size this value updated.

			if ((*(short int*)tree->size) != 0) { // Still have elements in the list.

				previouSet(tree->head, NULL); // so the previous of the new head is NULL.
			} else { // No more elements in the list.

				tree->tail = NULL; // so the tail is NULL.
			}

			 /*
				 It causes the next and the previous to the Node that
			   we take out to be NULL. *
			 */
			nextSet(tmp, NULL);
			previouSet(tmp, NULL);

			return tmp; // returns the withdrawn Node.
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

	if (tree != NULL) { // check if the arguments are valid.

		if ((*(short int*)tree->nodes) == 1) { // just one type of item (byte) in the input.

			representationSet(tree->head, "0"); // the new represent is 0 (MAX COMPRESS).
		} else {

			 /*
				 Otherwise, allocates memory to a string that will
			   have exactly the maximum size for any representation
			   of the leaves of the Tree.
			 */
			char *code = (char *) calloc(height(tree->head), sizeof(char));

			 /*
				 Sets the representation of the root Node of the Tree,
			   since this function is recursive it just sets in all
			   and only in the leaves.
			 */
			setNode(tree->head, code);

			free(code); // free memory.
		}
	}
}

/*
    Saves the nodes items from a tree in preorder to a file.

		MORE ABOUT THIS FUNCTION: open "huffmanTree.h" file.
*/
void saveHuffmanTree(huffmanTree_t *tree, FILE *dest){

	if (tree != NULL && dest != NULL) { // check if the arguments are valid.

		/*
			  We save the root Node of the Tree, since this function is
		   recursive it saves all the nodes of the Tree in preorder. *
		 */
		saveNode(tree->head, dest);
	}
}
