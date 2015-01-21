/* Commandline view implementation */

#include <stdio.h>
#include <string.h>

#include "../inc/cmd_view.h"

// cursor movement to skip cards
#define CUR_UP "\033[1A"
#define CUR_DN "\033[1B"
#define CUR_RT "\033[5C"
#define CUR_LT "\033[5D"

// clear screen
#define CLEAR "\033[2J"

// colors
#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

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
	for (int i = 0; i < stackSize(handP); ++i)
	{
		viewCard(&handP->cards[i],listRank,listSuit);
	}
	printf("\n");
}

void viewHandCol(stackT *handP, const char **listRank, const char **listSuit)
{
	for (int i = 0; i < stackSize(handP); ++i)
	{
		viewCardLn(&handP->cards[i],listRank,listSuit);
	}
	printf("\n");
}

void viewDeck(stackT *deckP, const char **listRank, const char **listSuit)
{
	// NOTE: game-specific implementation!

	// topmost position
	int top = stackSize(deckP);

	// print number of elements
	printf("%d ",top);

	// cards that face up
	int up = 0;
	{
		for (int i = 0; i < top; ++i)
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
	if (top-up > 0 )
	{
		viewCardLn(down,listRank,listSuit);
	}
	else
	{
		printf("\n");
	}
	cardDestroy(&down);
}

void viewWaste(stackT *wasteP)
{	
	int top = stackSize(wasteP);
	printf("%d ",top);
	for (int i = 0; i < top-1; ++i)
	{
		printf("[");
	}

	// print card face down
	cardT *down = cardNew(0,0,0);
	if (top > 0)
	{
		viewCardLn(down,NULL,NULL);
	}
	else
	{
		printf("\n");
	}
	cardDestroy(&down);
}

void viewTableRow(tableT *tableP, const char **listRank, const char **listSuit)
{
	// print attacking cards
	viewHandRow(tableP->att,listRank,listSuit);

	// print defending cards
	// get maximum of cards to print
	int range = stackSize(tableP->def);

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
	int height = stackSize(tableP->att);

	// move cursor back to top left
	for (int i = 0; i < height; ++i)
	{
		printf(CUR_UP);
	}
	// next column
	printf(CUR_RT);

	// print defending cards
	// get maximum of cards to print
	int range = stackSize(tableP->def);

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

void viewPlayer(playerT *playerP, partyT *partyP, int position, const char **listRank, const char **listSuit)
{
	char role[20];
	if (playerP == partyP->attacker)
	{
		strcpy(role,KRED"A"KNRM);
	}
	else if (playerP == partyP->defender)
	{
		strcpy(role,KGRN"D"KNRM);
	}
	printf("%s (%s)\n",playerP->name,role);
	viewHandRow(playerP->hand,listRank,listSuit);


	if (position >= 0)
	{
		for (int i = 0; i < position; ++i)
		{
			printf(CUR_RT);
		}
		printf("  *\n");
	}

}

void viewGame(partyT *partyP, tableT *tableP, stackT *deckP, stackT *wasteP, int position1, int position2, const char **listRank, const char **listSuit)
{
	// clear screen first
	printf(CLEAR);
	printf("\n\n");
	printf("Deck:\n");
	viewDeck(deckP,listRank,listSuit);
	printf("Waste:\n");
	viewWaste(wasteP);
	// WARNING: assumes exactly two players!!!
	viewPlayer(partyP->first,partyP,position1,listRank,listSuit);
	viewPlayer(partyP->first->next,partyP,position2,listRank,listSuit);
	printf("\n");
	printf("Table:\n");
	viewTableRow(tableP,listRank,listSuit);
}
