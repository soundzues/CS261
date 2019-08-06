/*
 * This file contains the implementation of a priority queue.
 *
 * You must complete the implementations of these functions:
 *   pq_insert()
 *   pq_first()
 *   pq_remove_first()
 */

#include <stdlib.h>
#include <assert.h>

#include "dynarray.h"
#include "pq.h"

// This is the initial capacity that will be allocated for the heap.
#define INITIAL_HEAP_CAPACITY 16

/*
 * This is the definition of the structure we will use to represent the
 * priority queue.  It contains only a dynamic array, which will be used to
 * store the heap underlying the priority queue.
 */
struct pq {
  struct dynarray* heap;
};


/*
 * This is an auxiliary structure that we'll use to represent a single element
 * in the priority queue.  It contains two fields:
 *
 *   priority - the priority value assigned to the item
 *   item - the pointer to the data item represented by this element
 *
 * Both of these will come directly from the corresponding values passed to
 * pq_insert().
 */
struct pq_elem {
  int priority;
  void* item;
};


/*
 * This function allocates and initializes a new priority queue.
 *
 * You should not modify this function.
 */
struct pq* pq_create() {
  struct pq* pq = malloc(sizeof(struct pq));
  assert(pq);
  pq->heap = dynarray_create(INITIAL_HEAP_CAPACITY);
  return pq;
}


/*
 * This function frees the memory associated with a priority queue.
 *
 * You should not modify this function.
 */
void pq_free(struct pq* pq) {
  assert(pq);
  while (!pq_isempty(pq)) {
    pq_remove_first(pq);
  }
  dynarray_free(pq->heap);
  free(pq);
}

/*
 * This function returns 1 if the given priority queue is empty or 0
 * otherwise.
 *
 * You should not modify this function.
 */
int pq_isempty(struct pq* pq) {
  assert(pq);
  return dynarray_size(pq->heap) == 0;
}


/*
 * This function inserts a new item with a specified priority into a priority
 * queue.
 *
 * You should complete the implementation of this function.  The first part
 * is done for, where a new element is created to be placed into the dynamic
 * array underlying the priority queue.
 */
void pq_insert(struct pq* pq, void* item, int priority) {
 	assert(pq);
	
	int size, last_elem;
	struct pq_elem *temp;
	
	temp = malloc(sizeof(struct pq_elem));//allocate space for newly inserted element 
	temp->item = item;
	temp->priority = priority; 

	size = dynarray_size(pq->heap);//size of the heap
	last_elem = size-1;//prelocate last element 
	dynarray_insert(pq->heap, last_elem, temp);//insert new element in the last index

	while(last_elem != 0)//make sure we are not at beginning of the array
	{
		struct pq_elem *parent;//points to parent 
		int parent_index = (((last_elem)-1)/2);//locates parrent using the formula
		parent = dynarray_get(pq->heap, parent_index);//get function to get parent
		
		if(temp->priority >= parent->priority)//if child prioroity is higher than parrent stop found the right place to insert
		{
			break;
		}
		else//swap
		{
			dynarray_set(pq->heap, last_elem, parent);//parent becomes child
			dynarray_set(pq->heap, parent_index, temp);//child becomes parent
			last_elem = parent_index;//change last elem to point to last elem
		}	
	}	
}


/*
 * This function returns the first (highest-priority) item from a priority
 * queue without removing it.
 *
 * You should complete the implementation of this function.
 */
void* pq_first(struct pq* pq) {
  	assert(pq);
  	assert(dynarray_size(pq->heap) > 0);
	
	struct pq_elem *first_element;
	first_element = dynarray_get(pq->heap,0);//gets the first element in the heap
	
	return first_element->item;//returns first element 	
}


/*
 * This function removes the first (highest-priority) element from a priority
 * queue and returns its value.
 *
 * You should complete this function.
 */

void* pq_remove_first(struct pq* pq) {
  	assert(pq);
  	assert(dynarray_size(pq->heap) > 0);
	
	struct pq_elem *first_element;
	first_element = dynarray_get(pq->heap,0);//locate and store the first element 

	struct pq_elem *last_element;
	last_element = dynarray_get(pq->heap,-1);//get and store the last element 
	dynarray_remove(pq->heap,-1);//remove the last element

	if(pq_isempty(pq))
	{
		if(first_element != NULL)
		{
			void *item = first_element->item;
			free(first_element);
			return item;
		}
		else
		{
			return NULL;
		}
	}

 

	dynarray_set(pq->heap, 0, last_element);//replace the first element with last

	int heap_size = dynarray_size(pq->heap);
	int child_index = (heap_size-1);
	int parent_index = 0;
	int temp_index = 1;

	while(temp_index <= child_index)
	{
		if(temp_index <= child_index)//compares two nodes and selects the smallest one
		{
			struct pq_elem *temp1 = dynarray_get(pq->heap, temp_index);//temps to compare and later swap
			struct pq_elem *temp2 = dynarray_get(pq->heap, temp_index+1);//depending on prioritu
			
			if(temp1->priority > temp2->priority)
			{
				temp_index++;
			}	
		}
	
		struct pq_elem *smallest = dynarray_get(pq->heap, temp_index);
		
		if(last_element->priority <= smallest->priority)//if child is bigger than parent stop
		{
			break;
		}
	
		//compare next child 
		dynarray_set(pq->heap, parent_index, smallest);
		parent_index = temp_index;
		temp_index = 2*parent_index+1;
	}

	dynarray_set(pq->heap, parent_index, last_element);
	
	if(first_element != NULL)
	{
		return first_element;
	}
	else
	{
		return NULL;
	}

}



	
	

