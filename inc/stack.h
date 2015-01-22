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


/* BASIC STACK FUNCTIONS */

// Allocate memory for an array of card pointers of given size
stackT *stackInit(int size);

// Deallocate memory, reset member variables
// Needs double pointer to set given pointer to NULL
void stackDestroy(stackT **stackP);

// Push card (using its pointer) on stack
int stackPush(stackT *stackP, cardT *card);

// Return card pointer from top of stack, decrease top
cardT *stackPop(stackT *stackP);

// Return number of elements in stack
int stackSize(stackT *stackP);

// Return maximum number of elements in stack
int stackMaxSize(stackT *stackP);

// Check if stack is full/empty
int stackEmpty(stackT *stackP);
int stackFull(stackT *stackP);


/* CARD GAME SPECIFIC STACK FUNCTIONS */

// Swap element at given position with top element
int stackSwap(stackT *stackP, int pos);

// Move element at given position to top of the stack
// Shift all others appropriately
int stackMoveTop(stackT *stackP, int pos);

// Shuffle stack
void stackShuffle(stackT *stackP);

// Sort stack by suit/rank
void stackSortRank(stackT *stackP);
void stackSortSuit(stackT *stackP);

// Put all cards from the stack onto some other stack
// Returns error code, since stack sizes may mismatch
int stackClean(stackT *sourceP, stackT *destP);

#endif // STACK_H