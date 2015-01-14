/* Card stack implementation with arrays */

#include <stdlib.h>
#include <time.h>
#include "stack.h"


stackT *stackInit(int size)
{
	// allocate memory for array of cards
	cardT *cards;
	cards = malloc(sizeof(cardT) * size);

	// handle allocation errors
	if (cards == NULL)
	{
		return(NULL);
	}

	// create new stack
	stackT *stackP;
	stackP = malloc(sizeof(stackT));

	// write initial values
	stackP->cards = cards;
	stackP->top = -1;
	stackP->size = size;

	return(stackP);
}

void stackDestroy(stackT **stackP)
{
	// free card array memory and reset pointer
	free((*stackP)->cards);
	(*stackP)->cards = NULL;
	
	// free stack memory and reset pointer
	free(*stackP);
	*stackP = NULL;
}

int stackPush(stackT *stackP, cardT *cardP)
{
	if (stackFull(stackP))
	{
		return(EXIT_FAILURE);
	}
	// put given card pointer on top of element
	// increase top counter
	stackP->cards[++stackP->top] = *cardP;

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
	return &stackP->cards[stackP->top--];
}

int stackNumElem(stackT *stackP)
{
	return stackP->top + 1;
}

int stackEmpty(stackT *stackP)
{
	return stackP->top < 0;
}

int stackFull(stackT *stackP)
{
	return stackP->top >= stackP->size - 1;
}


// Shuffle stack
void stackShuffle(stackT *stackP)
{
	// throw dice
	srand(time(NULL));

	// base case
	if (stackP->top <= 1)
	{
		return;
	}
	
	// swap entries in positions top and some random r
	// 0 <= r < top
	int top = stackP->top;
	int r = rand () % top;
	
	cardT temp = stackP->cards[top];
	stackP->cards[top] = stackP->cards[r];
	stackP->cards[r] = temp;
	
	// decrease top temporarily
	stackP->top--;
	// go down recursion to shuffle rest of stack
	stackShuffle(stackP);
	// reset top
	stackP->top++;
	
	return;
}


// Sort stack by rank/siut
void stackSortRank(stackT *stackP)
{
	qsort(stackP->cards,stackP->top+1,sizeof(cardT),&cardCompareRank);
}

void stackSortSuit(stackT *stackP)
{
	qsort(stackP->cards,stackP->top+1,sizeof(cardT),&cardCompareSuit);
}
