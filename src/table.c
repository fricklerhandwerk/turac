/* Durak game table implementation */

#include <stdio.h>
#include <stdlib.h>

#include "table.h"

// Allocate memory for table of given size and initialize member variables
tableT *tableInit(int sizeTable)
{
	// allocate memory for struct
	tableT *tableP = malloc(sizeof(tableT));
	// allocate memory for struct members
	stackT *attP = stackInit(sizeTable);
	stackT *defP = stackInit(sizeTable);
	int *beatsP = malloc(sizeof(int)*sizeTable);
	// link pointers
	tableP->att = attP;
	tableP->def = defP;
	tableP->beats = beatsP;

	return(tableP);
}

// Free members' and table memory
// Double pointer do get rid of the pointer itself as well
void tableDestroy(tableT **tableP);

// Check if table is full so no more attacking can be made
int tableFull(tableT *tableP);

// Check if all attacking cards on the table are beaten
int tableBeaten(tableT *tableP);

// Reset beating map
void tableEmpty(tableT *tableP);