/* Players' party interface */

#ifndef PARTY_H
#define PARTY_H

/* PARTY DATA TYPE
 *
 * Holds player array and its length as well as the current active player.
 */

typedef struct partyT
{
	playerT *players;
	int numPlayers;
	int currentPlayer;
};

// Allocate memory for party
// Takes a list of player Names,
// terminated with some special player entry (e.g. empty name)
int partyInit(partyT *partyP, char **listPlayers);

// Free memory for party
int partyDestroy(partyT *partyP);

// Shuffle player seats
int partyShuffle(partyT *partyP);

// Switch player roles such that the next player attacks
// Wraps around at array end and
// checks if next player is still in the game and skips accordingly
int partyNextPlayer(partyT *partyP);


#endif // PARTY_H