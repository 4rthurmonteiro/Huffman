#include <CUnit/Basic.h>
//https://mysnippets443.wordpress.com/2015/03/07/ubuntu-install-cunit/
// gcc  -o teste teste.c  -lcunit
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct _node{
  int item;
  struct _node *next;
} node_t;

typedef struct _list{
  int size;
  node_t *head;
} list_t;

list_t* createList(){
  list_t* list = (list_t*) malloc(sizeof(list_t));

  list->size = 0;
  list->head = NULL;

  return list;
}

bool isEmpty(list_t *list){
    return (list->size == 0);
}

int pop(list_t *list){
    if(!isEmpty(list)){
      int aux = list->head->item;
      node_t *pointer = list->head;

      list->head = pointer->next;
      free(pointer);
      list->size--;
      return aux;
    }
    return -11;
}

int checkSize(list_t *list){
  if(list != NULL){
    return list->size;
  }

  return -11;
}


void push(list_t* list, int item){
  node_t* new_node = (node_t*) malloc(sizeof(node_t));
  new_node->item = item;
  new_node->next = list->head;
  list->head = new_node;
  list->size++;
}

// teste da hashTest

#define HASH_SIZE 100

typedef struct _element{
  int value;
} element_t;

typedef struct _hashTable{
  element_t *table[HASH_SIZE];
  int sizeTable;
} hashTable_t;

hashTable_t* createHashTable(){
  hashTable_t *new_hashTable = (hashTable_t*) malloc(sizeof(hashTable_t));
  int i;
  new_hashTable->sizeTable = 0;

  for(i = 0; i < HASH_SIZE; i++) new_hashTable->table[i] = NULL;

  return new_hashTable;
}

int put(hashTable_t *ht,int value, int position){
  element_t *new_element = (element_t*) malloc(sizeof(element_t));

  new_element->value = value;
  ht->table[position] = new_element;
  ht->sizeTable++;
  return new_element->value;
}

int checkHashSize(hashTable_t *ht){
  if(ht != NULL){
    return ht->sizeTable;
  }
  return -11;
}

// tree test

typedef struct _binaryTree {
  int item;
  int nodes;
  struct _binaryTree *left;
  struct _binaryTree *right;
} binaryTree_t;

binaryTree_t* createEmptyBinaryTree(){
  return NULL;
}

binaryTree_t* createBinaryTree(int item, binaryTree_t *left, binaryTree_t *right){
  binaryTree_t *new_tree = (binaryTree_t*) malloc(sizeof(binaryTree_t));

  new_tree->nodes = 1;
  new_tree->item = item;
  new_tree->left = right;
  new_tree->right = left;

  return new_tree;
}

bool isEmptyy(binaryTree_t *bt){
  if(bt == NULL) return true;
  else return false;
}

binaryTree_t* add(binaryTree_t *bt, int item){
  if(bt == NULL){
    bt = createBinaryTree(item, NULL, NULL);
  }else if(bt->item > item){
    bt->left = add(bt->left, item);
  }else{
    bt->right = add(bt->right, item);
  }
  bt->nodes++;
  return bt;
}

int checkSizeTree(binaryTree_t *bt){
  if(bt == NULL){
    return 0;
  }else{
    return bt->nodes;
  }
}

int init_suite(void)
{
    return 0;
}

int clean_suite(void)
{
    return 0;
}

void listTest(){

    list_t *list = createList();

    push(list, 10);

    CU_ASSERT(checkSize(list) == 1);


    CU_ASSERT(pop(list) == 10);

    CU_ASSERT(checkSize(list) == 1);

    CU_ASSERT(checkSize(list) == 0);



}


void hashTest(){

  hashTable_t *ht = createHashTable();

  CU_ASSERT(checkHashSize(ht) == 0);

  CU_ASSERT(put(ht, 2, 1) == 1);

  CU_ASSERT(checkHashSize(ht) == 0);

  CU_ASSERT(checkHashSize(ht) == 1);

  CU_ASSERT(put(ht, 1, 2) == 1);

  CU_ASSERT(checkHashSize(ht) == 2);

}

void treeTest(){

  binaryTree_t *bt = createEmptyBinaryTree();

  bt = createBinaryTree(10, NULL, NULL);

  CU_ASSERT(checkSizeTree(bt) == 1);

  add(bt, 14);

  CU_ASSERT(checkSizeTree(bt) == 2);

  add(bt, 19);

  CU_ASSERT(checkSizeTree(bt) == 3);


}

int main(){
  /* pSuite1 = lista
     pSuite2 = hash
     pSuite3 = Árvore
 */

    CU_pSuite pSuite1 = NULL;

    if(CUE_SUCCESS != CU_initialize_registry() )
    {
        return CU_get_error();
    }

    // Adiciona suite1 para registro
    pSuite1 = CU_add_suite("list_test_suite", init_suite, clean_suite);
    if (NULL == pSuite1)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Adiciona test1 para suite1
    if(NULL == CU_add_test(pSuite1, "list_test_suit", listTest)){
        CU_cleanup_registry();
        return CU_get_error();
    }


    // Adiciona test2 para suite2
    if(NULL == CU_add_test(pSuite1, "hash_test_suit", hashTest)){
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Adiciona test1 para suite1
    if(NULL == CU_add_test(pSuite1, "tree_test_suit", treeTest)){
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    printf("\n");
    CU_basic_show_failures(CU_get_failure_list());

    CU_cleanup_registry();
    return CU_get_error();
}
