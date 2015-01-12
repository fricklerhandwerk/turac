#ifndef STANDARD_H
#define STANDARD_H

/* Interface for traditional Durak rules */

/* GAME CONSTANTS */

// Lists are terminated with NULL to have "portable" bound checking
// according to this post: http://stackoverflow.com/a/13583763

// Suits used
enum SUIT
{
	HEARTS,
	TILES,
	CLUBS,
	SPADES,
};

//const char *listSuit[] = {"Hearts","Tiles","Clubs","Spades",NULL};

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
const char *listSuit[] = {KRED"\u2665"KNRM,KRED"\u2666"KNRM,"\u2663","\u2660",NULL};

// Ranks used
enum RANK
{
	SIX,
	SEVEN,
	EIGHT,
	NINE,
	TEN,
	JACK,
	QUEEN,
	KING,
	ACE,
};

const char *listRank[] = {"6","7","8","9","10","J","Q","K","A",NULL};

// Card faces
enum FACE
{
	DOWN,
	UP
};

const char *listFace[] = {"down","up",NULL};

#define HAND_SIZE 6

/* GAME FUNCTIONS AND RULES */

// Create playing deck using rank and suit lists
// NOTE: Automatically shuffles and finds a trump suit
// by uncovering the card at the bottom.
stackT *deckInit(int &trumpSuit);

// Hand cards to players in party Order until HAND_SIZE is reached for each player
// Reduce stack size on the way
void handCards(partyT *partyP, stackT *stackP, int sizeHand);

// Determine if a card has trump suit
int isTrump(cardT *cardP, int trumpSuit);

// Determine if card `a` beats card `b` using trump suit
int cardBeats(cardT *aP, cardT *bP, int trumpSuit);

// Determine if a chosen card can be added to the table for the defender to beat
int cardFits(cardT *cardP, tableT *tableP);

// Determine if current round is over
// check if one of the conditions is true:
// - table full && all cards beaten
// - table not full, but attacking player(s) done and all cards beaten
// - table not full, but defending player has taken cards
int roundOver(partyT *partyP, tableT *tableP);

// Determine if game has ended
// Check if deck is empty && 1 or no player has cards on his hands
int gameOver(partyT *partyP, stackT *deckP);


/* TODO: Add more functions for rule-checking */


#endif // STANDARD_H
