// list/list.c
// 
// Implementation for linked list.
//
// <Sara Braddock>

#include <stdio.h>
#include <stdlib.h>
//#include <string.h>

#include "list.h"

list_t *list_alloc() {
  list_t* list = (list_t*) malloc(sizeof(list_t));
  list->head = NULL;
   return list; }

node_t *node_alloc(elem val){
  node_t* new_node = (node_t*) malloc(sizeof(node_t));
  new_node->value = val;
  new_node->next = NULL;
  return new_node;
}

void node_free(node_t *n) {
  free(n);
}

void list_free(list_t *l) {
  node_t *temp;
  node_t *cur = l -> head;
  if (l -> head != NULL){
    while (cur != NULL){
      temp = cur -> next;
      node_free(cur);
    }
  }
  free(l);
}


void list_print(list_t *l) {
  node_t *cur = l->head;
  if (cur == NULL){
    printf("Empty list! \n");
  }
  else{
    while (cur != NULL){
      printf("%d ", cur->value);
      cur = cur->next;
    }
  }
  printf("\n");
}
int list_length(list_t *l) { 
  int length = 0;
  node_t *temp = l->head;
  while ( temp != NULL){
    length++;
    temp = temp->next;
  }
  return length; }

void list_add_to_back(list_t *l, elem value) {
  // find last node 
  node_t *current = l->head;
  node_t *newNode = node_alloc(value);
  newNode -> value = value;
  newNode -> next = NULL;
  if (current == NULL){
    l -> head = newNode;
  }
  else{
    while (current -> next != NULL ){
      current = current -> next;
    }
    current->next = newNode;
  }
}

void list_add_to_front(list_t *l, elem value) {
  node_t *newNode;
  node_t *cur = l -> head;
  newNode = node_alloc(value);
  newNode -> value = value;
  newNode -> next = NULL;
  if (cur == NULL){
    l -> head = newNode;
  }
  else{
    newNode->next = cur;
    l -> head = newNode;
  }
}

void list_add_at_index(list_t *l, elem value, int index) {
  node_t *newNode;
  int curIdx = 0;
  bool current = true;
  node_t *prev = l -> head; 
  node_t *cur;
  if (l == NULL){
    printf("Empty List");
  }
  else if (index == 0){
    list_add_to_front(l, value);
  }
  else{
    while(current){
      if (curIdx == index){
        newNode = (node_alloc(value));
        newNode -> next = cur;
        prev -> next = newNode;
        current = false;
      }
      prev = prev -> next;
      cur = prev -> next; 
      curIdx++; 
    }
  }
}

elem list_remove_from_back(list_t *l) { 
  int count = 0;
  bool x = true;
  node_t * cur = l -> head;
  if(l == NULL){
    free(l);
    return 0;
  }
  while(x){
    if (cur -> next == NULL){
      node_free(cur);
      x = false;
    }
    cur = cur->next;
  }
  
  return 1; 
  }

elem list_remove_from_front(list_t *l) {
  node_t *temp = l -> head; 
  l -> head = temp -> next; 
  node_free(temp); 
   return -1; }

elem list_remove_at_index(list_t *l, int index) { 
  int count = 0;
  int count2 = -1;
  int i;
  node_t * current = l -> head;
  node_t * temp = NULL;

  if (index == 0){
    list_add_to_front(l, index);
  }
  else{
    for (i = 0; i < index; i++){
      if (current->next == NULL){

    }
    current = current->next;
  }

  temp = current->next;
  count2 = count - 1;
  current->next = temp;
  free(temp);
  }
  
  }

bool list_is_in(list_t *l, elem value) { 
  node_t * current = l -> head;
  while (current->next->next != NULL){
    if (current->value == value){
      return true;
    }
    current = current->next;
  }
  return false; }

elem list_get_elem_at(list_t *l, int index) { 
  int idxCount = 0;
  node_t * current = l -> head;
  int value;
  while (current->next->next != NULL){
    if (idxCount = index) {
      value = current -> value;
    }
    current = current->next;
    idxCount++;
  }
  return value; }
  
int list_get_index_of(list_t *l, elem value) { 
  int idxCount = 0;
  node_t * current = l -> head;
  while(current->next->next != NULL){
    if (current->value == value){
      return idxCount;
    }
    current = current->next;
    idxCount++;
  }
  return -1; }

