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


	// create table
	tableT *table = tableInit(size);
	// put all attack cards on table
	for (int i = 0; i < size; ++i)
	{
		tablePutAtt(table,stackPop(att));
		/*
		if(tablePutDef(table,stackPop(def),i))
		{
			printf("fail\n");
		}
		*/
	}


	tablePutDef(table,stackPop(def),0);
	tablePutDef(table,stackPop(def),1);
	tablePutDef(table,stackPop(def),2);


	printf("viewTable()\n");
	viewTable(table,listRank,listSuit);

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