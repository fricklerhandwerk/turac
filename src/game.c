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
#define SPEED (100*1000) // ms * 1000 = ns
#define VIEW_SPEED (500*1000)


int main(int argc, char *argv[])
{
	int humans = 0;

	// if no player number given, stop
	if (argc < 2)
	{
		printf("Usage: <i = number of human players> <player name (i)>\n");
		return(EXIT_FAILURE);
	}
	else
	{
		// get number of human players
		sscanf(argv[1],"%d",&humans);

		// check if number of players makes sense
		// WARNING: 2 is hardcoded here since there is no support for more than two players now
		if (humans < 0 || humans > 2)
		{
			printf("Only two human players possible!\n");
			return(EXIT_FAILURE);
		}		
		// check if all human players have names
		else if (argc != humans+2)
		{
			printf("Please give each human player a name!\n");
			return(EXIT_FAILURE);
		}
	}

	// Game variables
	int trump = -1;
	int quit = FALSE;
	tableT *table;
	stackT *deck, *waste;
	partyT *party;
	playerT *bot1, *bot2, *player1, *player2, *durakP;

	// initial cursor positions
	int position1 = 0, position2 = 0;

	// Initialize game objects
	table = tableInit(HAND_SIZE);
	deck = deckInit(listRank,listSuit,&trump);
	waste = stackInit(stackSize(deck));

	party = partyInit();
	bot1 = playerNew("Bot1",stackSize(deck));
	bot2 = playerNew("Bot2",stackSize(deck));
	player1 = playerNew(argv[2],stackSize(deck));
	player2 = playerNew(argv[3],stackSize(deck));


	switch(humans)
	{
		case 0:
			position1 = -1;
			position2 = -1;
			addPlayer(party,bot1);
			addPlayer(party,bot2);
			break;
		case 1:
			position2 = -1;
			addPlayer(party,player1);
			addPlayer(party,bot1);
			break;
		default:
			addPlayer(party,player1);
			addPlayer(party,player2);
			break;
	}


	// start game by handing cards
	handCardsGame(party,deck,HAND_SIZE);

	// set first round attacker/defender
	setFirstRound(party,trump);
	while (party->attacker == NULL)
	{
		printf("No trumps handed, game reset...\n");
		// wait a second for new random seed
		sleep(1);
		gameReset(party,deck,waste,table,HAND_SIZE,listRank,listSuit,&trump);
	}

	// update view
	viewGame(party,table,deck,waste,position1,position2,listRank,listSuit);

	// GAME LOOP
	while(!gameOver(party,deck))
	{
		// ROUND LOOP
		while(!roundOver(party,table))
		{
			// if defender wants to take cards, check if attacker can still add any
			// if not, set attacker done
			if (!playerInRound(party->defender) || tableBeaten(table))
			{
				int done = 1;
				for (int i = 0; i < stackSize(party->attacker->hand); ++i)
				{
					if (cardFits(&party->attacker->hand->cards[i],table))
						{
							done = 0;
							break;
						}
				}
				if (done)
				{
					playerEndRound(party->attacker);
					// wait a second to denote that something happens for a reason
					usleep(VIEW_SPEED);
					viewGame(party,table,deck,waste,position1,position2,listRank,listSuit);
					continue;
				}
			}
			
			// decide on player controls
			if (humans == 2)
			{
		
				// else, let attacker play normally
				input_twoplayers(party, player1, player2, table, &position1, &position2, &quit, trump);
				viewGame(party,table,deck,waste,position1,position2,listRank,listSuit);
			}
			else
			{
				// wait for attacker to play
				if (party->attacker == bot1 || party->attacker == bot2)
				{
					usleep(SPEED);
					botPlay(party->attacker,party,table,trump);
				}
				else if (party->attacker == player1)
				{
					input_player1(party,party->attacker, table, &position1, &quit, trump);
				}
				viewGame(party,table,deck,waste,position1,position2,listRank,listSuit);

				// wait for defender to play
				if (party->defender == bot1 || party->defender == bot2)
				{
					usleep(SPEED);
					botPlay(party->defender,party,table,trump);
				}
				else if (party->defender == player1)
				{
					input_player1(party,party->defender, table, &position1, &quit, trump);
				}
				viewGame(party,table,deck,waste,position1,position2,listRank,listSuit);
			}

			if (quit == TRUE)
			{
				exit(EXIT_SUCCESS);
			}
		}

		// AFTER EACH ROUND

		//printf("Round over.\n");
		// clean table
		if (playerInRound(party->defender))
		{
			//printf("%s defended successfully.\n",party->defender->name);
			// if defender won, table to waste
			tableClean(table,waste);
		}
		else
		{
			//printf("%s takes cards.\n",party->defender->name);
			// otherwise defender takes cards
			tableClean(table,party->defender->hand);

		}

		usleep(VIEW_SPEED);
		viewGame(party,table,deck,waste,position1,position2,listRank,listSuit);

		// hand cards if any left
		if (stackSize(deck) > 0)
		{
			handCardsRound(party,deck,HAND_SIZE);
			usleep(SPEED);
			viewGame(party,table,deck,waste,position1,position2,listRank,listSuit);

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
		viewGame(party,table,deck,waste,position1,position2,listRank,listSuit);
	}

	// after game ended
	viewGame(party,table,deck,waste,position1,position2,listRank,listSuit);
	printf("Game Over!\n");

	// find durak
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
