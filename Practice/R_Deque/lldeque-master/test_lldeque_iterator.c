#include <stdio.h>

#include "lldeque.h"

#define NUM_TEST_ELEMENTS 32

int main(int argc, char** argv) {

  struct lldeque* q = lldeque_create();

  for (int i = 0; i < NUM_TEST_ELEMENTS; i++) {
    lldeque_add_back(q, i);
  }

  // Remove all elements that are not divisible by 4.
  struct lldeque_iterator* iter = lldeque_iterator_create(q);
  while (lldeque_iterator_has_next(iter)) {
    int cur = lldeque_iterator_next(iter);
    if (cur % 4) {
      lldeque_iterator_remove(iter);
    }
  }
  lldeque_iterator_free(iter);

  // Print all remaining elements in the deque.
  printf("== Elements in the deque that are divisible by 4: ");
  iter = lldeque_iterator_create(q);
  while (lldeque_iterator_has_next(iter)) {
    int cur = lldeque_iterator_next(iter);
    printf("%4d,", cur);
  }
  lldeque_iterator_free(iter);
  printf(" done\n");

}
