/*  
* Card stack interface.
* Original: https://www.cs.bu.edu/teaching/c/stack/array/download/stack.h
*/

#ifndef STACK_H
#define STACK_H

#include "card.h"

typedef struct
{
	cardT *cards;
	int size;
	int top;
} stackT;

// Allocate memory for an array of card pointers of given size
stackT *stackInit(int size);

// Deallocate memory, reset member variables
// Needs double pointer to set given pointer to NULL
void stackDestroy(stackT **stackP);

// Push card (using its pointer) on stack
int stackPush(stackT *stackP, cardT *card);

// Return card pointer from top of stack, decrease top
cardT *stackPop(stackT *stackP);

// Return number of elements currently in stack
int stackTop(stackT *stackP);

// Return size of stack
int stackSize(stackT *stackP);

// Check if stack is full/empty
int stackEmpty(stackT *stackP);
int stackFull(stackT *stackP);

// Shuffle stack
void stackShuffle(stackT *stackP);

// Sort stack by suit/rank
void stackSortRank(stackT *stackP);
void stackSortSuit(stackT *stackP);

#endif // STACK_H