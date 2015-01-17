/* Durak game table implementation */

#include <stdio.h>
#include <stdlib.h>

#include "table.h"

tableT *tableInit(int sizeTable)
{
	// allocate memory for struct
	tableT *tableP = malloc(sizeof(tableT));

	// handle allocation errors
	if (tableP == NULL)
	{
		return(NULL);
	}

	// allocate memory for struct members
	stackT *attP = stackInit(sizeTable);
	stackT *defP = stackInit(sizeTable);
	int *beatsP = malloc(sizeof(int)*sizeTable);

	// handle allocation errors
	if (attP == NULL || defP == NULL || beatsP == NULL)
	{
		return(NULL);
	}

	// link pointers
	tableP->att = attP;
	tableP->def = defP;
	tableP->beats = beatsP;

	// initialize `beats` array with values
	for (int i = 0; i < sizeTable; ++i)
	{
		tableP->beats[i] = -1;
	}

	return(tableP);
}

void tableDestroy(tableT **tableP)
{
	// destroy stacks -- please kill me, hashtag #pointermadness
	stackDestroy(&(*tableP)->att);
	stackDestroy(&(*tableP)->def);

	// destroy array
	free((*tableP)->beats);
	(*tableP)->beats = NULL;
	
	// free table memory and reset pointer
	free(*tableP);
	*tableP = NULL;
}

// Put card on attack or defend stack
int tablePutAtt(tableT *tableP, cardT *cardP)
{
	if(cardP == NULL || stackPush(tableP->att,cardP) == EXIT_FAILURE)
	{
		return(EXIT_FAILURE);
	}
	return(EXIT_SUCCESS);
}

int tablePutDef(tableT *tableP, cardT *cardP, int beatPos)
{
	// check validity of defense assignment
	// exit with error if pushing not possible for some reason
	if(cardP == NULL || beatPos < 0 || beatPos >= stackSize(tableP->att) || stackPush(tableP->def,cardP) == EXIT_FAILURE)
	{
		/* some debugging
		printf("FIAL\n");
		if(cardP == NULL)
		{
			printf("CardPointer NULL!\n");
		}
		if(beatPos < 0 || beatPos >= stackSize(tableP->att))
		{
			printf("beatPos off range (%d/%d)!\n",beatPos,stackSize(tableP->att)-1);
		}
		*/
		return(EXIT_FAILURE);
	}

	// mark the position in `beats` array
	// which corresponds to the position of cardDef on the def stack (topmost)
	// with the position of the card to beat on the att stack (given)
	tableP->beats[stackSize(tableP->def)-1] = beatPos;

	return(EXIT_SUCCESS);
}

// Check if table is full so no more attacking can be made
int tableFull(tableT *tableP)
{
	return (stackFull(tableP->att));
}

// Check if all attacking cards on the table are beaten
int tableBeaten(tableT *tableP)
{
	return (stackFull(tableP->def));
}

int tableClean(tableT *tableP, stackT *destP)
{
	// clean attack stack
	while (!stackEmpty(tableP->att))
	{
		// take care of memory errors, just in case
		if (stackPush(destP,stackPop(tableP->att)) == EXIT_FAILURE)
		{
			return(EXIT_FAILURE);
		}
	}
	
	// clean defend stack
	while (!stackEmpty(tableP->def))
	{
		if (stackPush(destP,stackPop(tableP->def)) == EXIT_FAILURE)
		{
			return(EXIT_FAILURE);
		}
	}

	// reset `beats` array
	int size = stackSize(tableP->att);
	for (int i = 0; i < size; ++i)
	{
		tableP->beats[i] = -1;
	}

	return(EXIT_SUCCESS);
}