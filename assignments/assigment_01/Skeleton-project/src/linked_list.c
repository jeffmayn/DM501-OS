/*
 * linked_list.c
 *
 *  Created on: Dec 24, 2013
 *      Author: jacob
 */
#include "linked_list.h"
#include <stdlib.h>
#include <stdio.h>

/* Added a void pointer to element as parameter because I want to initialise
	 the first node with an element. otherwise - because of the way
	 'add_element' function is implemented - we would have an empty node that
	 points to the first real node. The way I've implemented my counter is that
	 the first node in the list keep track of the total list-size. Hence,
	 whenever a new node is added, the first node's size is incremented.
*/
linked_list *init_linked_list(void *element) {
    linked_list *init;
    init = malloc(sizeof(linked_list));
    init -> data = element;
    init -> next = NULL;
    init -> previous = NULL;
    init -> size = 1; 						// I like counting from one. :-)
    return init;
}

/*
	The add function is implemented recursively. We first check whether a node
	has a next pointer, if not, we initialize and assign space to a new node in
	memory. Then the new node will point to its associated data, and set the
	next- and previous pointer to NULL. Finally, we will make a reference from
	the previous node to the new, and a reference from our new node to the
	previous and increment list size with one.
*/
void add_element(linked_list *list, void *element) {
	if(list->next) {
	    add_element(list->next, element);
	  } else {
	    linked_list *newList = init_linked_list(element);
	    list->next = newList;
	    newList->previous = list;
	  }
	  list->size++;
}

// Simply returns the list-size by looking at the current size pointer
int linked_list_size(linked_list *list) {
	return list->size;
}

// changed the argument to take a double pointer instead of a single pointer
// because we are removing the first element such that the input variable
// will point to the next list node.
void *remove_first(linked_list **list) {
void *out = (*list)->data;
linked_list *next = (*list)->next;
free(*list);
*list = next;
if(next){
  next->previous = NULL;
}
return out;
}

// changed the argument to take a double pointer instead of a single pointer
// because if we delete a node, that pointer would be invalid, with a double
// pointer we obtain the abilty to change the pointer pointing to the element.
int remove_element(linked_list **list, void *element) {
  if(!*list){
    return -1;
  } else if((*list)->data==element){
    if((*list)->next) (*list)->next->previous = (*list)->previous;
    remove_first(list);
    return 0;
  } else {
    const int retVal = remove_element(&(*list)->next, element);
    // plus one to keep size of list correct.
    (*list)->size -= retVal+1;
    return retVal;
  }
}
