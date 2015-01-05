/*  
 * Card stack interface.
 * Original: https://www.cs.bu.edu/teaching/c/stack/array/download/stack.h
 */

#ifndef STACK_H
#define STACK_H

// Allocate memory for an array of cards of given size
void stackInit(stackT *stackP, int size);
// Deallocate memory, reset member variables
void stackDestroy(stackT *stackP);

// Push card on stack
void stackPush(stackT *stackP, cardT card);
// Return card from top of stack
cardT stackPop(stackT *stackP);

// Check if stack is full/empty
int stackEmpty(stackT *stackP);
int stackFull(stackT *stackP);

#endif // STACK_H