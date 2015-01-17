#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "../inc/card.h"
#include "../inc/stack.h"
#include "../inc/table.h"
#include "../inc/constants.h"
#include "../inc/cmd_view.h"

#define TEST numTests++;
#define PASS passedTests++;

int main()
{
	int numTests = 0;
	int passedTests = 0;

	/* Test memory allocation */
	TEST
	int size = 5;
	printf("\nNew table with size %d...\n",size);
	tableT *table = tableInit(size);
	printf("Table size: %d\n",table->att->size);
	if (table != NULL && table->att->size == size && table->def->size == size)
	{
		printf("OK.\n");
		PASS
	}
	else
	{
		printf("tableInit() failed!\n");
		
	}


	TEST
	printf("Deallocating table again...\n");
	tableDestroy(&table);
	
	if (table == NULL)
	{
		printf("OK.\n");
		PASS
	}
	else
	{
		printf("tableDestroy() failed!\n");
	}
	


	/* Test card operations */

	TEST
	cardT *card = cardNew(ACE,SPADES,UP);
	size = 1;

	printf("\nNew table with size %d...\n",size);
	table = tableInit(size);
	
	printf("Checking if not full...\n");
	if (!tableFull(table))
	{
		printf("OK.\n");
		PASS
	}
	else
	{
		printf("tableFull() failed!\n");
		
	}

	TEST
	printf("Putting card on attack...\n");
	int att = tablePutAtt(table,card);
	if (att == EXIT_SUCCESS)
	{
		printf("OK.\n");
		PASS
	}
	else
	{
		printf("tablePutAtt() failed to put a card on a free attack stack!\n");
		
	}
	
	TEST
	printf("Checking if table full...\n");
	if (tableFull(table))
	{
		printf("OK.\n");
		PASS
	}
	else
	{
		printf("tableFull() failed!\n");
		
	}

	TEST
	printf("Putting card on attack again, illegally...\n");
	att = tablePutAtt(table,card);
	if (att == EXIT_FAILURE)
	{
		printf("OK.\n");
		PASS
	}
	else
	{
		printf("tablePutAtt() failed to refuse putting a card on a full stack!\n");
	}

	TEST
	printf("Checking if table beaten...\n");
	if (!tableBeaten(table))
	{
		printf("OK.\n");
		PASS
	}
	else
	{
		printf("tableBeaten() failed!\n");
	}

	TEST
	printf("Putting card on defend with illegal position...\n");
	int def = tablePutDef(table,card,1);
	if (att != EXIT_SUCCESS)
	{
		printf("OK.\n");
		PASS
	}
	else
	{
		printf("tablePutDef() failed to refuse putting a card with invalid defense assignment!\n");
	}

	TEST
	printf("Putting card on defend legally...\n");
	int beat = 0;
	def = tablePutDef(table,card,beat);
	if (def == EXIT_SUCCESS && table->beats[stackSize(table->def)-1] == beat)
	{
		printf("OK.\n");
		PASS
	}
	else
	{
		printf("tablePutDef() failed to put a card on defense!\n");
	}

	TEST
	printf("Checking if table beaten...\n");
	if (tableBeaten(table))
	{
		printf("OK.\n");
		PASS
	}
	else
	{
		printf("tableBeaten() failed!\n");
		
	}

	TEST
	printf("Putting defend card on beaten table...\n");
	def = tablePutDef(table,card,0); // assignment does not matter here
	if (att != EXIT_SUCCESS)
	{
		printf("OK.\n");
		PASS
	}
	else
	{
		printf("tablePutDef() failed to refuse putting a defense card on a beaten table!\n");
		
	}
	
	TEST
	printf("\nTaking away all the cards...\n");
	stackT *stack = stackInit(size*2); // a place to put both att and def
	int clean = tableClean(table,stack);

	printf("Checking for internal success...\n");
	if (clean == EXIT_SUCCESS)
	{
		printf("OK.\n");
		PASS
	}
	else
	{
		viewCardLn(&table->def->cards[0],listRank,listSuit);
		printf("tableClean() failed for its own reasons!\n");
	}

	TEST
	printf("Checking if `beats` array reset...\n");
	int beats = 1;
	for (int i = 0; i < stackSize(table->att)-1; ++i)
	{
		if (table->beats[i] != -1)
		{
			printf("tableClean() failed and did not reset `beats` array!\n");
			beats = 0;
			break;
		}
	}
	if (beats)
	{
		printf("OK.\n");
		PASS
	}


	TEST
	printf("Checking if all cards have been moved...\n");
	if (stackSize(stack) == size*2 && !tableBeaten(table) && !tableFull(table))
	{
		printf("OK.\n");
		PASS
	}
	else
	{
		printf("tableClean() failed and did not transport all the cards!\n");
		printf("Target stack size: %d\n",stackSize(stack));
	}
	
	
	printf("\n\n%d/%d TESTS SUCCESSFUL.\n\n",passedTests,numTests);

	return(0);
}