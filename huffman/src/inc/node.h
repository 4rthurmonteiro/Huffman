#ifndef NODE_H

#include "huffmanComponents.h"

#define NODE_H

/* Define o tipo node.
*/
typedef struct _node node_t;


node_t *createNode(unsigned char, unsigned long long int, node_t *, node_t *);

/*  Destoi o nó e seus filhos, e aponta eles para NULL.
    Entrada: O pointeiro ponteiro do nó (node_t **) a ser destruido.
 */
void destroyNode(node_t **);

/*  Retorna true se for uma folha.
    Entrada: O nó (node_t *) a ser testado.
 */
bool isLeaf(node_t *);

/*  Retorna o item do nó.
    Entrada: O nó a ter o item retornado (node_t *).
 */
unsigned char item(node_t *);

/* Returns the frequency of an Node's item.
 * Pass: the Node (node_t *) whose item you want the frequency.
 * PS: returns 0 if the Node that was passed is NULL.
  Retorna a frequência do item naqueles nó.
  Entrada: Nó a ser consultado (node_t *).
 */
unsigned long long int frequency(node_t *);

/*  Acrescenta a frequência do nó em 1.
    Entrada: O nó a ter a frequência adicionada.
 */
void freqPP(node_t *);

/*  Retorna o ponteiro da string que contém o novo código do item do nó.
    Entrada: O nó (node_t *) que o novo codigo você quer.
 */
char *representation(node_t *);


void representationSet(node_t *, char *);



int height(node_t *);


node_t *previous(node_t *);


void previouSet(node_t *, node_t *);


node_t *next(node_t *);


void nextSet(node_t *, node_t *);


node_t *left(node_t *);


node_t *right(node_t *);


void setNode(node_t *, char *);


void saveNode(node_t *, FILE *);


node_t *getNode(FILE *);

#endif
