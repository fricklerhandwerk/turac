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

	// handle allocation errors
	if (stackP == NULL)
	{
		return(NULL);
	}

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
	// don't push on full stacks and don't push empty cards
	if (stackFull(stackP) || cardP == NULL)
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

int stackSize(stackT *stackP)
{
	return stackP->top+1;
}

int stackMaxSize(stackT *stackP)
{
	return stackP->size;
}

int stackSwap(stackT *stackP, int pos)
{
	// refuse to work on illegal positions
	if (pos < 0 || pos > stackP->top)
	{
		return(EXIT_FAILURE);
	}

	cardT temp = stackP->cards[pos];
	stackP->cards[pos] = stackP->cards[stackP->top];
	stackP->cards[stackP->top] = temp;

	return(EXIT_SUCCESS);
}

int stackMoveTop(stackT *stackP, int pos)
{
	// refuse to work on illegal positions
	if (pos < 0 || pos > stackP->top)
	{
		return(EXIT_FAILURE);
	}

	// remember the card at pos
	cardT temp = stackP->cards[pos];
	int i = pos;

	// shift all others one position back
	for (; i < stackP->top; ++i)
	{
		 //printf("card: %d\n",i);
		 stackP->cards[i] = stackP->cards[i+1]; 
	}

	// put temp on top
	stackP->cards[i] = temp;

	return(EXIT_SUCCESS);
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
	// save top position locally
	int top = stackP->top;

	// base case
	if (top < 1) {return;}

	// throw dice
	srand(time(NULL));

	// swap entries in positions top and some random r
	// 0 <= r < top
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

// Sort stack by rank/suit
void stackSortRank(stackT *stackP)
{
	qsort(stackP->cards,stackSize(stackP),sizeof(cardT),&cardCompareRank);
}

void stackSortSuit(stackT *stackP)
{
	qsort(stackP->cards,stackSize(stackP),sizeof(cardT),&cardCompareSuit);
}

int stackClean(stackT *sourceP, stackT *destP)
{
	// check if there is enough space at destination
	if (stackSize(sourceP) > (stackMaxSize(destP) - stackSize(destP)))
	{
		return(EXIT_FAILURE);
	}

	// move stack elements
	while (!stackEmpty(sourceP))
	{
		cardT *pop = stackPop(sourceP);

		// take care of memory errors, in case anything breaks on the way
		if (stackPush(destP,pop) == EXIT_FAILURE)
		{
			// put back refused card
			stackPush(sourceP,pop);
			return(EXIT_FAILURE);
		}
	}

	return(EXIT_SUCCESS);
}