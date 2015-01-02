#ifndef STANDARD_H
#define STANDARD_H

/* Interface for traditional Durak rules */

// Lists are terminated with NULL to have "portable" bound checking
// according to this post: http://stackoverflow.com/a/13583763

// List of suits used
// 	H = Hearts
//	T = Tiles
//	C = Clubs
//	S = Spades
const char *listSuit[] = {"H","T","C","S",NULL};

// List of ranks used, in order of value
const char *listRank[] = {"6","7","8","9","10","J","Q","K","A",NULL};



/* GAME FUNCTIONS */

// Create playing deck using rank and suit lists
// NOTE: Automatically shuffles and finds a trump suit
// by uncovering the card at the bottom.
int deckCreate(stackT *deckP, char **listSuit, char **listRank);



/* RULES */

// Determine if card `a` beats card `b` using trump suit from the deck
int cardBeats(cardT *aP, cardT *bP, stackT *deckP);


/* TODO: Add more functions for rule-checking */




#endif // STANDARD_H