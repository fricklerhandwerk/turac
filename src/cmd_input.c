
#include "../inc/cmd_input.h"

void input_player1(partyT *partyP, playerT *playerP,tableT *tableP, int *pos, int *quit, int trumpSuit)
{
	int handsize = stackSize(playerP->hand)-1;

	//setting input to raw input
	system ("stty raw");

	char input_c;
	input_c = getchar();

	switch(input_c)
	{
		case QUIT:
			(*quit) = TRUE;
			break;
		case P1_LT:
			if (*pos > 0)
			{
				(*pos)--;
			}
			else
			{
				(*pos) = handsize;
			}
			break;
		case P1_RT:
			if (*pos < handsize)
			{
				(*pos)++;
			}
			else
			{
				(*pos) = 0;
			}
			break;
		case P1_AC:
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
				if (stackSize(partyP->defender->hand) > (stackSize(tableP->att)-stackSize(tableP->def)) && cardFits(&playerP->hand->cards[*pos],tableP))
				{
					tablePutAtt(tableP,playCard(playerP,*pos));
					// stop attack if no cards left afterwards
					if (stackEmpty(playerP->hand))
					{
						playerEndRound(playerP);
					}
				}	
			}
			break;
		case P1_EN:
			if (!(playerP == partyP->attacker && stackEmpty(tableP->att)) && !(playerP == partyP->defender && tableBeaten(tableP)))
			{
				playerEndRound(playerP);
			}
			break;
		case P1_ST:
			playerSortHand(playerP, trumpSuit);
			break;
		default:
			break;
	}

	// reset cursor to valid position
	handsize = stackSize(playerP->hand)-1;
	while (*pos > handsize)
	{
		(*pos)--;
	}

	//setting input to cooked input
	system ("stty cooked");
}

void input_twoplayers(partyT *partyP, playerT *playerPone, playerT *playerPtwo, tableT *tableP, int *pos_one, int *pos_two, int *quit, int trumpSuit)
{
	int handsize1 = stackSize(playerPone->hand)-1;
	int handsize2 = stackSize(playerPtwo->hand)-1;

	//setting input to raw input
	system ("stty raw");

	char input_c;
	input_c = getchar();

	
	switch(input_c)
	{
		case QUIT:
			(*quit) = TRUE;
			break;
		// Player 1 commands
		case P1_LT:
			if (*pos_one > 0)
			{
				(*pos_one)--;
			}
			else
			{
				(*pos_one) = handsize1;
			}
			break;
		case P1_RT:
			if (*pos_one < handsize1)
			{
				(*pos_one)++;
			}
			else
			{
				(*pos_one) = 0;
			}
			break;
		case P1_AC:
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
				if (stackSize(partyP->defender->hand) > (stackSize(tableP->att)-stackSize(tableP->def)) && cardFits(&playerPone->hand->cards[*pos_one],tableP))
				{
					tablePutAtt(tableP,playCard(playerPone,*pos_one));

					// stop attack any if no cards left afterwards
					if (stackSize(playerPone->hand) == 0)
					{
						playerEndRound(playerPone);
					}
				}	
			}
			break;
		case P1_EN:
			if (!(playerPone == partyP->attacker && stackSize(tableP->att) == 0) && !(playerPone == partyP->defender && tableBeaten(tableP)))
			{
				playerEndRound(playerPone);
			}
			break;
		case P1_ST:
			playerSortHand(playerPone, trumpSuit);
			break;
		// Player 2 commands
		case P2_LT:
			if (*pos_two > 0)
			{
				(*pos_two)--;
			}
			else
			{
				(*pos_two) = handsize2;
			}
			break;
		case P2_RT:
			if (*pos_two < handsize2)
			{
				(*pos_two)++;
			}
			else
			{
				(*pos_two) = 0;
			}
			break;
		case P2_AC:
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
				if (stackSize(partyP->defender->hand) > (stackSize(tableP->att)-stackSize(tableP->def)) && cardFits(&playerPtwo->hand->cards[*pos_two],tableP))
				{
					tablePutAtt(tableP,playCard(playerPtwo,*pos_two));
					
					// stop attack if no cards left afterwards
					if (stackSize(playerPtwo->hand) == 0)
					{
						playerEndRound(playerPtwo);
					}
				}	
			}
			break;
		case P2_EN:
			if (!(playerPtwo == partyP->attacker && stackEmpty(tableP->att)) && !(playerPtwo == partyP->defender && tableBeaten(tableP)))
			{
				playerEndRound(playerPtwo);
			}
			break;
		case P2_ST:
			playerSortHand(playerPtwo, trumpSuit);
			break;
		default:
			break;
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
	system ("stty cooked");
}
