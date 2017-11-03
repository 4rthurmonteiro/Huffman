#include "inc/node.h"

/*
    Node structure.
*/
struct _node{

  unsigned char item; // The byte of the node.

  unsigned long long int frequency; // frequency of the item of the node.

  char *representation; // the new representation of the byte (Figured out by huffman algorithm).

  void *height; // The height of the node, used to know the size of the code.

  node_t *previous; // Previous Node in the list.

  node_t *next; // Next node in the list.

  node_t *left; // the left child "0".

  node_t *right; // the right child "1".
};

/*
    Creates the node, define the frequency of the node and the children.

		MORE ABOUT THIS FUNCTION: open "node.h" file.
*/
node_t *createNode(unsigned char item, unsigned long long int frequency, node_t *left, node_t *right){

	node_t *new_node = (node_t *) malloc(sizeof(node_t)); // Allocates memory to node_t struct

	new_node->item = item; // the item of the node.
	new_node->frequency = frequency; // sets the frequency.
	new_node->representation = NULL; // the representation initial is NULL, this variable will be the new code of the byte.

  new_node->height = malloc(sizeof(int)); // must allocate memory to height, because it's *void type.
  int aux = MAX(height(left), height(right)) + 1; // puts the MAX height in a aux value.
  memcpy(new_node->height, &aux, sizeof(int)); // and copy to new_node->height.

  new_node->previous = NULL; // Sets previous node NULL.
	new_node->next = NULL; // Sets next node NULL.
	new_node->left = left; // the left child.
	new_node->right = right; // the right child.

	return new_node; // returns the node created.
}

/*
    Destroy the node and the children, pointting to NULL.

		MORE ABOUT THIS FUNCTION: open "compress.h" file.
*/
void destroyNode(node_t **node){

	if ((*node) != NULL) { // checks if the arguments are valid.

		destroyNode(&(*node)->left);  // destroy the left child and points to NULL.

		destroyNode(&(*node)->right); // destroy the right child and points to NULL.

		free((*node)); // free the node.

		(*node) = NULL; // points to NULL.
	}
}

/*
    Returns true if it is a leaf.

		MORE ABOUT THIS FUNCTION: open "node.h" file.
*/
bool isLeaf(node_t *node){

	if (node != NULL) { // checks if the arguments are valid.

     if(node->left == NULL && node->right == NULL){ // if the node have not children, the node is a leaf.
        return true;
     }else{ // is not a leaf.

		return false;
  }
}
  return false;
}

/*
    Returns the node's item (node->item).

		MORE ABOUT THIS FUNCTION: open "node.h" file.
*/
unsigned char item(node_t *node){

	if (node != NULL) {

		return node->item;
	} else {

		return 0;
	}
}

/*
    Catch the frequency of each byte of a file and saves it in a hash table.

		MORE ABOUT THIS FUNCTION: open "node.h" file.
*/
unsigned long long int frequency(node_t *node){

	if (node != NULL) { // checks if the arguments are valid.

		return node->frequency; // returns the frequency.
	} else {

		return 0; // the node is NULL, so the frequency is "0".
	}
}

/*
    Adds 1 to the node's frequency.

		MORE ABOUT THIS FUNCTION: open "node.h" file.
*/
void freqPP(node_t *node)
{

	if (node != NULL) { // checks if the arguments are valid.

		node->frequency++; // adds "1".
	}
}

/*
    Returns the pointer to the string that contains the new code of the item of a node.

		MORE ABOUT THIS FUNCTION: open "node.h" file.
*/
char *representation(node_t *node)
{

	if (node != NULL) { // checks if the arguments are valid.

		return node->representation; // returns the new code of the byte.
	} else {

		return NULL;
	}
}

/*
    Sets a string as the new code of the item of a node.

		MORE ABOUT THIS FUNCTION: open "node.h" file.
*/
void representationSet(node_t *node, char *representation)
{

	if (node != NULL && representation != NULL) { // checks if the arguments are valid.

    /*
      Allocates memory for the string that will contain the new
  		binary code of the item (Byte) of the Node.
  	*/
		node->representation = (char *) calloc(strlen(representation) + 1, sizeof(char));

		strcpy(node->representation, representation); // copies the string.
	}
}

/*
    Returns the node's height in the Tree.

		MORE ABOUT THIS FUNCTION: open "node.h" file.
*/
int height(node_t *node)
{

	if (node != NULL) { // checks if the arguments are valid.

		return (*(int*)node->height); // returns the height, with a casting because is a *void type.
	} else {

		return -1;
	}
}

/*
    Returns the previous node.

		MORE ABOUT THIS FUNCTION: open "node.h" file.
*/
node_t *previous(node_t *node){

	if (node != NULL) { // checks if the arguments are valid.

		return node->previous; // returns the previous node.
	} else {

		return NULL;
	}
}

