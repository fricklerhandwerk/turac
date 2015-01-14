/* Commandline view implementation */

#include <stdio.h>

#include "../inc/cmd_view.h"

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
	for (int i = 0; i <= handP->top; ++i)
	{
		viewCard(&handP->cards[i],listRank,listSuit);
	}
	printf("\n");
}

void viewHandCol(stackT *handP, const char **listRank, const char **listSuit)
{
	for (int i = 0; i <= handP->top; ++i)
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

void viewTable(tableT *tableP, const char **listRank, const char **listSuit)
{
	viewHandRow(tableP->att,listRank,listSuit);
	viewHandRow(tableP->def,listRank,listSuit);

}
