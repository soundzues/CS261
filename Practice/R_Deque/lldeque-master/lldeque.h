/*
 * A definition for a linked list-based deque implementation.
 */

#ifndef __LLDEQUE_H
#define __LLDEQUE_H

/*
 * Structure used to represent a linked list-based deque.
 */
struct lldeque;

/*
 * Creates a new, empty deque.
 */
struct lldeque* lldeque_create();

/*
 * Free the memory associated with a deque.
 */
void lldeque_free(struct lldeque* deque);

/*
 * Returns 1 if the given deque is empty or 0 otherwise.
 */
int lldeque_isempty(struct lldeque* deque);

/*
 * Endeque a new value at the front of a deque.
 *
 * @param value the new value to be added to the front deque.
 */
void lldeque_add_front(struct lldeque* deque, int value);

/*
 * Endeque a new value at the back of a deque.
 *
 * @param value the new value to be added to the back deque.
 */
void lldeque_add_back(struct lldeque* deque, int value);

/*
 * Returns a deque's front value.
 */
int lldeque_front(struct lldeque* deque);

/*
 * Returns a deque's back value.
 */
int lldeque_back(struct lldeque* deque);

/*
 * Removes the front element from a deque and returns its value.
 */
int lldeque_remove_front(struct lldeque* deque);

/*
 * Removes the back element from a deque and returns its value.
 */
int lldeque_remove_back(struct lldeque* deque);


/***********************
 **
 ** Iterator interface
 **
 ***********************/

/*
 * Iterator structure for iterating through a linked list-based deque.
 */
struct lldeque_iterator;

/*
 * Allocates a new deque iterator and initializes it to the front element of
 * the given deque.
 */
struct lldeque_iterator* lldeque_iterator_create(struct lldeque* deque);

/*
 * Frees the memory associated with an iterator.
 */
void lldeque_iterator_free(struct lldeque_iterator* iter);

/*
 * Returns 0 if there are no more elements to move to in the deque or 1 if
 * there is at least one more element accessible via next().
 */
int lldeque_iterator_has_next(struct lldeque_iterator* iter);

/*
 * Moves the iterator to the next element in thge deque and returns its value.
 */
int lldeque_iterator_next(struct lldeque_iterator* iter);

/*
 * Removes the element from the deque currently pointed to by iter.
 */
void lldeque_iterator_remove(struct lldeque_iterator* iter);

/*
 * Inserts a new element with the specified value into the deque at the
 * position after the element currently pointed to by iter.
 */
void lldeque_iterator_insert(struct lldeque_iterator* iter, int value);

/*
 * Updates the element currently pointed to by iter to the specified value.
 */
void lldeque_iterator_update(struct lldeque_iterator* iter, int value);

#endif
