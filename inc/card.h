#ifndef CARD_H
#define CARD_H

/* CARD DATA TYPE
 *
 * PURPOSE
 * Holds the rule-independent properties of a single French playing card.
 * http://en.wikipedia.org/wiki/French_playing_cards
 * All information is incoded numerically.

 * EXAMPLE
 * cardT someCard = {1,2,0};
 *
 * NOTE
 * I was thinking a lot (maybe too much) about how to encode this information
 * in the nicest way possible. With strings it would be human-readable at the
 * data level, but comparing is just too cumbersome and storing strings takes
 * a lot of space.
 * So we now rely on external char arrays for the semantics. The ordering
 * of those is relevant for game mechanics. The card data type now only
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