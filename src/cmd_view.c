/* Commandline view implementation */

#include <stdio.h>

#include "../inc/cmd_view.h"

void viewCard(cardT *cardP, const char **listRank, const char **listSuit)
{
	// point local char* to char* in rank/suit lists
	// => AFAIK no additional memory use
	const char *rank = listRank[cardP->rank];
	const char *suit = listSuit[cardP->suit];

	if (cardP->face)
	{
		printf("[%2s%s]",rank,suit);
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


void viewHand(stackT *handP, const char **listRank, const char **listSuit)
{
	for (int i = 0; i <= handP->top; ++i)
	{
		viewCard(&handP->cards[i],listRank,listSuit);
	}
	printf("\n");
}