/*
    Sets the previous node.

		MORE ABOUT THIS FUNCTION: open "node.h" file.
*/
void previouSet(node_t *node, node_t *previous){

	if (node != NULL && previous != NULL) { // checks if the arguments are valid.

		node->previous = previous; // set as previous node.
	}
}

/*
    Returns the next node.

		MORE ABOUT THIS FUNCTION: open "node.h" file.
*/
node_t *next(node_t *node){

	if (node != NULL) { // checks if the arguments are valid.

		return node->next; // returns the next node.
	} else {

		return NULL;
	}
}

/*
    Returns the left child node from a node.

		MORE ABOUT THIS FUNCTION: open "node.h" file.
*/
void nextSet(node_t *node, node_t *next){

	if (node != NULL && next != NULL) { // checks if the arguments are valid.

		node->next = next; // set as next node.
	}
}

/*
    Returns the left child node from a node.

		MORE ABOUT THIS FUNCTION: open "node.h" file.
*/
node_t *left(node_t *node)
{

	if (node != NULL) { // checks if the arguments are valid.

		return node->left; // returns the left child.
	} else {

		return NULL;
	}
}

/*
    Returns the right child node from a node.

		MORE ABOUT THIS FUNCTION: open "node.h" file.
*/
node_t *right(node_t *node)
{

	if (node != NULL) { // checks if the arguments are valid.

		return node->right; // returns the right node.
	} else {

		return NULL;
	}
}

/*
    If the node is a leaf, it sets the new code with a string else calls this function
    recursively to your children with the same code put adding "0" or "1".

		MORE ABOUT THIS FUNCTION: open "node.h" file.
*/
void setNode(node_t *node, char *code){

	if (node != NULL && code != NULL) { // checks if the arguments are valid.

		if (isLeaf(node)) { // if the node is a leaf

			representationSet(node, code); // sets the code.
		}else{ // is not a leaf.

			short int i = strlen(code); // saves the position of the string.

			code[i] = '0'; // puts "0" in the position.

			setNode(left(node), code); // call this function to the left child, the "0" child.

			code[i] = '1'; // puts "1" in the position.

			setNode(right(node), code); // call this function to the right child, the "1" child.

			code[i] = '\0'; // cuts the string.
		}
	}
}

/*
    Saves the item of a node to a file and calls recursively to the childen of this node.

		MORE ABOUT THIS FUNCTION: open "node.h" file.
*/
void saveNode(node_t *node, FILE *dest){

	if (node != NULL) { // checks if the arguments are valid.

    /*
       If the Node that was passed is not a leaf or its item (Byte)
		   is not the auxiliary character, that is, the item of the
		   parent nodes, nor the escape character.
		 */
		if (!isLeaf(node) || (node->item != AUX && node->item != ESC)) {

			fwrite(&node->item, sizeof(unsigned char), 1,	dest); // writes the item in the dest file.
		} else {

      /*
         If it is sheet, but the item (Byte) of the Node is
			   the auxiliary character, that is, the item of the
			   parent nodes, or the escape character. We create a
			   temporary string composed of the escape character
			   followed by the (Byte) item of the Node.
			 */
			unsigned char tmp[2] = {ESC, node->item}; // puts the ESCAPE "\\" and the item.

			fwrite(tmp, sizeof(unsigned char), 2, dest); // and writes to the output file.
		}

		saveNode(left(node), dest);
		saveNode(right(node), dest);
	}
}

/*
    Returns a node which the item and the items of the childen were taken from a file.

		MORE ABOUT THIS FUNCTION: open "node.h" file.
*/
node_t *getNode(FILE *src){

	if (src != NULL) { // checks if the arguments are valid.
		unsigned char buffer; // char buffer to read info.

		fread(&buffer, sizeof(unsigned char), 1, src); // reads a byte from the input file.

		if (buffer == AUX) { // if is the byte of the auxiliary character, this is the parent item (byte).
      /*
         We return a new Node whose left and right children
			   are returns of this same function.
			 */
			return createNode(buffer, 0, getNode(src), getNode(src));
		} else if (buffer == ESC) { // if the escape character, so we read the next byte.

			fread(&buffer, sizeof(unsigned char), 1, src); // reads the byte from the input file.

			return createNode(buffer, 0, NULL, NULL); // and returns the node (which is a leaf).
		} else {
      /*
         If it is not the helper character or the escape
			   character, we only return a new Node (which is a
			   sheet) whose item is the Byte we just read.
			 */
			return createNode(buffer, 0, NULL, NULL);
		}
	} else { // if error

		return NULL; // the file passed is NULL.
	}
}
