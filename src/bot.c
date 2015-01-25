/* Durak bot implementation */

// WARNING: because of short time, no error checking is done here
// I really have to trust the underlying library for now

#include <../inc/bot.h>

void botAttack(playerT *botP, partyT *partyP, tableT *tableP, int trumpSuit)
{
	// sort cards by value
	playerSortHand(botP,trumpSuit);

	// look for the first card that would fit on the table
	for (int i = 0; i < stackSize(botP->hand); ++i)
	{
		// when found, put it on the table and exit
		if (stackSize(partyP->defender->hand) > (stackSize(tableP->att)-stackSize(tableP->def)) && cardFits(&botP->hand->cards[i],tableP))
		{
			tablePutAtt(tableP,playCard(botP,i));
			// don't attack any more if no cards left
			if (stackSize(botP->hand) == 0)
			{
				playerEndRound(botP);
			}
			return;
		}
	}
	// if no card found, stop attacking
	playerEndRound(botP);
	return;
}

void botDefend(playerT *botP, tableT *tableP, int trumpSuit)
{
	// sort cards by value
	playerSortHand(botP,trumpSuit);

	// for each card to beat, look for the lowest possible solution
	for (int k = 0; k < stackSize(botP->hand); ++k)
	{
		// beat with the first card possible
		for (int i = 0; i < stackSize(tableP->att); ++i)
		{
			if (cardBeats(&botP->hand->cards[k],tableP,i,trumpSuit))
			{
				tablePutDef(tableP,playCard(botP,k),i);
				return;
			}
		}
	}

	// if no card could beat any attacking cards, mark that bot will take cards
	playerEndRound(botP);
}

// decide what to do and do it
void botPlay(playerT *botP, partyT *partyP, tableT *tableP, int trumpSuit)
{
	if (botP == partyP->defender)
	{
		// check if table is already beaten or already taken cards
		if (playerInRound(botP) && !tableBeaten(tableP))
		{
			botDefend(botP,tableP,trumpSuit);
		}
	}
	else
	{
		// only attack if not done
		if (playerInRound(botP))
		{
			botAttack(botP,partyP,tableP,trumpSuit);
		}
	}
}