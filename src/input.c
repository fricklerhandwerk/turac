
#include <../inc/input.h>

void PlayerSortHand(playerT *playerP, int trumpSuit)
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
}

void input_player1(playerT *playerP,tableT *tableP, int *pos, int trumpSuit)//maybe but active players in here?
{
	int handsize = stackSize(playerP->hand);
	char input_c;
	int position = (int) pos;

	//setting input to raw input
	system ("/bin/stty raw");

	input_c = getchar();

	if(input_c == 'w'){
		if (position > 0){
			position = position - 1;
			//draw
		}
	} else if (input_c == 's'){
		if (position < handsize){
			position = position + 1;
			//draw
		}
	} else if (input_c == 'e'){
		if (cardFits(&playerP->hand->cards[position],tableP))
		{
			tablePutAtt(tableP,playCard(playerP,position));
			// don't attack any more if no cards left
			if (stackSize(playerP->hand) == 0)
			{
				playerEndRound(playerP);
			}
		}
	} else if (input_c == 'd'){
		playerEndRound(playerP);
	} else if (input_c == 'q'){
		PlayerSortHand(playerP, trumpSuit);
	} else {
		printf("\n--------------------\nBitte gebe etwas anderes ein!\n------------------\n");
	}

	pos = (int *) position;

	//setting input to cooked input
	system ("/bin/stty cooked");
}

void input_twoplayers(playerT *playerPone, playerT *playerPtwo, tableT *tableP, int *pos_one, int *pos_two, int trumpSuit)//maybe but active players in here?
{
	int handsize1 = stackSize(playerPone->hand);
	int handsize2 = stackSize(playerPtwo->hand);
	char input_c;

	int position_one = (int) pos_one;
	int position_two = (int) pos_two;

	//setting input to raw input
	system ("/bin/stty raw");

	input_c = getchar();

	if(input_c == 'w'){
		if (position_one > 0){
			position_one = position_one - 1;
			//draw
		}
	} else if (input_c == 's'){
		if (position_one < handsize1){
			position_one = position_one + 1;
			//draw
		}
	} else if (input_c == 'e'){
		if (cardFits(&playerPone->hand->cards[position_one], tableP))
		{
			tablePutAtt(tableP,playCard(playerPone, position_one));
			// don't attack any more if no cards left
			if (stackSize(playerPone->hand) == 0)
			{
				playerEndRound(playerPone);
			}
		}
	} else if (input_c == 'd'){
		playerEndRound(playerPone);
	} else if (input_c == 'q'){
		PlayerSortHand(playerPone, trumpSuit);
	}
	else if (input_c == 'o'){
		if (position_two > 0){
			position_two = position_two - 1;
			//draw
		}
	} else if (input_c == 'l'){
		if (position_two < handsize2){
			position_two = position_two + 1;
			//draw
		}
	} else if (input_c == 'i'){
		if (cardFits(&playerPtwo->hand->cards[position_two], tableP))
		{
			tablePutAtt(tableP,playCard(playerPtwo, position_two));
			// don't attack any more if no cards left
			if (stackSize(playerPtwo->hand) == 0)
			{
				playerEndRound(playerPtwo);
			}
		}
	} else if (input_c == 'k'){
		playerEndRound(playerPtwo);
	} else if (input_c == 'p'){
		PlayerSortHand(playerPtwo, trumpSuit);
	} else {
		printf("\n--------------------\nBitte gebe etwas anderes ein!\n------------------\n");
	}

	pos_one = (int *) position_one;
	pos_two = (int *) position_two;

	//setting input to cooked input
	system ("/bin/stty cooked");
}
