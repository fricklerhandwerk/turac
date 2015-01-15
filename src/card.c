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

// Free memory reserved for card struct
void cardDestroy(cardT **cardP)
{
	// free card memory
	free(*cardP);
	// reset pointer
	*cardP = NULL;
}

// Set card facing
void cardSetFace(cardT *cardP, int face)
{
	// NOTE: rule-agnostic - sets whatever value it gets!
	cardP->face = face;
}

// Compare two cards by rank/suit
// Return values: a == b : 0; a > b : 1; a < b : -1;
int cardCompareRank(const void *aP, const void *bP)
{
	// casting generic pointers to what we need here using this method
	// http://www.anyexample.com/programming/c/qsort__sorting_array_of_strings__integers_and_structs.xml
	
	cardT const *a = (cardT const *)aP;
	cardT const *b = (cardT const *)bP;
	
	// comparison using this method (lots of street cred attached):
	// http://stackoverflow.com/a/10997428
	return (a->rank > b->rank) - (a->rank < b->rank);
}

int cardCompareSuit(const void *aP, const void *bP)
{
	cardT const *a = (cardT const *)aP;
	cardT const *b = (cardT const *)bP;
	
	return (a->suit > b->suit) - (a->suit < b->suit);
}