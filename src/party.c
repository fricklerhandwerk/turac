/* Players' party implementation */

#include "player.h"

// Allocate memory for an empty party
partyT *partyInit(void)
{
	partyT *partyP = malloc(sizeof(partyT));
	partyP->currentPlayer = NULL;
	partyP->numPlayers = 0;
	return partyP;
}

// Free memory for party
void partyDestroy(partyT **partyP)
{
	// destroy all remaining players
	playerT *nextPlayer;
	while ((*partyP)->currentPlayer != NULL)
	{
		nextPlayer = (*partyP)->currentPlayer->next;
		// if implemented correctly, should set currentPlayer pointer to NULL
		playerDestroy(&(*partyP)->currentPlayer); // may need be double pointer to currentPlayer
		(*partyP)->currentPlayer = nextPlayer;
	}
	free(*partyP);
	*partyP = NULL;
}

// Add player to linked list and update numPlayers
int partyAddPlayer(partyT *partyP, playerT *playerP)
{
	// don't add empty players
	// last player already points to NULL
	if (playerP != NULL)
	{
		if (partyP->currentPlayer != NULL)
		{
			// just insert new one after current player
			// O(1) instead of O(n) for appending
			playerP->next = partyP->currentPlayer->next;
			partyP->currentPlayer->next = playerP;
			partyP->numPlayers++;
		}
		else
		{
			// otherwise make it the first (and current) player
			partyP->currentPlayer = playerP;
		}
		return(EXIT_SUCCESS);
	}
	return(EXIT_FAILURE);
}

// Remove player from linked list
// Update currentPlayer pointer if necessary
int partyRemovePlayer(partyT *partyP, playerT *playerP)
{
	
}

// Switch player roles such that the next player attacks
// Check if next player is still in the game and skip accordingly
void partyNextPlayer(partyT *partyP);

/* not important right now
// Shuffle player seats
// Use something like this method:
// http://stackoverflow.com/a/11309261
int partyShuffle(partyT *partyP);
*/
