/* 
 * Developed by R. E. Bryant, 2017
 * Extended to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q =  malloc(sizeof(queue_t));
    /* What if malloc returned NULL? */
    if(q == NULL){
	return NULL;
    }
    //initialize queue
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
  /*IF QUEUE IS EMPTY, RETURN NULL AND DO NOTHING*/
    if(q == NULL){
	return;
    }
    /*free_string goes through queue and frees each character*/

    /*previous pointer accesses the elements which were freed by free_string and then frees the element*/ 

    list_ele_t *free_string = q->head;
    list_ele_t *previous = q->head;

    while(free_string != NULL){
	free(free_string->value);
	previous = free_string;
	free_string = previous->next;
	free(previous);
    }
    /* How about freeing the list elements and the strings? */
    /* Free queue structure */
    free(q);
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    list_ele_t *newh;
    int string_size;
    char *copy_string;
    /* What should you do if the q is NULL? */
    if(q == NULL){
    	return false;
    }


    newh = malloc(sizeof(list_ele_t));
    if(newh == NULL){
	return false;
    }


    /* Don't forget to allocate space for the string and copy it */
    string_size = strlen(s) + 1;
    copy_string = malloc(string_size * sizeof(char));

    /* What if either call to malloc returns NULL? */

    if(copy_string == NULL){
	free(newh);
	return false;
    }

    
    strcpy(copy_string, s);
    newh->value = copy_string;
    
    if(q->head == NULL){
    /*head and tail are initialized to same new element*/
	q->head = q->tail = newh;
	newh->next = NULL;
    }
    /*list is not empty*/
    else{
    /*new head is set to old head*/
	newh->next = q->head;
    /*new element inserted at head position*/
	q->head = newh;
    }


    q->size++;
    return true;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */

    /*IF QUEUE DOES NOT EXIST*/
    if(q == NULL){
	return false;
    }
    
    char *copy_string;
    list_ele_t *newtail;
    int string_size;
    string_size = strlen(s) + 1;

    /*CREATE SPACE FOR NEW ELEMENT AND MAKE POINTER POINT TO THIS*/
    newtail = malloc(sizeof(list_ele_t));
    if(newtail == NULL){
	return false;
    }

    /*IF FUNCTION FAILS, FREE THE SPACE CREATED BEFORE*/
    copy_string = malloc(string_size * sizeof(char));
    if(copy_string == NULL){
	free(newtail);
	return false;
    }

    strcpy(copy_string, s);
    newtail->value = copy_string;
    newtail->next = NULL;
    /*if list is empty, head and tail initialized to first element*/
    if(q->head == NULL){
	q->head = newtail;
	q->tail = newtail;
	q->size++;
	return true;
    }
    /*insert element after tail*/
    q->tail->next = newtail;
    /*set tail to new last element*/
    q->tail = newtail;
    q->size++;


    return true;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    /*IF Q IS EMPTY*/
    if(q == NULL){
	return false;
    }
    /*IF Q IS NULL*/
    if(q->head == NULL){
	return false;
    }

    /*IF sp is not NULL, copy the string*/
    if(sp != NULL){
	strncpy(sp, q->head->value, bufsize - 1);
	*(sp + bufsize -1) = '\0';
    }

    /*Free space*/
    list_ele_t *x = q->head;
    q->head = q->head->next;

    free(x->value);
    free(x);
    q->size--;
    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */

    if(q == NULL){
	return 0;
    }

    return q->size;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    /*IF Q IS EMPTY*/
    if(q == NULL || q->head == NULL){
	return;
    }

    list_ele_t *x;
    list_ele_t *previous;
    list_ele_t *next;


    previous = NULL;
    x = q->head;
    next = NULL;
    q->tail = q->head;
   
    //while head != NULL
    while(x != NULL){
    //store next so we dont lose the link
	next = x->next;
    //reverse current node's pointer
	x->next = previous;
    //Move ahead one position
	previous = x;
	x = next;
    }

    q->head = previous;
    


}

