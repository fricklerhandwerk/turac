#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../inc/card.h"
#include "../inc/stack.h"
#include "../inc/constants.h"
#include "../inc/cmd_view.h"

void testHand(void)
{
	int size = 6;

	// create random stack
	stackT *hand = stackInit(size);

	for (int i = 0; i < size; ++i)
	{
		int rank = rand() % 7;
		int suit = rand() % 4;
		stackPush(hand,cardNew(rank,suit,UP));
	}

	printf("viewHandRow()\n");
	viewHandRow(hand,listRank,listSuit);
	printf("viewHandCol()\n");
	viewHandCol(hand,listRank,listSuit);
}

void testDeck(void)
{
	int size = 6;
	stackT *stack = stackInit(size);

	for (int i = 0; i < size; ++i)
	{
		int rank = rand() % 7;
		int suit = rand() % 4;
		stackPush(stack,cardNew(rank,suit,DOWN));
	}
	// set first card face up
	cardSetFace(&stack->cards[0],UP);

	printf("viewDeck()\n");

	viewDeck(stack,listRank,listSuit);

	cardT *waste;
	for (int i = 0; i < size; ++i)
	{
		waste = stackPop(stack);
		viewDeck(stack,listRank,listSuit);
	}
}

void testTable(void)
{
	int size = 6;
	// create two random stacks
	stackT *att = stackInit(size);
	stackT *def = stackInit(size);

	for (int i = 0; i < size; ++i)
	{
		// one full size
		int rank = rand() % 7;
		int suit = rand() % 4;
		stackPush(att,cardNew(rank,suit,UP));
		// one half size
		if (i%2 == 0)
		{
			rank = rand() % 7;
			suit = rand() % 4;
			stackPush(def,cardNew(rank,suit,UP));
		}
	}

	printf("hands:\n");

	viewHandRow(att,listRank,listSuit);
	viewHandRow(def,listRank,listSuit);

	// create table
	tableT *table = tableInit(size);
	// put all attack cards on table
	for (int i = 0; i < size; ++i)
	{
		tablePutAtt(table,stackPop(att));
	}

	// put all defend cards on table

	tablePutDef(table,stackPop(def),2);
	tablePutDef(table,stackPop(def),0);


	printf("beat:\n[");
	for (int i = 0; i < size; ++i)
	{
		printf("%d,",table->beats[i]);
	}
	printf("]\n");


	printf("viewTableRow()\n");
	viewTableRow(table,listRank,listSuit);
	printf("Put new card...\n");
	viewCardLn(&def->cards[def->top],listRank,listSuit);
	tablePutDef(table,stackPop(def),3);

	printf("beat:\n[");
	for (int i = 0; i < size; ++i)
	{
		printf("%d,",table->beats[i]);
	}
	printf("]\n");

	printf("viewTableCol()\n");
	viewTableCol(table,listRank,listSuit);
}

int main(void)
{	
	// throw dice
	srand(time(NULL));
	//testHand();
	//testDeck();
	testTable();

	return 0;
}