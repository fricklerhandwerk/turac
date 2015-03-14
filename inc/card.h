#ifndef CARD_H
#define CARD_H

/* CARD DATA TYPE
 *
 * PURPOSE
 * Holds the two rule-independent properties of a single French playing card.
 * http://en.wikipedia.org/wiki/French_playing_cards

 * EXAMPLE
 * cardT someCard = {1,2};
 *
 * NOTE
 * We rely on external char arrays for the semantics. The ordering
 * of those is relevant for game mechanics. The card data type only
 * stores a numeric value which is evaluated/interpreted somewhere else.
*/

typedef struct
{
	int rank;
	int suit;
} cardT;

/* BASIC CARD FUNCTIONS */

// Create card with given rank and suit and facing
cardT *cardNew(int rank, int suit);

// Free memory reserved for card struct
void cardDestroy(cardT **cardP);

// Compare two cards by rank/suit
// Return values: a == b : 0; a > b : 1; a < b : -1;
int cardCompareRank(const void *aP, const void *bP);
int cardCompareSuit(const void *aP, const void *bP);

#endif // CARD_H