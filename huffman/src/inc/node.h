#ifndef NODE_H

#include "huffmanComponents.h"

#define NODE_H

/*
    Define the node type.
*/
typedef struct _node node_t;


node_t *createNode(unsigned char, unsigned long long int, node_t *, node_t *);

/*
    Destroy the node and the children, pointting to NULL.
    Input: The node pointer pointer (node_t **) to be destroyed.
    Output: It's a void function.
 */
void destroyNode(node_t **);

/*
    Returns true if it is a leaf.
    Input: The node (node_t *) to be tested.
    Output: True if it is a leaf OR False if not.
 */
bool isLeaf(node_t *);

/*
    Returns the node's item (node->item).
    Input: The node to have the item returned (node_t *);
    Output: The item (node->item) if the node is not NULL.
 */
unsigned char item(node_t *);

/*
  Returns the frequency of a node's item.
  Input: The node (node_t *) to be picked up the frequency.
  Output:  0 if the node that was passed is NULL or the real frequency if not.
 */
unsigned long long int frequency(node_t *);

/*
    Adds 1 to the node's frequency.
    Input: The node to the frequency will be added 1.
    Output: It's a void function.
 */
void freqPP(node_t *);

/*  Returns the pointer to the string that contains the new code of the item of a node.
    Input: The node (node_t *) which the new code of the item its necessary to know.
    Output: If is NULL returns NULL else returns the new code representation.
 */
char *representation(node_t *);

/*
    Sets a string as the new code of the item of a node.
    Input: The node (node_t *) which the item will be updated. If one of the arguments passed is NULL, the function does nothing.
    Output: It's a void function.
*/
void representationSet(node_t *, char *);

/*
    Returns the node's height in the Tree.
    Input: The node (node_t *) which its necessary to know the height.
    Output: If the node passed is NULL returns -1 else return the real value.
 */
int height(node_t *);

/*
    Returns the previous node.
    Input: The node (node_t *) which is desired to know the previous node.
    Output: Returns NULL if the node passed is NULL or Returns the previous node.
 */
node_t *previous(node_t *);

/*
    Sets the previous node.
    Input: The node (node_t *) which is desired to set the previous node and the previous node (node_t *) to set.
    If one of the arguments passed is NULL, the function does nothing.
    Output: It's a void function.
 */
void previouSet(node_t *, node_t *);

/*
    Returns the next node.
    Input: The node (node_t *) which is desired to know the next node.
    Output: Returns NULL if the node passed is NULL or Returns the next node.
 */
node_t *next(node_t *);

/*
    Sets the next node.
    Input: The node (node_t *) which is desired to set the next node and the next node (node_t *) to set.
    If one of the arguments passed is NULL, the function does nothing.
    Output: It's a void function.
 */
void nextSet(node_t *, node_t *);

/*
   Returns the left child node from a node.
   Input: The node (node_t *) which is desired to know the left child.
   Output: Returns NULL if the node passed is NULL else returns the left child.
 */

node_t *left(node_t *);

/*
   Returns the right child node from a node.
   Input: The node (node_t *) which is desired to know the right child.
   Output: Returns NULL if the node passed is NULL else returns the right child.
 */
node_t *right(node_t *);

/*
  If the node is a leaf, it sets the new code with a string else calls this function
  recursively to 
*/
void setNode(node_t *, char *);


void saveNode(node_t *, FILE *);


node_t *getNode(FILE *);

#endif
