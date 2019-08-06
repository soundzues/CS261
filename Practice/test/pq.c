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

    struct pq_elem* new_elem = malloc(sizeof(struct pq_elem));
    new_elem->item = item;
    new_elem->priority = priority;
    
    /*
 *      * Figure out where in the heap array to insert the new element represented
 *           * by new_elem and insert it.
 *                */
    
    
    int ch_idx = dynarray_size(pq->heap)-1; // last index = child index
    dynarray_insert(pq->heap,ch_idx,new_elem); // insert new element to last index
    
    while(ch_idx != 0){
        int pa_idx = (ch_idx-1)/2;
        struct pq_elem* pa = dynarray_get(pq->heap,pa_idx);
        if(new_elem->priority >= pa->priority){
            break;
        }
        
        dynarray_set(pq->heap,ch_idx,pa);
        dynarray_set(pq->heap, pa_idx, new_elem);
        ch_idx = pa_idx;
    
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
    
    struct pq_elem* first_elem = NULL;
    
    /*
 *      * Determine what index in the heap array corresponds to the highest-priority
 *           * element (i.e. the one with the lowest priority value), and store the
 *                * value there in first_elem.
 *                     */
    
    first_elem = dynarray_get(pq->heap,0);
    
    /*
 *      * Return the extracted item, if the element taken out of the priority
 *           * queue is not NULL.
 *                */
    if (first_elem != NULL) {
        return first_elem->item;
    } else {
        return NULL;
    }
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
    
    struct pq_elem* first_elemnt;
    first_elemnt = dynarray_get(pq->heap,0);
	
    struct pq_elem* last_elem = dynarray_get(pq->heap, -1);
    dynarray_remove(pq->heap,-1);
    
   
    if(pq_isempty(pq)){
        if (first_elemnt != NULL) {
            void* item = first_elemnt->item;
            free(first_elemnt);
            return item;
        } else {
            return NULL;
        }
    }     
    dynarray_set(pq->heap, 0, last_elem);
    
    int ch_idx = dynarray_size(pq->heap)-1;
    int pa_idx = 0;
    int tem =1;
    while(tem <= ch_idx){
        if(tem < ch_idx){
            struct pq_elem* a = dynarray_get(pq->heap,tem);
            struct pq_elem* b = dynarray_get(pq->heap,tem+1);
            if(a->priority > b->priority){
                tem++;
            }
        } 
        
        struct pq_elem* min = dynarray_get(pq->heap,tem);
        if(last_elem->priority <= min->priority){
            break;
        } 
        
        dynarray_set(pq->heap,pa_idx,min);
        pa_idx = tem;
        tem = 2*pa_idx+1;
        
    }
 
    
    dynarray_set(pq->heap,pa_idx,last_elem);
    
    if (first_elemnt != NULL) {
        return first_elemnt;
    } else {
        return NULL;
    }
    
}
