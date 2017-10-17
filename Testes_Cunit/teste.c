#include <CUnit/Basic.h>
//https://mysnippets443.wordpress.com/2015/03/07/ubuntu-install-cunit/
// gcc  -o test test.c  -lcunit
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

void push(list_t* list, int item){
  node_t* new_node = (node_t*) malloc(sizeof(node_t));
  new_node->item = item;
  new_node->next = list->head;
  list->head = new_node;
  list->size++;
}

void printList(list_t *list){
  node_t *pointer = list->head;

  if(pointer == NULL) printf("Lista Vazia\n");

  while(pointer != NULL){
    printf("%d ", pointer->item);
    pointer = pointer->next;

  }
  printf("\n");
}

bool isEmpty(list_t *list){
    return (list->size == 0);

    return false;
}

int pop(list_t *list){
    if(!isEmpty(list)){
      node_t *pointer = list->head;

      list->head = pointer->next;
      free(pointer);
      list->size--;
      return list->head->item;
    }
    return -1;
}

node_t* atPos(list_t *list, int index){

  if(index >= 0 && index < list->size){
    node_t* node = list->head;

    int i;
    for(i = 0; i < index; i++) node = node->next;

    return node;

  }
  printf("Indice Invalido\n");
  return NULL;
}

int indexOf(list_t *list, node_t *node){
  if(node != NULL){
      node_t *pointer = list->head;

      int index = 0;
      while(pointer != node && pointer != NULL){
        pointer = pointer->next;
        index++;
      }
      if(pointer != NULL) return index;
  }

  printf("No nao percentece a lista\n");
  return -1;
}

void erase(list_t *list, int index){
  if(index == 0){
    pop(list);

  } else{
    node_t *current = atPos(list, index);

    if(current != NULL){
      node_t *previous = atPos(list, index - 1);
      previous->next = current->next;

      free(current);
      list->size--;

    }
  }
}

void insert(list_t *list, int item, int index){
  if(index == 0){
    push(list, item);
  }else{
    node_t *current = atPos(list, index);

    if(current != NULL){
      node_t * previous = atPos(list, index - 1);
      node_t *new_node = (node_t*) malloc(sizeof(node_t));
      new_node->item = item;

      previous->next = new_node;
      new_node->next = current;
      list->size++;
    }
  }
}

void xchgNodes(list_t *list, node_t *nodeA, node_t *nodeB){

  if(nodeA == nodeB) return;

  int indexA = indexOf(list, nodeA);
  int indexB = indexOf(list, nodeB);

  if(indexA > indexB){
    nodeA = nodeB;
    nodeB = atPos(list, indexA);

    indexA = indexB;
    indexB = indexOf(list, nodeB);
  }

  node_t *pb = atPos(list, indexB - 1);

  if(nodeA == list->head){
    list->head = nodeB;
  }else{
    node_t *pa = atPos(list, indexA - 1);
    pa->next = nodeB;
  }

  pb->next = nodeA;

  node_t *pointer = nodeA->next;
  nodeA->next = nodeB->next;
  nodeB->next = pointer;
}

node_t *min(list_t *list, int index){
  node_t *pointer = atPos(list, index);

  if(pointer != NULL){
    node_t* minNode = pointer;

    while(pointer != NULL){
      if(pointer->item < minNode->item) minNode = pointer;

      pointer = pointer->next;
    }
    return minNode;
  }

  return NULL;
}

node_t *max(list_t *list, int index){
  node_t *pointer = atPos(list, index);

  if(pointer != NULL){
    node_t* maxNode = pointer;

    while(pointer != NULL){
      if(pointer->item > maxNode->item) maxNode = pointer;

      pointer = pointer->next;
    }
    return maxNode;
  }

  return NULL;
}

void incSort(list_t *list){
  int i;

  for(i = 0; i < list->size - 1; i++) xchgNodes(list, atPos(list, i), min(list, i));
}

void decSort(list_t *list){
  int i;

  for(i = 0; i < list->size - 1; i++) xchgNodes(list, atPos(list,i), max(list,i));
}

int checkSize(list_t *list){
  if(list != NULL){
    return list->size;
  }else{
    return -1;
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

    list_t* list = createList();

    CU_ASSERT_EQUAL(isEmpty(list), 0);
    push(list, 10);
    printf("\n%d\n", checkSize(list));

    CU_ASSERT_EQUAL(checkSize(list), 1);
    push(list, 20);

    CU_ASSERT_EQUAL(checkSize(list), 2);

    CU_ASSERT_EQUAL(pop(list), 20);

    CU_ASSERT_EQUAL(pop(list), 10);

    CU_ASSERT_EQUAL(pop(list), -1);

}

/*
void hashTest(){

}

void binaryTreeTest(){

}
*/
int main(){
    CU_pSuite pSuite = NULL;
    if(CUE_SUCCESS != CU_initialize_registry() )
    {
        return CU_get_error();
    }

    pSuite = CU_add_suite("list_test_suite", init_suite, clean_suite);
    if (NULL == pSuite)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if(NULL == CU_add_test(pSuite, "list_test_suite", listTest)){
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
