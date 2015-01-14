/* Commandline view implementation */

#include <stdio.h>

#include "../inc/cmd_view.h"

// cursor movement to skip cards
#define CUR_UP "\033[1A"
#define CUR_DN "\033[1B"
#define CUR_RT "\033[5C"
#define CUR_LT "\033[5D"

void viewCard(cardT *cardP, const char **listRank, const char **listSuit)
{
	if (cardP->face)
	{
		printf("[%2s%s]",listRank[cardP->rank],listSuit[cardP->suit]);
	}
	else
	{
		printf("[xxx]");
	}
}

void viewCardLn(cardT *cardP, const char **listRank, const char **listSuit)
{
	viewCard(cardP,listRank,listSuit);
	printf("\n");
}


void viewHandRow(stackT *handP, const char **listRank, const char **listSuit)
{
	for (int i = 0; i <= stackTop(handP); ++i)
	{
		viewCard(&handP->cards[i],listRank,listSuit);
	}
	printf("\n");
}

void viewHandCol(stackT *handP, const char **listRank, const char **listSuit)
{
	for (int i = 0; i <= stackTop(handP); ++i)
	{
		viewCardLn(&handP->cards[i],listRank,listSuit);
	}
	printf("\n");
}

void viewDeck(stackT *deckP, const char **listRank, const char **listSuit)
{
	// NOTE: game-specific implementation!

	// topmost position
	int top = stackTop(deckP);

	// print number of elements
	printf("%d ",top+1);

	// cards that face up
	int up = 0;
	{
		for (int i = 0; i <= top; ++i)
		{
			// assuming only up/down binary
			if(deckP->cards[i].face)
			{
				viewCardLn(&deckP->cards[i],listRank,listSuit);
				up++;
			}
		}
	}


	// stack cards
	for (int i = 0; i < top-up; ++i)
	{
		printf("[");
	}

	// print card face down
	cardT *down = cardNew(0,0,0);
	if (top-up >= 0 )
	{
		viewCardLn(down,listRank,listSuit);
	}


	printf("\n");
}



void viewTableRow(tableT *tableP, const char **listRank, const char **listSuit)
{
	// print attacking cards
	viewHandRow(tableP->att,listRank,listSuit);

	// print defending cards
	// get maximum of cards to print
	int range = stackTop(tableP->def)+1;

	// walk through `beats` array
	for (int i = 0; i < range; ++i)
	{
		int beats = tableP->beats[i];
		// depending on beat position, move cursor
		for (int j = 0; j < beats; ++j)
		{
			printf(CUR_RT);
		}

		viewCard(&tableP->def->cards[i],listRank,listSuit);

		// move cursor back
		for (int j = 0; j <= beats; ++j)
		{
			printf(CUR_LT);
		}
	}
	printf("\n");
}

void viewTableCol(tableT *tableP, const char **listRank, const char **listSuit)
{
	// print attacking cards
	viewHandCol(tableP->att,listRank,listSuit);
	int height = stackTop(tableP->att)+1;

	// move cursor back to top left
	for (int i = 0; i <= height; ++i)
	{
		printf(CUR_UP);
	}
	// next column
	printf(CUR_RT);

	// print defending cards
	// get maximum of cards to print
	int range = stackTop(tableP->def)+1;

	// walk through `beats` array
	for (int i = 0; i < range; ++i)
	{
		int beats = tableP->beats[i];
		// depending on beat position, move cursor down
		for (int j = 0; j < beats; ++j)
		{
			printf(CUR_DN);
		}

		viewCard(&tableP->def->cards[i],listRank,listSuit);

		// move cursor back up
		for (int j = 0; j < beats; ++j)
		{
			printf(CUR_UP);
		}
		// back to left side
		printf(CUR_LT);
	}
	// move down to end of column
	for (int i = 0; i < height-1; ++i)
	{
		printf(CUR_DN);
	}
	printf(CUR_LT);
	printf("\n");
}
