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
  node_t *next;
  while(t!=NULL){
    //get next
    next=t->next;
    //free current
    free(t);
    //move t 
    t = next; 
  }
  //set head back to null
  l->head=NULL;
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
  //if the head is null then i can just make the new node head
  if(l->head==NULL){
    l->head = cur_node;
    return;
  }
  //if t->next ==NULL then we're at the end of the list
  while(t->next!=NULL){
    t = t->next;
  }
  //add the new node
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
  //checking cases
  if(l==NULL||index<1) return;
  node_t *t = l->head;
  node_t *current; 
  //if index is 1, insert at front of list
  if(index==1){
    //making new node point to old head
    cur_node->next=l->head;
    //move head
    l->head=cur_node;
    return;
  }

  int count = 1; 
  //want to stop count before its on the same index (that way we have access to link nodes)
  while(t!=NULL &&count<index-1){
    //go through nodes and increase count
    t = t->next;
    count++;
  }
  //out of bounds
  if(t==NULL){
    free(cur_node);
    return;
  }
  //connecting nodes
  cur_node->next = t->next;
  t->next= cur_node;
}

elem list_remove_from_back(list_t *l) { 
  node_t *t =l->head; 
  if(l==NULL || l->head==NULL){
    return -1;
  }
  //list only contains one element 
  if(t->next==NULL){
    elem value = t->value;
    free(t);
    l->head=NULL;
    return value;
  }
  //want to delete next node
  while(t->next->next!=NULL){
    t= t->next;
  }
  node_t *deleted_node = t->next;
  elem value = deleted_node->value;
  free(deleted_node);
  t->next=NULL;
  return value;
  
  }
elem list_remove_from_front(list_t *l) { 
  node_t *t= l->head;
  if(l==NULL || l->head==NULL){
    return -1;
  }
 //getting the value at the front
  elem value = t->value;
  //make head the next node
  l->head=t->next;
  //free node
  free(t);
  return value;
  }
elem list_remove_at_index(list_t *l, int index) { 
  node_t *t = l->head; 
  if(l==NULL || l->head ==NULL || index<0){
    return -1;
  }
  //if index is 1, we're removing from the front
  if(index==1){
    elem value = t->value;
    l->head = t->next;
    free(t);
    return value;
  }
  int count= 1;
  //want to stop the count 1 prior to the index so we can connect the nodes correctly
  while(t!=NULL && count < index-1){
    t=t->next;
    count++;
  }
  if(t==NULL || t->next==NULL){
    return -1;
  }
  //t->next is pointing to the node that will be deleted
  node_t *deleted_node = t->next;
  elem value = deleted_node->value;
  //set the next value of the current node to point to the deleted node's next (connecting nodes)
  t->next = deleted_node->next;
  free(deleted_node);
  return value;

 }

bool list_is_in(list_t *l, elem value) { 
  if(l==NULL) return false;
  node_t *t = l->head;
  while(t!=NULL){
    //iterating through nodes and checking value
    if(t->value==value){
      return true;
    }
    t=t->next;
  }
  return false;
 }
elem list_get_elem_at(list_t *l, int index) { 
  if(l==NULL|| l->head==NULL||index<1){
    return -1;
  }
  node_t *t = l->head;
  int count =1;
  while(t!=NULL){
    //iterating through nodes and checking Index
    //then retrieving value
    if(count==index){
      return t->value;
    }
    t=t->next;
    count++;
  }
  return -1;
 }
int list_get_index_of(list_t *l, elem value) { 
  if(l==NULL|| l->head==NULL){
    return -1;
  }
  node_t *t = l->head;
  int index = 1;
  while(t!=NULL){
    //iterating through nodes and checking values
    //retrieving index
    if(t->value == value){
      return index;
    }
    t=t->next;
    index++;
  }
  return -1;
 }

