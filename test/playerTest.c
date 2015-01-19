#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "../inc/card.h"
#include "../inc/stack.h"
#include "../inc/table.h"
#include "../inc/player.h"
#include "../inc/constants.h"
#include "../inc/cmd_view.h"

#define TEST numTests++;
#define PASS passedTests++;

int main()
{
	int numTests = 0;
	int passedTests = 0;

	// Test memory allocation
	TEST
	int size = 5;
	// need a malloc'd string here, because eventually it will be created dynamically
	char name_pre[] = "Hans";
	char *name = malloc(sizeof(char)*(strlen(name_pre)+1));
	strcpy(name,name_pre);

	printf("\nNew player with name %d and hand size %s...\n",size,name);
	playerT *player = playerNew(name,size);
	printf("Player name: %s\n",player->name);
	printf("Player hand size: %d\n",stackSize(player->hand));
	if (player != NULL && stackSize(player->hand) == 0 && player->hand->size == size && strcmp(player->name,name) == 0 && player->roundF == 0 && player->gameF == 0)
	{
		printf("OK.\n");
		PASS
	}
	else
	{
		printf("playerInit() failed!\n");
	}


	TEST
	printf("Deallocating player again...\n");
	playerDestroy(&player);
	
	if (player == NULL)
	{
		printf("OK.\n");
		PASS
	}
	else
	{
		printf("playerDestroy() failed!\n");
	}
	

	//Test setting player values
	TEST
	// allocate player name again
	name = malloc(sizeof(char)*(strlen(name_pre)+1));
	strcpy(name,name_pre);

	printf("\nNew player with name %d and hand size %s...\n",size,name);
	player = playerNew(name,size);
	printf("Setting gameF and roundF to TRUE...\n");
	playerStartGame(player);
	playerStartRound(player);
	if (player->roundF == TRUE && player->gameF == TRUE)
	{
		printf("OK.\n");
		PASS
	}
	else
	{
		printf("playerStartRound() or playerStartGame() failed!\n");
	}

	TEST
	printf("Reading gameF and roundF with appropriate functions...\n");
	if (playerInRound(player) == TRUE && playerInGame(player) == TRUE)
	{
		printf("OK.\n");
		PASS
	}
	else
	{
		printf("playerInRound() or playerInGame() failed!\n");
	}


	TEST
	printf("Setting gameF and roundF to FALSE...\n");
	playerEndGame(player);
	playerEndRound(player);
	if (player->roundF == FALSE && player->gameF == FALSE)
	{
		printf("OK.\n");
		PASS
	}
	else
	{
		printf("playerEndRound() or playerEndGame() failed!\n");
	}


	//Test player operations with cards
	TEST
	cardT *card = cardNew(ACE,SPADES,UP);

	printf("\nGiving player a card...\n");
	if (takeCard(player,card) == EXIT_SUCCESS && playerHandSize(player) == 1)
	{
		printf("OK.\n");
		PASS
	}
	else
	{
		printf("takeCard() failed!\n");
	}

	TEST
	printf("\nTrying to play illegal card...\n");
	if (playCard(player,1) == NULL && playCard(player,-1) == NULL)
	{
		printf("OK.\n");
		PASS
	}
	else
	{
		printf("playCard() failed to refuse playing an illegal card!\n");
	}

	TEST
	printf("\nTrying to play card legally...\n");
	cardT *played = playCard(player,0);
	if (cardCompareRank((const void *)played,(const void *)card) == 0  && cardCompareSuit((const void *)played,(const void *)card) == 0 && playerHandSize(player) == 0)
	{
		printf("OK.\n");
		PASS
	}
	else
	{
		printf("playCard() failed!\n");
	}

	printf("\n\n%d/%d TESTS SUCCESSFUL.\n\n",passedTests,numTests);

	return(0);
}