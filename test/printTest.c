#include <stdio.h>

#include "../inc/card.h"
#include "../inc/stack.h"
#include "../inc/rules.h"
#include "../inc/cmd_view.h"

int main(void)
{
	cardT *card1 = cardNew(ACE,SPADES,UP);
	cardT *card2 = cardNew(TEN,HEARTS,UP);
	cardT *card3 = cardNew(ACE,SPADES,UP);
	

	stackT *stack = stackInit(3);
	stack->cards[0] = card1;
	stack->cards[1] = card2;
	stack->cards[2] = card3;
	stack->top = 2;
	printf("%d",card3->rank);
	//viewCard(card3,listRank,listSuit);
	//viewCardLn(card3,listRank,listSuit);

	//viewHand(stack,listRank,listSuit);
	return 0;
}