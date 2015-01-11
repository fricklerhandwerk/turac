/* Implementation of basic card functions */

#include <stdlib.h>

#include "../inc/card.h"       

// Create card with given rank and suit and facing
cardT *cardNew(int rank, int suit, int face)
{
	// allocate memory for card struct
	cardT *cardP = malloc(sizeof(cardT));

	// handle allocation errors
	if (cardP == NULL)
	{
		return(NULL);
	}

	// write values
	cardP->rank = rank;
	cardP->suit = suit;
	cardP->face = face;

	return(cardP);
}

// Set card facing
void cardSetFace(cardT *cardP, int face)
{
	// NOTE: rule-agnostic - sets whatever value it gets!
	cardP->face = face;
}

// Compare two cards by rank/suit
// Return values: a == b : 0; a > b : 1; a < b : -1;
int cardCompareRank(cardT *a, cardT *b)
{
	// using this method (lots of street cred attached):
	// http://stackoverflow.com/a/10997428
	return (a->rank > b->rank) - (a->rank < b->rank);
}

int cardCompareSuit(cardT *a, cardT *b)
{
	return (a->suit > b->suit) - (a->suit < b->suit);
}