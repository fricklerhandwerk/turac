#ifndef PLAYER_H
#define PLAYER_H

/* PLAYER DATA TYPE
 *
 * Holds all properties of a player as well as a pointer to the next player.
 *
 * EXAMPLE
 * (attacking player "Foo", who didn't yet stop)
 * playerT playerFoo = {"Foo",&hand,TRUE,TRUE};
 *
 * NOTE
 * `roundF` denotes if a player is still active in the current round.
 * It has two meanings depending on the player's current role:
 * If a player is attacking or spectating,
 + `roundF == FALSE` means, he won't add any cards.
 * If a player is defending, `roundF == FALSE` means,
 + he gives up and takes all cards from the table.
 * `gameF` denotes if a player is still in the game.
 */

#include "stack.h"

 #define TRUE 1
 #define FALSE 0

struct playerT
{
	char *name;
	stackT *hand;
	int roundF;
	int gameF;
	struct playerT *next;
};

typedef struct playerT playerT;

/* PLAYER FUNCTIONS */

// Allocate memory for player with given name and empty hand of given size
playerT *playerNew(char *name, int sizeHand);

// Free member and player memory
void playerDestroy(playerT **playerP);

// Set player state
void playerStartRound(playerT *playerP);
void playerEndRound(playerT *playerP);
void playerStartGame(playerT *playerP);
void playerEndGame(playerT *playerP);

// Retrieve player State
int playerInRound(playerT *playerP);
int playerInGame(playerT *playerP);
int playerHandSize(playerT *playerP);

// Play a given cards from a players hand
// Just return a card
cardT *playCard(playerT *playerP, int numCard);

// Put given card in player's hand
int takeCard(playerT *playerP, cardT *cardP);

// Sort player hand such that trumps are separated
// and all cards ordered by increasing rank
void playerSortHand(playerT *playerP, int trumpSuit);

#endif // PLAYER_H