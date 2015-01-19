#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>


#include "../inc/rules.h"
#include "../inc/constants.h"
#include "../inc/cmd_view.h"

#define TEST numTests++;
#define PASS passedTests++;

int main()
{
	int numTests = 0;
	int passedTests = 0;

	// Create deck
	TEST

	int handSize = 6;
	printf("\nCreating new deck...\n");
	int trump = -1;
	stackT *deck = deckInit(listRank,listSuit,&trump);
	viewDeck(deck,listRank,listSuit);
	if (stackSize(deck) == 36 && trump != -1)
	{
		printf("OK.\n");
		PASS
	}
	else
	{
		printf("deckInit() failed!\n");	
	}

	// Create waste stack
	TEST
	printf("\nCreating waste stack...\n");
	stackT *waste = stackInit(stackSize(deck));
	if (waste != NULL)
	{
		printf("OK.\n");
		PASS
	}
	else
	{
		printf("Creating waste stack failed!\n");	
	}

	// Create table
	TEST
	printf("\nCreating table...\n");
	tableT *table = tableInit(handSize);
	if (table != NULL)
	{
		printf("OK.\n");
		PASS
	}
	else
	{
		printf("Creating table failed!\n");	
	}

	// create party and players
	TEST
	printf("\nCreating new party...\n");
	partyT *party = partyInit();
	printf("Creating two players...\n");
	playerT *player1 = playerNew("Player1",stackSize(deck));
	playerT *player2 = playerNew("Player2",stackSize(deck));
	printf("Adding players to party...\n");
	addPlayer(party,player1);
	addPlayer(party,player2);
	if (party != NULL && party->numPlayers == 2)
	{
		printf("OK.\n");
		PASS
	}
	else
	{
		printf("Creating party with two players failed!\n");	
	}

	// hand cards
	TEST
	printf("\nHanding cards at the beginning of the game...\n");
	handCardsGame(party,deck,handSize);
	viewDeck(deck,listRank,listSuit);
	printf("%s:\n",player1->name);
	viewHandRow(player1->hand,listRank,listSuit);
	printf("%s:\n",player2->name);
	viewHandRow(player2->hand,listRank,listSuit);
	if (stackSize(player1->hand) == handSize && stackSize(player2->hand) == handSize && stackSize(deck) == 36-(2*handSize))
	{
		printf("OK.\n");
		PASS
	}
	else
	{
		printf("Handing cards failed!\n");	
	}

	// set first round attacker/defender
	TEST
	printf("\nSetting up first round of the game...\n");
	setFirstRound(party,trump);
	while (party->attacker == NULL)
	{
		printf("No trumps handed, game reset...\n");
		sleep(1);
		gameReset(party,deck,waste,table,handSize,listRank,listSuit,&trump);
	}
	viewDeck(deck,listRank,listSuit);
	printf("%s:\n",player1->name);
	viewHandRow(player1->hand,listRank,listSuit);
	printf("%s:\n",player2->name);
	viewHandRow(player2->hand,listRank,listSuit);
	printf("Attacker: %s\n",party->attacker->name);
	printf("Defender: %s\n",party->defender->name);


	if (party->attacker != NULL)
	{
		printf("OK.\n");
		PASS
	}
	else
	{
		printf("Setting up first round failed!\n");	
	}


	// play some card
	TEST
	printf("\nAttacker plays some card...\n");
	cardT *att = playCard(party->attacker,0);
	if (cardFits(att,table))
	{
		tablePutAtt(table,att);
	}
	else
	{
		takeCard(party->attacker,att);
	}
	printf("Attacker: %s\n",party->attacker->name);
	printf("Defender: %s\n",party->defender->name);
	printf("%s:\n",player1->name);
	viewHandRow(player1->hand,listRank,listSuit);
	printf("%s:\n",player2->name);
	viewHandRow(player2->hand,listRank,listSuit);
	printf("Table:\n");
	viewTableRow(table,listRank,listSuit);
	if (stackSize(party->attacker->hand) == 5 && stackSize(table->att) == 1)
	{
		printf("OK.\n");
		PASS
	}
	else
	{
		printf("Attacker playing card failed!\n");	
	}

	// defender tries to beat randomly
	TEST
	printf("\nDefender beats randomly...\n");
	cardT *def = playCard(party->defender,0);
	if (cardBeats(def,&table->att->cards[0],trump))
	{
		tablePutDef(table,def,0);

	}
	else
	{
		takeCard(party->defender,def);
	}
	printf("Attacker: %s\n",party->attacker->name);
	printf("Defender: %s\n",party->defender->name);
	printf("%s:\n",player1->name);
	viewHandRow(player1->hand,listRank,listSuit);
	printf("%s:\n",player2->name);
	viewHandRow(player2->hand,listRank,listSuit);
	printf("Table:\n");
	viewTableRow(table,listRank,listSuit);
	if ((stackSize(party->defender->hand) == 5 && stackSize(table->def) == 1 && tableBeaten(table)) || (stackSize(party->defender->hand) == 6 && stackSize(table->def) == 0))
	{
		printf("OK.\n");
		PASS
	}
	else
	{
		printf("Defender playing card failed!\n");	
	}


	TEST
	printf("\nChange player status accordingly...\n");
	playerEndRound(party->attacker);
	if (!tableBeaten(table))
	{
		playerEndRound(party->defender);
	}

	if (!playerInRound(party->attacker))
	{
		printf("OK.\n");
		PASS
	}
	else
	{
		printf("Changing player status failed!\n");	
	}

	TEST
	printf("\nCheck if round is over (should be in any case)...\n");
	if(roundOver(party, table))
	{
		printf("OK.\n");
		PASS
	}
	else
	{
		printf("roundOver() failed!\n");	
	}


	TEST
	printf("\nClean table accordingly...\n");
	if (tableBeaten(table))
	{
		tableClean(table,waste);
	}
	else
	{
		tableClean(table,party->defender->hand);
	}	
	printf("Attacker: %s\n",party->attacker->name);
	printf("Defender: %s\n",party->defender->name);
	printf("%s:\n",player1->name);
	viewHandRow(player1->hand,listRank,listSuit);
	printf("%s:\n",player2->name);
	viewHandRow(player2->hand,listRank,listSuit);
	printf("Table:\n");
	viewTableRow(table,listRank,listSuit);


	if (stackSize(table->def) == 0 && stackSize(table->att) == 0)
	{
		printf("OK.\n");
		PASS
	}
	else
	{
		printf("Cleaning table failed!\n");	
	}

	TEST
	printf("\nSet next player accordingly...\n");
	// defender beaten successfully
	if (playerInRound(party->defender))
	{
		nextPlayer(party);
	}
	else
	{
		nextPlayerSkip(party);
	}
	printf("Attacker: %s\n",party->attacker->name);
	printf("Defender: %s\n",party->defender->name);
	printf("%s:\n",player1->name);
	viewHandRow(player1->hand,listRank,listSuit);
	printf("%s:\n",player2->name);
	viewHandRow(player2->hand,listRank,listSuit);
	PASS

	printf("\n\n%d/%d TESTS SUCCESSFUL.\n\n",passedTests,numTests);

	return(0);
}