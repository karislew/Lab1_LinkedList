// list/list.c
// 
// Implementation for linked list.
//
// <Author>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

list_t *list_alloc() { 
   //creates memory for list structure and return it
  list_t* mylist =  (list_t *) malloc(sizeof(list_t));
  //keeps track of head of list 
  mylist->head = NULL;
  return mylist;
 
}

void list_free(list_t *l) {
  node_t *t = l->head;
  node_t *previous;
  while(t!=NULL){
    previous=t;
    free(previous);
    t = t->next; 
  }
}

void list_print(list_t *l) {
    node_t *cur;
  //current (sets to head)
  cur = l->head;
  printf("MY List: \n");
  //while you havent reached an empty node
  while(cur!=NULL){
    //print out the value
    printf("%d\n", cur->value);
    cur= cur->next;
  }
}

char * listToString(list_t *l) {
  char* buf = (char *) malloc(sizeof(char) * 10024);
  char tbuf[20];

	node_t* curr = l->head;
  while (curr != NULL) {
    sprintf(tbuf, "%d->", curr->value);
    curr = curr->next;
    strcat(buf, tbuf);
  }
  strcat(buf, "NULL");
  return buf;
}

int list_length(list_t *l) {
  int count = 0; 
  node_t *cur_node = l->head;
  while(cur_node!=NULL){
    cur_node = cur_node->next;
    count++;
  }
  return((l==NULL)? -1:count);
}

void list_add_to_back(list_t *l, elem value) {
  node_t *cur_node = (node_t *) getNode(value);
  node_t *t = l->head;
  while(t->next!=NULL){
    t = t->next;
  }
  t->next = cur_node;

}


void list_add_to_front(list_t *l, elem value) {

    //creates new code 
     node_t *cur_node = (node_t *) getNode(value);

     /* Insert to front */
     //get beginning of the list 
     node_t *head = l->head;  // get head of list

    //setting the added node to point to the "old" head
     cur_node->next = head;
     
     //set head to the added node 
     l->head = cur_node;
}

node_t * getNode(elem value) {
  node_t *mynode;

  mynode = (node_t *) malloc(sizeof(node_t));
  mynode->value = value;
  mynode->next = NULL;

  return mynode;
}

void list_add_at_index(list_t *l, elem value, int index) {
  node_t *cur_node = (node_t *) getNode(value);
  node_t *t = l->head;
  node_t *current; 
  int count = 0; 
  while(count!=index){
    t = t->next;
    count++;
  }
  current = t->next;
  t->next = cur_node;
  cur_node->next = current;
}

elem list_remove_from_back(list_t *l) { 
  node_t *t =l->head; 
  while(t->next!=NULL){
    t= t->next;
  }
  node_t *deleted_node = t;
  free(deleted_node);
  return -1;
  }
elem list_remove_from_front(list_t *l) { return -1; }
elem list_remove_at_index(list_t *l, int index) { return -1; }

bool list_is_in(list_t *l, elem value) { return false; }
elem list_get_elem_at(list_t *l, int index) { return -1; }
int list_get_index_of(list_t *l, elem value) { return -1; }

