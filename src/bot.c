/* Durak bot implementation */

// WARNING: because of short time, no error checking is done here
// I really have to trust the underlying library for now

#include <../inc/bot.h>

void botAttack(playerT *botP, tableT *tableP, int trumpSuit)
{
	// sort cards by value
	playerSortHand(botP,trumpSuit);

	// look for the first card that would fit on the table
	for (int i = 0; i < stackSize(botP->hand); ++i)
	{
		// when found, put it on the table and exit
		if (cardFits(&botP->hand->cards[i],tableP))
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

	/* WARNING: REALLY IMPORTANT HACK TO CHECK WHETHER A CARD BEATS ANOTHER ONE */

	// for each card to beat, look for the lowest possible solution
	for (int k = 0; k < stackSize(botP->hand); ++k)
	{
		// look at each card on attack stack
		for (int i = 0; i < stackSize(tableP->att); ++i)
		{
			// check if it's been beaten already by some other card on defend stack
			int beaten = FALSE;
			for (int j = 0; j < stackSize(tableP->def); ++j)
			{
				if (tableP->beats[j] == i)
				{
					beaten = TRUE;
					break;
				}
			}
			// if so, work on next attacking card
			if (beaten) {continue;}

			// otherwise try to beat it with currend card
			if (cardBeats(&botP->hand->cards[k],&tableP->att->cards[i],trumpSuit))
			{
				tablePutDef(tableP,playCard(botP,k),i);
				return;
			}
			else
			{
				continue;
			}
		}
	}

	// if no card could beat any attacking cards, mark that bot will take cards
	//printf("No card found that would beat anything...\n");
	playerEndRound(botP);
	return;
}

// decide what to do and do it
void botPlay(playerT *botP, partyT *partyP, tableT *tableP, int trumpSuit)
{
	if (botP == partyP->defender)
	{
		// check if table is already beaten or already taken cards
		if (tableBeaten(tableP) || !playerInRound(botP))
		{
			//printf("Attacker stopped, all cards beaten, init next round.\n");
			return;
		}
		//printf("%s defending.\n", botP->name);
		botDefend(botP,tableP,trumpSuit);
	}
	else
	{
		// check if last round we already set to done
		if (!playerInRound(botP))
		{
			return;
		}
		//printf("%s attacking.\n", botP->name);
		botAttack(botP,tableP,trumpSuit);
	}
}