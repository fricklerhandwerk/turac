#ifndef PLAYER_H
#define PLAYER_H

/* PLAYER DATA TYPE
 *
 * Holds all properties of a player.
 *
 * EXAMPLE
 * (attacking player "Foo", who didn't yet stop)
 * playerT playerFoo = {"Foo",&hand,FALSE,FALSE};
 *
 * NOTE
 * `stopF` has two meanings depending on the player's current role:
 * If a player is attacking or spectating,
 + `stopF == TRUE` means, he won't add any cards.
 * If a player is defending, `stopF == TRUE` means,
 + he gives up and takes all cards from the table.
 * `doneF` denotes if a player has finished the game.
 */

 #define ATT 1
 #define DEF -1
 #define SPEC 0

 #define TRUE 1
 #define FALSE 0

typedef struct playerT
{
	char *name;
	stackT *hand;
	int stopF;
	int doneF;
};

/* PLAYER FUNCTIONS */

// Allocate memory for player with empty hand
int playerInit(playerT *playerP);

// Deallocate member variables where possible
int playerDestroy(playerT *playerP);

// Set player state
int playerStart(playerT *playerP);
int playerStop(playerT *playerP);
int playerDone(playerT *playerP);

#endif // PLAYER_H