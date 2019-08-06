#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "lldeque.h"

// Structure representing a single link in a doubly linked list.
struct link {
  int value;
  struct link* next;
  struct link* prev;
};


struct lldeque {
  struct link* front_sentinel;
  struct link* back_sentinel;
};


struct lldeque* lldeque_create() {
  struct lldeque* deque = malloc(sizeof(struct lldeque));
  assert(deque);

  deque->front_sentinel = malloc(sizeof(struct link));
  assert(deque->front_sentinel);

  deque->back_sentinel = malloc(sizeof(struct link));
  assert(deque->back_sentinel);

  deque->front_sentinel->next = deque->back_sentinel;
  deque->front_sentinel->prev = NULL;

  deque->back_sentinel->next = NULL;
  deque->back_sentinel->prev = deque->front_sentinel;

  return deque;
}


void lldeque_free(struct lldeque* deque) {
  assert(deque);

  /*
   * Here, we're assuming that lldeque_remove_back() handles freeing the memory
   * associated with each removed element.
   */
  while (!lldeque_isempty(deque)) {
    lldeque_remove_back(deque);
  }
  free(deque->front_sentinel);
  free(deque->back_sentinel);
  free(deque);
}


int lldeque_isempty(struct lldeque* deque) {
  assert(deque);
  return deque->front_sentinel->next == deque->back_sentinel;
}


void _lldeque_add_before(struct link* link, int value) {
  struct link* new_link = malloc(sizeof(struct link));
  assert(new_link);

  new_link->value = value;
  new_link->next = link;
  new_link->prev = link->prev;

  link->prev = new_link;
  new_link->prev->next = new_link;
}


void lldeque_add_front(struct lldeque* deque, int value) {
  assert(deque);
  _lldeque_add_before(deque->front_sentinel->next, value);
}


void lldeque_add_back(struct lldeque* deque, int value) {
  assert(deque);
  _lldeque_add_before(deque->back_sentinel, value);
}


int lldeque_front(struct lldeque* deque) {
  assert(deque && !lldeque_isempty(deque));
  return deque->front_sentinel->next->value;
}


int lldeque_back(struct lldeque* deque) {
  assert(deque && !lldeque_isempty(deque));
  return deque->back_sentinel->prev->value;
}


int _lldeque_remove_link(struct link* link) {
  assert(link);

  int value = link->value;

  link->prev->next = link->next;
  link->next->prev = link->prev;

  free(link);
  return value;
}


int lldeque_remove_front(struct lldeque* deque) {
  assert(deque && !lldeque_isempty(deque));
  return _lldeque_remove_link(deque->front_sentinel->next);
}


int lldeque_remove_back(struct lldeque* deque) {
  assert(deque && !lldeque_isempty(deque));
  return _lldeque_remove_link(deque->back_sentinel->prev);
}

/***********************
 **
 ** Iterator interface
 **
 ***********************/

struct lldeque_iterator {
  struct lldeque* deque;
  struct link* curr;
};

struct lldeque_iterator* lldeque_iterator_create(struct lldeque* deque) {
  assert(deque);
  struct lldeque_iterator* iter = malloc(sizeof(struct lldeque_iterator));
  assert(iter);
  iter->deque = deque;
  iter->curr = deque->front_sentinel;
  return iter;
}

void lldeque_iterator_free(struct lldeque_iterator* iter) {
  assert(iter);
  free(iter);
}

int lldeque_iterator_has_next(struct lldeque_iterator* iter) {
  assert(iter);
  return iter->curr->next != iter->deque->back_sentinel;
}

int lldeque_iterator_next(struct lldeque_iterator* iter) {
  assert(iter && lldeque_iterator_has_next(iter));
  iter->curr = iter->curr->next;
  return iter->curr->value;
}

void lldeque_iterator_remove(struct lldeque_iterator* iter) {
  assert(iter && iter->curr != iter->deque->front_sentinel);
  iter->curr = iter->curr->prev;
  _lldeque_remove_link(iter->curr->next);
}

void lldeque_iterator_insert(struct lldeque_iterator* iter, int value) {
  assert(iter);
  _lldeque_add_before(iter->curr->next, value);
}

void lldeque_iterator_update(struct lldeque_iterator* iter, int value) {
  assert(iter && iter->curr != iter->deque->front_sentinel);
  iter->curr->value = value;
}
