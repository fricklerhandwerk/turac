#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../inc/card.h"
#include "../inc/rules.h"


void printCard(cardT *cardP)
{
	// point local char* to char* in rank/suit lists
	// => AFAIK no additional memory use
	const char *rank = listRank[cardP->rank];
	const char *suit = listSuit[cardP->suit];
	const char *face = listFace[cardP->face];

	printf("Rank: %s\nSuit: %s\nFace: %s\n\n",rank,suit,face);
}

int testCreateCard(void)
{
	// test card creation
	printf("Creating card...\n");
	cardT *card = cardNew(ACE,SPADES,DOWN);
	if (card == NULL)
	{
		printf("MEMORY FAIL\n");
		return(EXIT_FAILURE);
	}
	printCard(card);
	return(EXIT_SUCCESS);
}

int testSetFace(void)
{
	// test setting facing
	cardT *card = cardNew(ACE,SPADES,DOWN);
	printCard(card);
	printf("Setting card face up...\n");
	cardSetFace(card,UP);
	printCard(card);
	printf("Setting card face down...\n");
	cardSetFace(card,DOWN);
	printCard(card);

	if(card->face != DOWN)
	{
		return(EXIT_FAILURE);
	}
	else
	{
		return(EXIT_SUCCESS);
	}
}

int testCompareRank(void)
{
	// compare rank
	cardT *card1 = cardNew(ACE,SPADES,DOWN);
	cardT *card2 = cardNew(TEN,HEARTS,DOWN);
	cardT *card3 = cardNew(TEN,SPADES,DOWN);
	printCard(card1);
	printCard(card2);
	printCard(card3);
	int cmp1 = cardCompareRank(card1,card2);
	printf("Comparing 1, 2: %2d\n",cmp1);
	int cmp2 = cardCompareRank(card2,card3);
	printf("Comparing 2, 3: %2d\n",cmp2);
	int cmp3 = cardCompareRank(card2,card1);
	printf("Comparing 2, 1: %2d\n",cmp3);
	if (cmp1 < 0 || cmp2 != 0 || cmp3 > 0)
	{
		return(EXIT_FAILURE);
	}
	else
	{
		return(EXIT_SUCCESS);
	}
}

int testCompareSuit(void)
{
	// compare rank
	cardT *card1 = cardNew(ACE,SPADES,DOWN);
	cardT *card2 = cardNew(TEN,HEARTS,DOWN);
	cardT *card3 = cardNew(TEN,SPADES,DOWN);
	printCard(card1);
	printCard(card2);
	printCard(card3);
	int cmp1 = cardCompareSuit(card1,card2);
	printf("Comparing 1, 2: %2d\n",cmp1);
	int cmp2 = cardCompareSuit(card2,card3);
	printf("Comparing 2, 3: %2d\n",cmp2);
	int cmp3 = cardCompareSuit(card1,card3);
	printf("Comparing 1, 3: %2d\n",cmp3);
	if (cmp1 == 0 || cmp2 == 0 || cmp3 != 0)
	{
		return(EXIT_FAILURE);
	}
	else
	{
		return(EXIT_SUCCESS);
	}
}

int main()
{
	#define NUM_TESTS 4
	// create array of all test functions
	int (*tests[NUM_TESTS])() = {&testCreateCard,&testSetFace,&testCompareRank,&testCompareSuit};
	// create array for result values
	int results[NUM_TESTS];
	int total = 0;

	// execute all functions in the tests array
	for (int i = 0; i < NUM_TESTS; ++i)
	{
		printf("TEST NO. %d\n\n",i+1);

		// write results to results array
		results[i] = (tests[i]());

		// print test results
		printf("\nTEST %d ",i+1);
		if (!results[i])
		{
			printf("SUCCESSFUL.\n\n\n");
			// add to total
			total++;
		}
		else
		{
			printf("FAILED!\n\n\n");
		}
	}

	printf("%d/%d TESTS SUCCESSFUL.\n\n",total,NUM_TESTS);

	






	return(0);

}