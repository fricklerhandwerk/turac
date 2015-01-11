#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../inc/card.h"
#include "../inc/rules.h"
#include "../inc/cmd_view.h"

int testCardNew(void)
{
	// test card creation
	printf("Creating card...\n");
	cardT *card = cardNew(ACE,SPADES,UP);
	if (card != NULL)
	{
		viewCardLn(card,listRank,listSuit);
		return(EXIT_SUCCESS);
	}
	printf("MEMORY FAIL\n");
	return(EXIT_FAILURE);
}

int testSetFace(void)
{
	// test setting facing
	cardT *card = cardNew(ACE,SPADES,UP);
	viewCardLn(card,listRank,listSuit);
	printf("Setting card face down...\n");
	cardSetFace(card,DOWN);
	viewCardLn(card,listRank,listSuit);
	printf("Setting card face up...\n");
	cardSetFace(card,UP);
	viewCardLn(card,listRank,listSuit);

	if(card->face == UP)
	{
		return(EXIT_SUCCESS);
	}
	return(EXIT_FAILURE);
}

int testCompareRank(void)
{
	// compare rank
	cardT *card1 = cardNew(ACE,SPADES,UP);
	cardT *card2 = cardNew(TEN,HEARTS,UP);
	cardT *card3 = cardNew(TEN,SPADES,UP);
	viewCardLn(card1,listRank,listSuit);
	viewCardLn(card2,listRank,listSuit);
	viewCardLn(card3,listRank,listSuit);
	int cmp1 = cardCompareRank(card1,card2);
	printf("Comparing 1, 2: %2d\n",cmp1);
	int cmp2 = cardCompareRank(card2,card3);
	printf("Comparing 2, 3: %2d\n",cmp2);
	int cmp3 = cardCompareRank(card2,card1);
	printf("Comparing 2, 1: %2d\n",cmp3);
	if (cmp1 > 0 && cmp2 == 0 && cmp3 < 0)
	{
		return(EXIT_SUCCESS);
	}
	return(EXIT_FAILURE);
	
}

int testCompareSuit(void)
{
	// compare rank
	cardT *card1 = cardNew(ACE,SPADES,UP);
	cardT *card2 = cardNew(TEN,HEARTS,UP);
	cardT *card3 = cardNew(TEN,SPADES,UP);
	viewCardLn(card1,listRank,listSuit);
	viewCardLn(card2,listRank,listSuit);
	viewCardLn(card3,listRank,listSuit);
	int cmp1 = cardCompareSuit(card1,card2);
	printf("Comparing 1, 2: %2d\n",cmp1);
	int cmp2 = cardCompareSuit(card2,card3);
	printf("Comparing 2, 3: %2d\n",cmp2);
	int cmp3 = cardCompareSuit(card1,card3);
	printf("Comparing 1, 3: %2d\n",cmp3);
	if (cmp1 != 0 &&  cmp2 != 0 &&  cmp3 == 0)
	{
		return(EXIT_SUCCESS);
	}
	return(EXIT_FAILURE);
}

int main()
{
	#define NUM_TESTS 4
	// create array of all test functions
	int (*tests[NUM_TESTS])() = {&testCardNew,&testSetFace,&testCompareRank,&testCompareSuit};
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
		if (results[i] == EXIT_SUCCESS)
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