/* Card interface */

#ifndef CARD_H
#define CARD_H

/* CARD DATA TYPE
 *
 * PURPOSE
 * Holds all the rule-independent properties of a single French playing card.
 * http://en.wikipedia.org/wiki/French_playing_cards
 *		
 * EXAMPLE
 * card someCard = {"Ace","Spades",UP};
 *
 * NOTE
 * While the binary encoding of the card's facing is more efficient,
 + it may make sense to encode it as a string (e.g. "up"/"down".
 + This would spare the macro name space of additional definitions
 + and keep the data structure more human-readble.
*/

typedef struct
{
	int rank;
	int suit;
	int face;
} cardT;

/* BASIC CARD FUNCTIONS */

// Create card with given rank and suit and facing
cardT *cardNew(int rank, int suit, int face);

// Free memory reserved for card struct
void cardDestory(cardT **cardP);

// Set card facing
void cardSetFace(cardT *cardP, int face);

// Compare two cards by rank/suit
// Return values: a == b : 0; a > b : 1; a < b : -1;
int cardCompareRank(const void *a, const void *b);
int cardCompareSuit(const void *aP, const void *bP);

#endif // CARD_H