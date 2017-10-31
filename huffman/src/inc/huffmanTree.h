#ifndef HUFFMANTREE_H

#include "node.h"

#define HUFFMANTREE_H

/*
  Define the huffman tree type.
*/
typedef struct _huffmanTree huffmanTree_t;

/*
   Creates a new tree.
*/
huffmanTree_t *createBinaryTree();

/*
   Destroy the tree and sets to NULL.
   Input: The tree pointer pointer (huffmanTree_t **) to be destroyed.
   Output: If the tree passed is NULL the function does nothing else destroy the tree.
   Returns nothing because is a void function.
*/
void destroyBinaryTree(huffmanTree_t **);

/*
   Returns the number of nodes of a tree.
   Input: The tree (huffmanTree_t *) which is desired to know the number of nodes.
   Output: Returns -1 if the tree passed is NULL or the real value.
 */
short int numberOfNodes(huffmanTree_t *);

/*
   Returns the root of a tree.
   Input: The tree (huffmanTree_t *) which the root is desired.
   Output: Returns NULL if the tree passed is NULL or the tree's root node.
*/
node_t *root(huffmanTree_t *);

/*
   Puts the node in the tree, AS LIST AND IN A ORDERED WAY.
   Input: The tree (huffmanTree_t *) which the node will be put and the node (node_t *).
   Output: If one of the arguments passed is NULL, the function does nothing else put the
   node in the tree.
*/
void add(huffmanTree_t *, node_t *);

/*
    Transform a "tree linked list" in a strictly binary tree, like the huffman algorithm demands.
    Input: The tree (huffmanTree_t *) which still is a linked list.
    Output: If the tree is NULL the function does nothing and if the tree is already a strictly binary tree,
    it creates another node root increasing the depth of the tree.
    Return nothing because is a void function.
*/
void forest(huffmanTree_t *);

/*
   Returns the node of a tree, that still is a linked list, which the item has the lowest
   frequency and removes the node from the list.
   Input: The tree (huffmanTree_t *) which is desired to remove the node with the lowest frequency.
   Output: If the tree passed is NULL or is empty returns NULL else returns de node with de lowest frequency and remove from the tree.
*/
node_t *getMin(huffmanTree_t *);

/*
   Sets the string that are the new codes of the itens of each leaf.
   Input: The tree (huffmanTree_t *) which the new leaf codes will be set.

   IMPORTANT ISSUE !!!
      The tree must already have passed through the forest function.

   Output: The string is set. Example: b'001100110.
   Returns nothing because is a void function.
*/
void setLeaf(huffmanTree_t *);

/*
   Saves the nodes items from a tree in preorder to a file.
   Input: The tree (huffmanTree_t *) and the file (FILE *) to be saved.

      IMPORTANT ISSUE !!!
         The tree must already have passed through the forest function.

   Output: This function does nothing if one of the arguments, the tree or the file is NULL else
   saves the items in the file.
   Returns nothing because is a void function.
*/
void saveHuffmanTree(huffmanTree_t *, FILE *);

#endif
