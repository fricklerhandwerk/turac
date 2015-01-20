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

void input_player1(playerT *playerP, int* position)//maybe but active players in here?
{
	int handsize = stackSize(playerP->hand);
	char input_c;

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
		//player 1 play selected card
	} else if (input_c == 'd'){
		//player 1 stop
	} else {
		printf("\n--------------------\nBitte gebe etwas anderes ein!\n------------------\n");
	}

	//setting input to cooked input
	system ("/bin/stty cooked");
}

void input_twoplayers(playerT *PlayerPone, playerT *playerPtwo, int* position_one, int* position_two)//maybe but active players in here?
{
	int handsize1 = stackSize(playerPone->hand);
	int handsize2 = stackSize(playerPtwo->hand);
	char input_c;

	//setting input to raw input
	system ("/bin/stty raw");

	input_c = getchar();

	if(input_c == 'w'){
		//player 1 selcet up
	} else if (input_c == 's'){
		//player 1 select down
	} else if (input_c == 'e'){
		//player 1 play selected card
	} else if (input_c == 'd'){
		//player 1 stop
	} else if (input_c == 'o'){
		//player 2 select up
	} else if (input_c == 'l'){
		//player 2 select down
	} else if (input_c == 'i'){
		//player 2 play selected card
	} else if (input_c == 'k'){
		//player 2 stop
	} else {
		printf("\n--------------------\nBitte gebe etwas anderes ein!\n------------------\n");
	}

	//setting input to cooked input
	system ("/bin/stty cooked");
}
