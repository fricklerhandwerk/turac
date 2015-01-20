#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>


#include "../inc/rules.h"
#include "../inc/bot.h"
#include "../inc/constants.h"
#include "../inc/cmd_view.h"
#include "../inc/input.h"

// game speed
#define SPEED (10*1000) // ms * 1000 = ns

int main()
{
	// Game variables
	int trump = -1;
	tableT *table;
	stackT *deck, *waste;
	partyT *party;
	playerT *player1, *player2, *durakP;

	// Initialize game objects
	table = tableInit(HAND_SIZE);
	deck = deckInit(listRank,listSuit,&trump);
	waste = stackInit(stackSize(deck));

	party = partyInit();
	player1 = playerNew("Player1",stackSize(deck));
	player2 = playerNew("Player2",stackSize(deck));

	addPlayer(party,player1);
	addPlayer(party,player2);


	// start game by handing cards
	handCardsGame(party,deck,HAND_SIZE);

	// set first round attacker/defender
	setFirstRound(party,trump);
	while (party->attacker == NULL)
	{
		printf("No trumps handed, game reset...\n");
		usleep(SPEED);
		gameReset(party,deck,waste,table,HAND_SIZE,listRank,listSuit,&trump);
	}

	// update view
	viewGame(party,table,deck,waste,listRank,listSuit);

	// GAME LOOP
	while(!gameOver(party,deck))
	{
		// ROUND LOOP
		while(!roundOver(party,table))
		{
			int position = 0;
			// wait for attacker to play
			usleep(SPEED);
			//botPlay(party->attacker,party,table,trump);
			input_player1(party->attacker, table, position, trump);
			viewGame(party,table,deck,waste,listRank,listSuit);

			// wait for defender to play
			usleep(SPEED);
			botPlay(party->defender,party,table,trump);
			viewGame(party,table,deck,waste,listRank,listSuit);
		}

		// AFTER EACH ROUND

		printf("Round over.\n");
		// clean table
		if (playerInRound(party->defender))
		{
			printf("%s defended successfully.\n",party->defender->name);
			// if defender won, table to waste
			tableClean(table,waste);
		}
		else
		{
			printf("%s takes cards.\n",party->defender->name);
			// otherwise defender takes cards
			tableClean(table,party->defender->hand);

		}

		usleep(SPEED);
		viewGame(party,table,deck,waste,listRank,listSuit);

		// hand cards if any left
		if (stackSize(deck) > 0)
		{
			handCardsRound(party,deck,HAND_SIZE);
			usleep(SPEED);
			viewGame(party,table,deck,waste,listRank,listSuit);
		}

		// switch to next player
		if (playerInRound(party->defender))
		{
			// if defender won, defender is next
			nextPlayer(party);
		}
		else
		{
			// if defender has taken cards, next after defender is next
			nextPlayerSkip(party);
		}

		usleep(SPEED);
		viewGame(party,table,deck,waste,listRank,listSuit);
	}
	viewGame(party,table,deck,waste,listRank,listSuit);
	printf("Game Over!\n");
	durakP = durak(party);
	if (durakP != NULL)
	{
		printf("%s is the fool!\n",durakP->name);
	}
	else
	{
		printf("It's a tie!\n");
	}
	return(0);
}
