#include <stdio.h>

#include "../inc/card.h"
#include "../inc/stack.h"
#include "../inc/rules.h"
#include "../inc/cmd_view.h"

int main(void)
{
	cardT *card1 = cardNew(ACE,SPADES,UP);
	cardT *card2 = cardNew(TEN,HEARTS,UP);
	cardT *card3 = cardNew(KING,CLUBS,UP);

	stackT *stack = stackInit(3);
	stackPush(stack,card1);
	stackPush(stack,card2);
	stackPush(stack,card3);

	viewHand(stack,listRank,listSuit);
	return 0;
}