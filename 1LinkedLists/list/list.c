// list/list.c
// 
// Implementation for linked list.
//
// <Author>

#include <stdio.h>
#include <stdlib.h>
//#include <string.h>

#include "list.h"

list_t *list_alloc() { return NULL; }
void list_free(list_t *l) {}

void list_print(list_t *l) {
  list_t * current = l;
  while (current != NULL){
    printf("%d\n", current->value);
    current = current->next;
  }
}
int list_length(list_t *l) { 
  int length = 0;
  list_t * temp = l;
  while ( temp-> != NULL){
    length++;
    temp = temp->next;
  }
  return length; }

void list_add_to_back(list_t *l, elem value) {
  // find last node 
  list_t * current = l;
  while (current->next != NULL ){
    current = current -> next;
  }

  current->next = (list_t*)malloc(sizeof(list_t));
  current->next->value = value;
  current->next->next = NULL;
}
void list_add_to_front(list_t *l, elem value) {
  list_t * newNode;
  newNode = (list_t *) malloc(sizeof(list_t));
  newNode->value = value;
  newNode->next = *l;
  *l = newNode;
}
void list_add_at_index(list_t *l, elem value, int index) {}

elem list_remove_from_back(list_t *l) { 
  int count = 0;
  if(l->next == NULL){
    count = l->value;
    free(l);
    return count;
  }
  list_t * current = l;
  while(current->next->next != NULL){
    current = curent->next;
  }
  count = curent->next->value;
  free(current->next);
  current->next = NULL;
  return count; 
  }
elem list_remove_from_front(list_t *l) { return -1; }
elem list_remove_at_index(list_t *l, int index) { 
  int count = 0;
  int count2 = -1;
  list_t * current = *l;
  list_t * temp = NULL;

  if (index == 0){
    return list_add_to_front(l);
  }
  for (i = 0; i < index -1; i++){
    if (current->next == NULL){
      return -1;
    }
    current = current->next;
  }

  if (current->next == NULL){
    return -1;
  }

  temp = current->next;
  count2 = temp->value;
  current->next = temp->value;
  free(temp);
  return count2; }

bool list_is_in(list_t *l, elem value) { 
  list_t * current = *l;
  while (current->next->next != NULL){
    if (current->value == value){
      return true;
    }
    current = current->next;
  }
  return false; }
elem list_get_elem_at(list_t *l, int index) { 
  int idxCount = 0;
  list_t * current = *l;
  while (current->next->next != NULL){
    if (idxCount = index) {
      value = current.value;
    }
    current = current->next;
    idxCount++;
  }
  return value; }
int list_get_index_of(list_t *l, elem value) { 
  int idxCount = 0;
  list_t * current = *l;
  while(current->next->next != NULL){
    if (current.value == value){
      return idxCount;
    }
    current = current->next;
    idxCount++;
  }
  return -1; }

