
#include <../inc/input.h>

void playerSortHand(playerT *playerP, int trumpSuit)
{
	// take all trumps from hand
	stackT *trumps = stackInit(stackMaxSize(playerP->hand));
	// this one is a bit tricky...
	// move trough stack until last element
	for (int i = 0; i < stackSize(playerP->hand); ++i)
	{
		// but since playCard() currently swaps the chosen card with top,
		// the new card at this position might also come in question
		while (i < stackSize(playerP->hand) && isTrump(&playerP->hand->cards[i],trumpSuit))
		{
			// put the trump card onto trumps stack
			stackPush(trumps,playCard(playerP,i));
		}
	}


	// sort remaining cards by rank
	stackSortRank(playerP->hand);

	// now, if we push the trumps back after sorting, they will be in wrong order
	// so instead, for now, we just exchange first and last, pop the top
	// sort it again and repeat until no cards are left in trumps
	// terribly inefficient, a simple stackReverse function would be nice...
	while (!stackEmpty(trumps))
	{
		stackSortRank(trumps);
		stackSwap(trumps,0);
		takeCard(playerP,stackPop(trumps));
	}
	// we don't need the trumps stack any more
	stackDestroy(&trumps);
}

void input_player1(partyT *partyP, playerT *playerP,tableT *tableP, int *pos, int *quit, int trumpSuit)//maybe but active players in here?
{
	int handsize = stackSize(playerP->hand)-1;

	/* assuming we get a valid cursor position to begin with
	while (*pos > handsize)
	{
		(*pos)--;
	}
	*/

	char input_c;

	//setting input to raw input
	system ("/bin/stty raw");

	input_c = getchar();

	if (input_c == QUIT)
	{

		(*quit) = TRUE;
	}
	else if(input_c == P1_LT)
	{
		if (*pos > 0)
		{
			(*pos)--;
		}
		else
		{
			(*pos) = handsize;
		}
	}
	else if (input_c == P1_RT)
	{

		if (*pos < handsize)
		{
			(*pos)++;
		}
		else
		{
			(*pos) = 0;
		}
	}
	else if (input_c == P1_AC)
	{
		if (partyP->defender == playerP)
		{
			// beat the first card possible
			// otherwise do nothing
			for (int i = 0; i < stackSize(tableP->att); ++i)
			{
				if (cardBeats(&playerP->hand->cards[*pos],tableP,i,trumpSuit))
				{
					tablePutDef(tableP,playCard(playerP,*pos),i);
					break;
				}
			}
		}
		else
		{
			if (cardFits(&playerP->hand->cards[*pos],tableP))
			{
				tablePutAtt(tableP,playCard(playerP,*pos));
				// stop attack if no cards left afterwards
				if (stackSize(playerP->hand) == 0)
				{
					playerEndRound(playerP);
				}
			}	
		}

	}
	else if (input_c == P1_EN)
	{
		if (!(playerP == partyP->attacker && stackSize(tableP->att) == 0) && !(playerP == partyP->defender && tableBeaten(tableP)))
		{
			playerEndRound(playerP);
		}

	}
	else if (input_c == P1_ST){
		playerSortHand(playerP, trumpSuit);
	}

	// reset cursor to valid position
	handsize = stackSize(playerP->hand)-1;
	while (*pos > handsize)
	{
		(*pos)--;
	}

	//setting input to cooked input
	system ("/bin/stty cooked");
}

void input_twoplayers(partyT *partyP, playerT *playerPone, playerT *playerPtwo, tableT *tableP, int *pos_one, int *pos_two, int *quit, int trumpSuit)//maybe but active players in here?
{
	int handsize1 = stackSize(playerPone->hand)-1;
	int handsize2 = stackSize(playerPtwo->hand)-1;

	/* assuming we get a valid position to start with
	// reset cursors to valid positions
	while (*pos_one > handsize1)
	{
		(*pos_one)--;
	}	
	while (*pos_two > handsize2)
	{
		(*pos_two)--;
	}
	*/

	//setting input to raw input
	system ("/bin/stty raw");

	char input_c;
	input_c = getchar();

	
	if (input_c == QUIT)
	{

		(*quit) = TRUE;
	}

	// Player 1 commands
	else if(input_c == P1_LT)
	{
		if (*pos_one > 0)
		{
			(*pos_one)--;
		}
		else
		{
			(*pos_one) = handsize1;
		}
	}
	else if (input_c == P1_RT)
	{

		if (*pos_one < handsize1)
		{
			(*pos_one)++;
			//draw
		}
		else
		{
			(*pos_one) = 0;
		}
	}
	else if (input_c == P1_AC)
	{
		if (partyP->defender == playerPone)
		{
			// beat the first card possible
			// otherwise do nothing
			for (int i = 0; i < stackSize(tableP->att); ++i)
			{
				if (cardBeats(&playerPone->hand->cards[*pos_one],tableP,i,trumpSuit))
				{
					tablePutDef(tableP,playCard(playerPone,*pos_one),i);
					break;
				}
			}
		}
		else
		{
			if (cardFits(&playerPone->hand->cards[*pos_one],tableP))
			{
				tablePutAtt(tableP,playCard(playerPone,*pos_one));

				// stop attack any if no cards left afterwards
				if (stackSize(playerPone->hand) == 0)
				{
					playerEndRound(playerPone);
				}
			}	
		}

	}
	else if (input_c == P1_EN)
	{
		if (!(playerPone == partyP->attacker && stackSize(tableP->att) == 0) && !(playerPone == partyP->defender && tableBeaten(tableP)))
		{
			playerEndRound(playerPone);
		}
	}
	else if (input_c == P1_ST)
	{
		playerSortHand(playerPone, trumpSuit);
	}




	// Player 2 commands
	else if (input_c == P2_LT)
	{
		if (*pos_two > 0)
		{
			(*pos_two)--;
		}
		else
		{
			(*pos_two) = handsize2;
		}
	}
	else if (input_c == P2_RT)
	{

		if (*pos_two < handsize2)
		{
			(*pos_two)++;
		}
		else
		{
			(*pos_two) = 0;
		}
	}
	else if (input_c == P2_AC)
	{
		if (partyP->defender == playerPtwo)
		{
			// look at each card on attack stack
			for (int i = 0; i < stackSize(tableP->att); ++i)
			{
				if (cardBeats(&playerPtwo->hand->cards[*pos_two],tableP,i,trumpSuit))
				{
					tablePutDef(tableP,playCard(playerPtwo,*pos_two),i);
					break;
				}
			}
		}
		else
		{
			if (cardFits(&playerPtwo->hand->cards[*pos_two],tableP))
			{
				tablePutAtt(tableP,playCard(playerPtwo,*pos_two));
				
				// stop attack if no cards left afterwards
				if (stackSize(playerPtwo->hand) == 0)
				{
					playerEndRound(playerPtwo);
				}
			}	
		}

	}
	else if (input_c == P2_EN)
	{
		if (!(playerPtwo == partyP->attacker && stackSize(tableP->att) == 0) && !(playerPtwo == partyP->defender && tableBeaten(tableP)))
		{
			playerEndRound(playerPtwo);
		}
	}
	else if (input_c == P2_ST)
	{
		playerSortHand(playerPtwo, trumpSuit);
	}


	// reset cursors to valid positions
	handsize1 = stackSize(playerPone->hand)-1;
	handsize2 = stackSize(playerPtwo->hand)-1;
	while (*pos_one > handsize1)
	{
		(*pos_one)--;
	}	
	while (*pos_two > handsize2)
	{
		(*pos_two)--;
	}	

	//setting input to cooked input
	system ("/bin/stty cooked");
}
