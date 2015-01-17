/* Players' party implementation */

#include <stdlib.h>

#include "party.h"

// Allocate memory for an empty party
partyT *partyInit(void)
{
	partyT *partyP = malloc(sizeof(partyT));
	partyP->first = NULL;
	partyP->attacker = NULL;
	partyP->defender = NULL;
	partyP->numPlayers = 0;
	return partyP;
}

// Free memory for party
void partyDestroy(partyT **partyP)
{
	// destroy all remaining players
	playerT *current = (*partyP)->first;
	playerT *next;
	// walk through list and destroy each player
	while (current != NULL)
	{
		// since the list is circular, we don't compare to a terminator
		// but whether the last element points to the first
		if (current->next != (*partyP)->first)
		{
			next = current->next;
		}
		else
		{
			// at the end, set break condition
			next = NULL;
		}
		// if implemented correctly, should set currentPlayer pointer to NULL
		playerDestroy(&current);
		current = next;
	}

	// reset pointers
	(*partyP)->first = NULL;
	(*partyP)->attacker = NULL;
	(*partyP)->defender = NULL;

	free(*partyP);
	*partyP = NULL;
}

// Add player to linked list and update numPlayers
int addPlayer(partyT *partyP, playerT *playerP)
{
	// don't add empty players
	// last player already points to first
	if (playerP != NULL)
	{
		// if player list non-empty
		if (partyP->first != NULL)
		{
			playerT *current = partyP->first->next;
			// add player at the end of the list
			// we should never hit a NULL player here, since the list is circular
			while(current->next != partyP->first)
			{
				current = current->next;
			}
			// reroute pointers appropriately
			current->next = playerP;
			playerP->next = partyP->first;
		}
		else
		{
			// otherwise make it the first player
			partyP->first = playerP;
			playerP->next = partyP->first;
		}
		// increase number of players
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

// Switch player roles such that the last defender attacks
// Check if next player is still in the game and skip accordingly
void nextPlayer(partyT *partyP)
{
	partyP->attacker = partyP->defender;
	playerT *current = partyP->defender;
	// look for next defender until either an active player is found
	// or we hit the defender again
	while(1)
	{
		current = current->next;
		if (playerInGame(current) || current == partyP->defender)
		{
			partyP->defender = current;
			return;
		}
	}
}


void nextPlayerSkip(partyT *partyP)
{
	// skip defender
	playerT *current = partyP->defender;
	// find next attacker
	while(1)
	{
		current = current->next;
		// look for next attacker until either we found the next best active player
		// or it's the defender again
		if (playerInGame(current) || current == partyP->defender)
		{
			partyP->attacker = current;
			break;
		}
	}
	// find next defender
	while(1)
	{
		current = current->next;
		if (playerInGame(current) || current == partyP->defender)
		{
			partyP->defender = current;
			return;
		}
	}
}

// return who is attacking and defending
playerT *partyAttacker(partyT *partyP)
{
	return partyP->attacker;
}

playerT *partyDefender(partyT *partyP)
{
	return partyP->defender;
}


/* not important right now
// Shuffle player seats
// Use something like this method:
// http://stackoverflow.com/a/11309261
int partyShuffle(partyT *partyP);
*/
