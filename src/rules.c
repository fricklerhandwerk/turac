/* GAME FUNCTIONS AND RULES */

#include <stdlib.h>

#include "../inc/rules.h"
#define UP 1
#define DOWN 0

stackT *deckInit(const char **listRank, const char **listSuit, int *trumpSuit)
{
	// space for card pointer
	// we need to free each created card after pushing
	// because the stack contains the actual data, not pointers
	cardT *cardP;
	int ranks = 0;
	int suits = 0;
	// find out number of ranks
	for (; *(listRank+ranks); ranks++);
	// find out number of suits
	for (; *(listSuit+suits); suits++);

	// initialize stack
	stackT *deckP = stackInit(ranks*suits);

	// create a card of each suit/rank combination and add it to the deck
	for (int s = 0; s < suits; s++)
	{
		for (int r = 0; r < ranks; r++)
		{
			// create new card face down
			// with current rank and suit
			cardP = cardNew(r,s,0);
			// add to deck
			stackPush(deckP,cardP);
			// free card memory again
			cardDestroy(&cardP);
		}
	}
	
	stackShuffle(deckP);

	// uncover trump card (bottom card of the deck)
	// write its suit into given variable
	*trumpSuit = cardSetFace(&deckP->cards[0],UP)->suit;

	return(deckP);
}

void handCardsPlayer(playerT *playerP, stackT *deckP, int handSize)
{
	// put cards into players hand until
	// a) hand size reached
	// b) stack is empty
	// c) player's hand full -- very unlikely though
	for (int i = handSize; i > 0 && stackSize(playerP->hand) < handSize && !stackEmpty(deckP); i--)
	{
		cardT *pop = stackPop(deckP);
		if (takeCard(playerP,cardSetFace(pop,UP)) == EXIT_FAILURE)
		{
			// put refused card back
			stackPush(deckP,cardSetFace(pop,DOWN));
			break;
		}
	}
}

void handCardsGame(partyT *partyP, stackT *deckP, int handSize)
{
	// give each player cards
	playerT *current = partyP->first;
	// we stop the loop when we hit the first player again
	do
	{
		handCardsPlayer(current,deckP,handSize);
		current = current->next;
	}
	while (current != partyP->first);
}

void handCardsRound(partyT *partyP, stackT *deckP, int handSize)
{
	// here come the traditional rules...
	// first, the original attacking player takes cards
	handCardsPlayer(partyP->attacker,deckP,handSize);

	// then we skip the defender and all others take cards
	playerT *current = partyP->defender->next;
	// we stop the loop when we hit the original attacker again
	while (current != partyP->attacker)
	{
		handCardsPlayer(current,deckP,handSize);
		current = current->next;
	}
	// then, at last, the defender takes cards
	handCardsPlayer(partyP->defender,deckP,handSize);
}

void setFirstRound(partyT *partyP, int trumpSuit)
{
	int lowest = 99; // gnah... magic number
	playerT *first = NULL;

	playerT *current = partyP->first;
	do
	{
		// set all players to playing
		playerStartGame(current);
		playerStartRound(current);

		// find the player with the lowest trump on hand
		int range = stackSize(current->hand);
		for (int i = 0; i < range; i++)
		{
			if (current->hand->cards[i].suit == trumpSuit && current->hand->cards[i].rank < lowest)
			{
				lowest = current->hand->cards[i].rank;
				first = current;
			}
		}
		current = current->next;
	}
	while (current != partyP->first);

	// set this found player as attacker
	partyP->attacker = first;

	// only if we found anyone with a trump, the following player defends
	if (partyP->attacker != NULL)
	{
		partyP->defender = partyP->attacker->next;
	}

	// if we haven't found any player with a trump,
	// attacker is still set to NULL.
	// the consequences must be evaluated by the calling function
}

// Determine if a card has trump suit
int isTrump(cardT *cardP, int trumpSuit)
{
	return (cardP->suit == trumpSuit);
}

