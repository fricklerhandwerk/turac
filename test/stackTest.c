#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "../inc/card.h"
#include "../inc/stack.h"
#include "../inc/rules.h"
#include "../inc/cmd_view.h"

#define SIZE 36

int testStackInitDestroy(void)
{
	printf("Initializing stack with size %d...\n",SIZE);
	stackT *stack = stackInit(SIZE);
	printf("Stack size: %d\nStack top: %d\n",stack->size,stack->top);
	if (stack != NULL && stack->size == SIZE && stack->top == -1)
	{
		printf("OK.\n");
	}
	else
	{
		printf("stackInit() failed!\n");
		return(EXIT_FAILURE);
	}
	
	printf("Deallocating stack again...\n");
	stackDestroy(&stack);
	
	//printf("stack size: %d\n",stack->size);
	if (stack == NULL)
	{
		printf("OK.\n");
		return(EXIT_SUCCESS);
	}
	printf("stackDestroy() failed!\n");
	return(EXIT_FAILURE);
}

int testStackBasicOps(void)
{
	cardT *card = cardNew(ACE,SPADES,UP);
	printf("New stack with size 1...\n");
	stackT *stack = stackInit(1);
	
	printf("Checking if empty...\n");
	if (stackEmpty(stack))
	{
		printf("OK.\n");
	}
	else
	{
		printf("isEmpty() failed!\n");
		return(EXIT_FAILURE);
	}
	
	printf("Pushing card...\n");
	stackPush(stack,card);
	if (stack->size == 1 && stack->top == 0)
	{
		printf("Updated stack: ");
		viewHand(stack,listRank,listSuit);
	}
	else
	{
		printf("stackPush() failed!\n");
		return(EXIT_FAILURE);
	}
	
	printf("Checking if full...\n");
	if (stackFull(stack))
	{
		printf("OK.\n");
	}
	else
	{
		printf("isFull() failed!\n");
		return(EXIT_FAILURE);
	}
	
	printf("Popping card...\n");
	cardT *card2 = stackPop(stack);
	if (card->rank == ACE && stackEmpty(stack) && stack->top == -1)
	{
		printf("Popped card: ");
		viewCardLn(card2,listRank,listSuit);
	}
	else
	{
		printf("stackPop() failed!\n");
		return(EXIT_FAILURE);
	}
	
	return(EXIT_SUCCESS);
}

void testStackShuffle(void)
{
	// create some cards
	cardT *card1 = cardNew(ACE,SPADES,UP);
	cardT *card2 = cardNew(TEN,HEARTS,UP);
	cardT *card3 = cardNew(KING,CLUBS,UP);
	cardT *card4 = cardNew(QUEEN,TILES,UP);
	
	// create stack und push cards inside
	stackT *stack = stackInit(4);
	stackPush(stack,card1);
	stackPush(stack,card2);
	stackPush(stack,card3);
	stackPush(stack,card4);
	
	printf("Shuffling stack, please wait 5s...\n   ");
	viewHand(stack,listRank,listSuit);
	for(int i = 0; i < 5; i++)
	{
		printf("%d: ",i);
		stackShuffle(stack);
		viewHand(stack,listRank,listSuit);
		sleep(1);
	}
	printf("Compare results by hand.\n");
	
	
	return;
	
}
int main()
{
	//testStackInitDestroy();
	//testStackBasicOps();
	testStackShuffle();
	return(0);
}