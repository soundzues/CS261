#include <stdio.h>

#include "lldeque.h"

#define NUM_TEST_ELEMENTS 32

int main(int argc, char** argv) {

  struct lldeque* q = lldeque_create();

  for (int i = 0; i < NUM_TEST_ELEMENTS; i++) {
    lldeque_add_front(q, i);
  }
  printf("== Deque contents, add front, remove back (in the order removed): ");
  while (!lldeque_isempty(q)) {
    printf("%4d,", lldeque_remove_back(q));
  }
  printf(" empty\n\n");

  for (int i = 0; i < NUM_TEST_ELEMENTS; i++) {
    lldeque_add_back(q, i);
  }
  printf("== Deque contents, add back, remove front (in the order removed): ");
  while (!lldeque_isempty(q)) {
    printf("%4d,", lldeque_remove_front(q));
  }
  printf(" empty\n");

  lldeque_free(q);

}
