/* Players' party interface */

#ifndef PARTY_H
#define PARTY_H

#include "player.h"

/* PARTY DATA TYPE
 *
 * Holds a linked list of players and its length.
 * The linked list points to the current player.
 */

typedef struct partyT
{
	playerT *currentPlayer;
	int numPlayers;
};

// Allocate memory for an empty party
partyT *partyInit(void);

// Free memory for party
int partyDestroy(partyT **partyP);

// Add player to linked list and update numPlayers
void partyAddPlayer(partyT *partyP, playerT *playerP);

// Remove player from linked list
// Update currentPlayer pointer if necessary
void partyRemovePlayer(partyT *partyP, playerT *playerP);

// Switch player roles such that the next player attacks
// Check if next player is still in the game and skip accordingly
void partyNextPlayer(partyT *partyP);

/* not important right now
// Shuffle player seats
// Use something like this method:
// http://stackoverflow.com/a/11309261
int partyShuffle(partyT *partyP);
*/
#endif // PARTY_H