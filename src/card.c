/* Implementation of basic card functions */

#include <stdlib.h>

#include "../inc/card.h"       

cardT *cardNew(int rank, int suit)
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

	return(cardP);
}

void cardDestroy(cardT **cardP)
{
	// free card memory
	free(*cardP);

	// reset pointer
	*cardP = NULL;
}

// Compare two cards by rank/suit
// Return values: a == b : 0; a > b : 1; a < b : -1;
int cardCompareRank(const void *aP, const void *bP)
{	
	// don't try to access NULL, will segfault
	if (aP == NULL || bP == NULL)
	{
		return(0);
	}

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
	if (aP == NULL || bP == NULL)
	{
		return(0);
	}
	
	cardT const *a = (cardT const *)aP;
	cardT const *b = (cardT const *)bP;
	
	return (a->suit > b->suit) - (a->suit < b->suit);
}