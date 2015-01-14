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

int tableClean(tableT *tableP, stackT *discardP)
{
	// clean attack stack
	while (!stackEmpty(tableP->att))
	{
		// take care of memory errors, just in case
		if (stackPush(discardP,stackPop(tableP->att)) == EXIT_FAILURE)
		{
			return(EXIT_FAILURE);
		}
	}
	// clean defend stack
	while (!stackEmpty(tableP->def))
	{
		if (stackPush(discardP,stackPop(tableP->def)) == EXIT_FAILURE)
		{
			return(EXIT_FAILURE);
		}
	}

	// reset beats array
	int size = stackSize(tableP->att);
	for (int i = 0; i < size; ++i)
	{
		tableP->beats[i] = -1;
	}

	return(EXIT_SUCCESS);
}