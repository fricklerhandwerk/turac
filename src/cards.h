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

#define UP 1
#define DN 0

typedef struct cardT
{
	char* rank;
	char* suit;
	int face;
};

/* BASIC CARD FUNCTIONS */

// Set card facing
int cardFaceUp(cardT *card);
int cardFaceDown(cardT *card);

// Compare two cards by rank/suit
// Takes a list of ranks/suits from the rules file to determine rank/suit values
// Return values: a == b : 0; a > b : 1; a < b : -1;
int cardCompareRank(cardT *a, cardT *b, char **listRank);
int cardCompareSuit(cardT *a, cardT *b, char **listSuit);

#endif // CARD_H