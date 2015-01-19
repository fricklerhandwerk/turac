/* Durak bot implementation */

// WARNING: because of short time, no error checking is done here
// I really have to trust the underlying library for now

#include <../inc/bot.h>

void botSortHand(playerT *botP, int trumpSuit)
{
	// take all trumps from hand
	stackT *trumps = stackInit(stackMaxSize(botP->hand));
	// this one is a bit tricky...
	// move trough stack until last element
	for (int i = 0; i < stackSize(botP->hand); ++i)
	{
		// but since playCard() currently swaps the chosen card with top,
		// the new card at this position might also come in question
		while (i < stackSize(botP->hand) && isTrump(&botP->hand->cards[i],trumpSuit))
		{
			// put the trump card onto trumps stack
			stackPush(trumps,playCard(botP,i));
		}
	}


	// sort remaining cards by rank
	stackSortRank(botP->hand);

	// now, if we push the trumps back after sorting, they will be in wrong order
	// so instead, for now, we just exchange first and last, pop the top
	// sort it again and repeat until no cards are left in trumps
	// terribly inefficient, a simple stackReverse function would be nice...
	while (!stackEmpty(trumps))
	{
		stackSortRank(trumps);
		stackSwap(trumps,0);
		takeCard(botP,stackPop(trumps));
	}
	// we don't need the trumps stack any more
	stackDestroy(&trumps);
}

void botAttack(playerT *botP, tableT *tableP, int trumpSuit)
{
	// sort cards by value
	botSortHand(botP,trumpSuit);

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
	botSortHand(botP,trumpSuit);

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