/* Card stack implementation with arrays */

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"       


stackT *stackInit(int size)
{
  // allocate memory for array of card pointers
  cardT **cards;
  cards = malloc(sizeof(cards) * size);

  // handle allocation errors
  if (cards == NULL)
  {
    return(NULL);
  }

  // create new stack
  stackT *stackP;

  // write initial values
  stackP->cards = cards;
  stackP->top = -1;
  stackP->size = size;

  return(stackP);
}

void stackDestroy(stackT *stackP)
{
  // free card array memory
  free(stackP->cards);
  // free stack pointer
  free(stackP);
}

int StackPush(stackT *stackP, cardT *cardP)
{
  if (stackFull(stackP))
  {
    return(EXIT_FAILURE);
  }
  // put given card pointer on top of element
  // increase top counter
  stackP->cards[++stackP->top] = cardP;

  return(EXIT_SUCCESS);
}

cardT *stackPop(stackT *stackP)
{
  if (stackEmpty(stackP))
  {
    return(NULL);
  }
  // return card pointer from top of stack
  // decrease top counter
  return stackP->cards[stackP->top--];
}

int stackEmpty(stackT *stackP)
{
  return stackP->top < 0;
}

int stackFull(stackT *stackP)
{
  return stackP->top >= stackP->size - 1;
}

/*
// Shuffle stack
void stackShuffle(stackt *stackP);

// Sort stack by suit/rank according to lists
void stackSortSuit(stackT *stackP,char **listSuit);
void stackSortRank(stackT *stackP,char **listRank);
*/




