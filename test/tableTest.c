#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "../inc/card.h"
#include "../inc/stack.h"
#include "../inc/table.h"
#include "../inc/constants.h"
#include "../inc/cmd_view.h"

int main()
{
	int numTests = 0;
	int passedTests = 0;

	/* Test memory allocation */

	numTests++;
	int size = 5;
	printf("\nNew table with size %d...\n",size);
	tableT *table = tableInit(size);
	printf("Table size: %d\n",table->att->size);
	if (table != NULL && table->att->size == size && table->def->size == size)
	{
		printf("OK.\n");
		passedTests++;
	}
	else
	{
		printf("tableInit() failed!\n");
		
	}


	numTests++;
	printf("Deallocating table again...\n");
	tableDestroy(&table);
	
	if (table == NULL)
	{
		printf("OK.\n");
		passedTests++;
	}
	else
	{
		printf("tableDestroy() failed!\n");
	}
	


	/* Test card operations */

	numTests++;
	cardT *card = cardNew(ACE,SPADES,UP);
	size = 1;

	printf("\nNew table with size %d...\n",size);
	table = tableInit(size);
	
	printf("Checking if not full...\n");
	if (!tableFull(table))
	{
		printf("OK.\n");
		passedTests++;
	}
	else
	{
		printf("tableFull() failed!\n");
		
	}

	numTests++;
	printf("Putting card on attack...\n");
	int att = tablePutAtt(table,card);
	if (att == EXIT_SUCCESS)
	{
		printf("OK.\n");
		passedTests++;
	}
	else
	{
		printf("tablePutAtt() failed to put a card on a free attack stack!\n");
		
	}
	
	numTests++;
	printf("Checking if table full...\n");
	if (tableFull(table))
	{
		printf("OK.\n");
		passedTests++;
	}
	else
	{
		printf("tableFull() failed!\n");
		
	}

	numTests++;
	printf("Putting card on attack again, illegally...\n");
	att = tablePutAtt(table,card);
	if (att == EXIT_FAILURE)
	{
		printf("OK.\n");
		passedTests++;
	}
	else
	{
		printf("tablePutAtt() failed to refuse putting a card on a full stack!\n");
	}

	numTests++;
	printf("Checking if table beaten...\n");
	if (!tableBeaten(table))
	{
		printf("OK.\n");
		passedTests++;
	}
	else
	{
		printf("tableBeaten() failed!\n");
	}

	numTests++;
	printf("Putting card on defend with illegal position...\n");
	int def = tablePutDef(table,card,1);
	if (att != EXIT_SUCCESS)
	{
		printf("OK.\n");
		passedTests++;
	}
	else
	{
		printf("tablePutDef() failed to refuse putting a card with invalid defense assignment!\n");
	}

	numTests++;
	printf("Putting card on defend legally...\n");
	int beat = 0;
	def = tablePutDef(table,card,beat);
	if (def == EXIT_SUCCESS && table->beats[stackTop(table->def)] == beat)
	{
		printf("OK.\n");
		passedTests++;
	}
	else
	{
		printf("tablePutDef() failed to put a card on defense!\n");
	}

	numTests++;
	printf("Checking if table beaten...\n");
	if (tableBeaten(table))
	{
		printf("OK.\n");
		passedTests++;
	}
	else
	{
		printf("tableBeaten() failed!\n");
		
	}

	numTests++;
	printf("Putting defend card on beaten table...\n");
	def = tablePutDef(table,card,0); // assignment does not matter here
	if (att != EXIT_SUCCESS)
	{
		printf("OK.\n");
		passedTests++;
	}
	else
	{
		printf("tablePutDef() failed to refuse putting a defense card on a beaten table!\n");
		
	}
	
	numTests++;
	printf("\nTaking away all the cards...\n");
	stackT *stack = stackInit(size*2); // a place to put both att and def
	int clean = tableClean(table,stack);

	printf("Checking for internal success...\n");
	if (clean == EXIT_SUCCESS)
	{
		printf("OK.\n");
		passedTests++;
	}
	else
	{
		viewCardLn(&table->def->cards[0],listRank,listSuit);
		printf("tableClean() failed for its own reasons!\n");
	}

	numTests++;
	printf("Checking if `beats` array reset...\n");
	int beats = 1;
	for (int i = 0; i < stackTop(table->att); ++i)
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
		passedTests++;
	}


	numTests++;
	printf("Checking if all cards have been moved...\n");
	if (stackTop(stack)+1 == size*2 && !tableBeaten(table) && !tableFull(table))
	{
		printf("OK.\n");
		passedTests++;
	}
	else
	{
		printf("tableClean() failed and did not transport all the cards!\n");
		printf("Target stack size: %d\n",stackTop(stack)+1);
	}
	
	
	
	printf("\n\n%d/%d TESTS SUCCESSFUL.\n\n",passedTests,numTests);

	return(0);
}