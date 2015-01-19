#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "../inc/card.h"
#include "../inc/stack.h"
#include "../inc/table.h"
#include "../inc/player.h"
#include "../inc/party.h"
#include "../inc/constants.h"

#define TEST numTests++;
#define PASS passedTests++;

int main()
{
	int numTests = 0;
	int passedTests = 0;

	// Test memory allocation
	TEST

	printf("\nNew party...\n");
	partyT *party = partyInit();
	if (party != NULL && party->numPlayers == 0 && party->attacker == NULL && party->defender == NULL)
	{
		printf("OK.\n");
		PASS
	}
	else
	{
		printf("partyInit() failed!\n");
		
	}


	TEST
	printf("Deallocating party again...\n");
	partyDestroy(&party);
	
	if (party == NULL)
	{
		printf("OK.\n");
		PASS
	}
	else
	{
		printf("playerDestroy() failed!\n");
	}
	

	//Test adding players
	TEST
	printf("\nNew party...\n");
	party = partyInit();


	// two new destructible players
	char name_pre[] = "One";
	char name_pre2[] = "Two";
	char name_pre3[] = "Three";

	char *name = malloc(sizeof(char)*(strlen(name_pre)+1));
	char *name2 = malloc(sizeof(char)*(strlen(name_pre2)+1));
	char *name3 = malloc(sizeof(char)*(strlen(name_pre3)+1));

	strcpy(name,name_pre);
	strcpy(name2,name_pre2);
	strcpy(name3,name_pre3);

	playerT *player1 = playerNew(name,1);
	playerT *player2 = playerNew(name2,1);
	playerT *player3 = playerNew(name3,1);


	printf("Adding player to Party...\n");
	addPlayer(party,player1);
	if (party->numPlayers == 1 && party->first == player1)
	{
		printf("OK.\n");
		PASS
	}
	else
	{
		printf("addPlayer() failed!\n");
	}


	TEST
	printf("Adding second player to party...\n");
	addPlayer(party,player2);
	if (party->numPlayers == 2 && player1->next == player2 && player2->next == player1)
	{
		printf("OK.\n");
		PASS
	}
	else
	{
		printf("addPlayer() failed!\n");
	}

	TEST
	printf("Adding third player to party...\n");
	addPlayer(party,player3);
	if (party->numPlayers == 3 && player1->next == player2 && player2->next == player3 && player3->next == player1)
	{
		printf("OK.\n");
		PASS
	}
	else
	{
		printf("addPlayer() failed!\n");
	}


	// Test switching to next player
	TEST
	printf("Setting player 1 att, player 2 def, all three players in game...\n");
	party->attacker = player1;
	party->defender = player2;
	player1->gameF = TRUE;
	player2->gameF = TRUE;
	player3->gameF = TRUE;
	printf("Switching to next player...\n");
	nextPlayer(party);
	if (party->attacker == player2 && party->defender == player3)
	{
		printf("OK.\n");
		PASS
	}
	else
	{
		printf("nextPlayer() failed!\n");
	}

	// Test switching to next player
	TEST
	printf("Switching to next player once again...\n");
	nextPlayer(party);
	if (party->attacker == player3 && party->defender == player1)
	{
		printf("OK.\n");
		PASS
	}
	else
	{
		printf("nextPlayer() failed!\n");
	}

	TEST
	printf("Switching to next player, skipping defender...\n");
	nextPlayerSkip(party);
	if (party->attacker == player2 && party->defender == player3)
	{
		printf("OK.\n");
		PASS
	}
	else
	{
		printf("nextPlayer() failed!\n");
	}

	TEST
	printf("Setting player1 out of game, switching again...\n");
	player1->gameF = FALSE;
	nextPlayer(party);
	if (party->attacker == player3 && party->defender == player2)
	{
		printf("OK.\n");
		PASS
	}
	else
	{
		printf("nextPlayer() failed!\n");
	}

	// Test destroying party with players
	TEST
	printf("Destroying party with three players...\n");
	partyDestroy(&party);
	
	if (party == NULL)
	{
		printf("OK.\n");
		PASS
	}
	else
	{
		printf("playerDestroy() failed!\n");
	}

	printf("\n\n%d/%d TESTS SUCCESSFUL.\n\n",passedTests,numTests);

	return(0);
}