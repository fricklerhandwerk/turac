/*  
 * Card stack interface.
 * Original: https://www.cs.bu.edu/teaching/c/stack/array/download/stack.h
 */

#ifndef STACK_H
#define STACK_H


typedef struct stackT
{
  cardT *cards;
  int size;
  int top;
};

// Allocate memory for an array of cards of given size
int stackInit(stackT *stackP, int size);
// Deallocate memory, reset member variables
int stackDestroy(stackT *stackP);

// Push card on stack
int stackPush(stackT *stackP, cardT card);
// Return card from top of stack
cardT stackPop(stackT *stackP);

// Check if stack is full/empty
int stackEmpty(stackT *stackP);
int stackFull(stackT *stackP);

// Shuffle stack
int stackShuffle(stackt *stackP);

// Sort stack by suit/rank according to lists
int stackSortSuit(stackT *stackP,char **listSuit);
int stackSortRank(stackT *stackP,char **listRank);


#endif // STACK_H