// Determine if card `a` beats card `b` using trump suit
int cardBeats(cardT *aP, cardT *bP, int trumpSuit)
{
	// if both have the same suit
	if (aP->suit == bP->suit)
	{
		// then `a` wins with higher rank
		return (cardCompareRank((const void *) aP,(const void *) bP) > 0);
	}
	else
	{
		// otherwise `a` only wins if it's trump
		return isTrump(aP,trumpSuit);
	}
}

// Determine if a chosen card can be added to the table for the defender to beat
int cardFits(cardT *cardP, tableT *tableP)
{
	// check if there is any card on the table that has the same rank

	// get number of attacking/defending cards
	int att = stackSize(tableP->att);
	int def = stackSize(tableP->def);

	// if it's the first card, of course it fits
	if (att == 0)
	{
		return TRUE;
	}

	// otherwise walk through both attacking and defending arrays
	for (int i = 0; i < def; i++)
	{
		if (cardP->rank == tableP->def->cards[i].rank)
		{
			return TRUE;
		}
	}
	for (int i = 0; i < att; i++)
	{
		if (cardP->rank == tableP->att->cards[i].rank)
		{
			return TRUE;
		}
	}

	return FALSE;
}

// Determine if all attackers have stopped
int attackStopped(partyT *partyP)
{
	// start from next after defender
	playerT *current = partyP->defender->next;
	// walk through all players until we hit the defender again
	while(current != partyP->defender)
	{
		// if any is still attacking, return FALSE
		if (playerInRound(current))
		{
			return FALSE;
		}
		current = current->next;
	}
	return TRUE;
}

// Determine if current round is over
// check if one of the conditions is true:
// - table full && all cards beaten
// - table not full, but attacking player(s) done and all cards beaten
// - table not full, but defending player has taken cards
int roundOver(partyT *partyP, tableT *tableP)
{
	// has defender taken cards?
	int defTaken = !playerInRound(partyP->defender);
	// all others stopped attacking?
	int attStopped = attackStopped(partyP);

	return
	(
		// defender has taken cards and attacker stopped
		(defTaken && attStopped) ||
		// attacker stopped and table is beaten
		(attStopped && tableBeaten(tableP)) ||
		// table is full and beaten
		(tableFull(tableP) && tableBeaten(tableP))
	);
}

// Determine if game has ended
// Check if deck is empty && 1 or no player has cards on his hands
int gameOver(partyT *partyP, stackT *deckP)
{
	// count players with cards on their hands
	int active = 0;
	playerT *current = partyP->first;
	// walk through all players until we hit the first again
	do
	{
		// sum up players with nonempty hands
		active += !stackEmpty(current->hand);
		current = current->next;
	}
	while(current != partyP->first);

	return (stackEmpty(deckP) && active < 2);
}

playerT *durak(partyT *partyP)
{
	playerT *current = partyP->first;
	do
	{
		if (stackSize(current->hand) != 0)
		{
			return current;
		}
		current = current->next;
	}
	while(current != partyP->first);

	// if it's a tie return NULL
	return NULL;	
}

void gameReset(partyT *partyP, stackT *deckP, stackT *wasteP, tableT *tableP, int handSize, const char **listRank, const char **listSuit, int *trumpSuit)
{
	// put all cards from the table back to deck
	tableClean(tableP,deckP);

	// put all cards from the waste stack back to deck
	stackClean(wasteP,deckP);

	// put all cards from player hands back to deck
	playerT *current = partyP->first;
	// walk through all players until we hit the first again
	do
	{
		// sum up players with nonempty hands
		stackClean(current->hand,deckP);
		current = current->next;
	}
	while(current != partyP->first);

	// recreate deck from scratch
	stackDestroy(&deckP);
	deckP = deckInit(listRank,listSuit,trumpSuit);

	// hand cards again
	handCardsGame(partyP, deckP, handSize);

	// set first attacker
	setFirstRound(partyP,*trumpSuit);
}

/* TODO: Add more functions for rule-checking */