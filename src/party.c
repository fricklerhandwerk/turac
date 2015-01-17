/* Players' party implementation */

#include "player.h"

// Allocate memory for an empty party
partyT *partyInit(void)
{
	partyT *partyP = malloc(sizeof(partyT));
	partyP->first = NULL;
	partyP->current = NULL;
	partyP->numPlayers = 0;
	return partyP;
}

// Free memory for party
void partyDestroy(partyT **partyP)
{
	// destroy all remaining players
	playerT *current = (*partyP)->first;
	playerT *next = current->next;
	while (current != NULL)
	{
		// if implemented correctly, should set currentPlayer pointer to NULL
		playerDestroy(&current);
		current = next;
		if (next != NULL)
		{
			next = next->next;
		}
	}
	free(*partyP);
	*partyP = NULL;
}

// Add player to linked list and update numPlayers
int partyAddPlayer(partyT *partyP, playerT *playerP)
{
	// don't add empty players
	// last player already points first
	if (playerP != NULL)
	{
		// if player list non-empty
		if (partyP->current != NULL)
		{
			// just insert new one after current player
			// O(1) instead of O(n) for appending to single-linked list
			// NOTE: semantically, this may not always be a good idea
			playerP->next = partyP->current->next;
			partyP->current->next = playerP;
		}
		else
		{
			// otherwise make it the first (and current) player
			playerP->next = playerP;
			partyP->first = playerP;
			partyP->current = playerP;
		}
		partyP->numPlayers++;
		return(EXIT_SUCCESS);
	}
	return(EXIT_FAILURE);
}

/*
// Remove player from linked list
// Update currentPlayer pointer if necessary
int partyRemovePlayer(partyT *partyP, playerT *playerP)
{

}
*/

// Switch player roles such that the next player attacks
// Check if next player is still in the game and skip accordingly
void partyNextPlayer(partyT *partyP)
{
	partyP->current = partyP->current->next;
}

/* not important right now
// Shuffle player seats
// Use something like this method:
// http://stackoverflow.com/a/11309261
int partyShuffle(partyT *partyP);
*/
