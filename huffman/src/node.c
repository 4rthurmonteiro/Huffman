#include "inc/node.h"

struct _node{

  unsigned char item;


  unsigned long long int frequency;


  char *representation;


  void *height;

node_t *previous;


node_t *next;


node_t *left;

node_t *right;
};

node_t *createNode(unsigned char item, unsigned long long int frequency, node_t *left, node_t *right){


	node_t *new_node = (node_t *) malloc(sizeof(node_t));

	new_node->item = item;
	new_node->frequency = frequency;
	new_node->representation = NULL;
  new_node->height = malloc(sizeof(int));
  int aux = MAX(height(left), height(right)) + 1;
  memcpy(new_node->height, &aux, sizeof(int));
	new_node->previous = NULL;
	new_node->next = NULL;
	new_node->left = left;
	new_node->right = right;

	return new_node;
}

void destroyNode(node_t **node){

	if ((*node) != NULL) {

		destroyNode(&(*node)->left);

		destroyNode(&(*node)->right);

		free((*node));

		(*node) = NULL;
	}
}

bool isLeaf(node_t *node){

	if (node != NULL) {

     if(node->left == NULL && node->right == NULL){
        return true;
     }else{

		return false;
	 }
  }
  return false;
}

unsigned char item(node_t *node){

	if (node != NULL) {

		return node->item;
	} else {

		return 0;
	}
}

unsigned long long int frequency(node_t *node){

	if (node != NULL) {

		return node->frequency;
	} else {

		return 0;
	}
}

void freqPP(node_t *node)
{

	if (node != NULL) {

		node->frequency++;
	}
}

char *representation(node_t *node)
{

	if (node != NULL) {

		return node->representation;
	} else {

		return NULL;
	}
}

void representationSet(node_t *node, char *representation)
{

	if (node != NULL && representation != NULL) {

		node->representation = (char *) calloc(strlen(representation) + 1, sizeof(char));


		strcpy(node->representation, representation);
	}
}

int height(node_t *node)
{

	if (node != NULL) {

		return (*(int*)node->height);
	} else {

		return -1;
	}
}

node_t *previous(node_t *node){

	if (node != NULL) {

		return node->previous;
	} else {

		return NULL;
	}
}

void previouSet(node_t *node, node_t *previous){

	if (node != NULL && previous != NULL) {

		node->previous = previous;
	}
}

node_t *next(node_t *node){

	if (node != NULL) {

		return node->next;
	} else {

		return NULL;
	}
}

void nextSet(node_t *node, node_t *next){

	if (node != NULL && next != NULL) {

		node->next = next;
	}
}

node_t *left(node_t *node)
{

	if (node != NULL) {

		return node->left;
	} else {

		return NULL;
	}
}

node_t *right(node_t *node)
{

	if (node != NULL) {

		return node->right;
	} else {

		return NULL;
	}
}

void setNode(node_t *node, char *code){

	if (node != NULL && code != NULL) {

		if (isLeaf(node)) {

			representationSet(node, code);
		}else{

			short int i = strlen(code);


			code[i] = '0';


			setNode(left(node), code);


			code[i] = '1';


			setNode(right(node), code);


			code[i] = '\0';
		}
	}
}

void saveNode(node_t *node, FILE *dest){

	if (node != NULL) {

		if (!isLeaf(node) || (node->item != AUX && node->item != ESC)) {
	
			fwrite(&node->item, sizeof(unsigned char), 1,	dest);
		} else {

			unsigned char tmp[2] = {ESC, node->item};


			fwrite(tmp, sizeof(unsigned char), 2, dest);
		}

		saveNode(left(node), dest);
		saveNode(right(node), dest);
	}
}

node_t *getNode(FILE *src){

	if (src != NULL) {
		unsigned char buffer;


		fread(&buffer, sizeof(unsigned char), 1, src);


		if (buffer == AUX) {

			return createNode(buffer, 0, getNode(src), getNode(src));
		} else if (buffer == ESC) {

			fread(&buffer, sizeof(unsigned char), 1, src);

			return createNode(buffer, 0, NULL, NULL);
		} else {

			return createNode(buffer, 0, NULL, NULL);
		}
	} else {

		return NULL;
	}
}
