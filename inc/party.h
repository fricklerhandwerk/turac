/* Players' party interface */

#ifndef PARTY_H
#define PARTY_H

#include "player.h"

/* PARTY DATA TYPE
 *
 * Holds a circular linked list of players with its beginning,
 + the current attacking and defending players
 + as well as the total number of players.
 */

typedef struct
{
	playerT *first;
	playerT *attacker;
	playerT *defender;
	int numPlayers;
} partyT;

// Allocate memory for an empty party
partyT *partyInit(void);

// Free memory for party
void partyDestroy(partyT **partyP);

// Add player to linked list and update numPlayers
int addPlayer(partyT *partyP, playerT *playerP);

/* Will not be used in first demo
// Remove player from linked list
// Update currentPlayer pointer if necessary
int partyRemovePlayer(partyT *partyP, playerT *playerP);
*/

// Switch player roles such that the last defender attacks
// Check if next player is still in the game and skip accordingly
void nextPlayer(partyT *partyP);

// Switch to next player, skipping defender
// (because defender took cards)
void nextPlayerSkip(partyT *partyP);


// return who is attacking and defending
playerT *partyDefender(partyT *partyP);
playerT *partyAttacker(partyT *partyP);

/* not important right now
// Shuffle player seats
// Use something like this method:
// http://stackoverflow.com/a/11309261
int partyShuffle(partyT *partyP);
*/
#endif // PARTY_H