/* Durak game table interface */

#ifndef TABLE_H
#define TABLE_H

#include "stack.h"

/* TABLE DATA TYPE
 *
 * Holds two equally sized stacks of cards,
 + one for the attacking cards which have to be beaten,
 + one for the defending cards, which beat the attacking ones.
 * The `beats array is a mapping of cards in def to cards in att
 + that tells us which card beats which.
 * Ex: [1,4] => def->cards[0] beats att->cards[1]
 *              def->cards[1] beats att->cards[4]
 */

typedef struct
{
	stackT *att;
	stackT *def;
	int *beats;
} tableT;

// Allocate memory for table of given size and initialize member variables
tableT *tableInit(int sizeTable);

// Free members' and table memory
// Double pointer do get rid of the pointer itself as well
void tableDestroy(tableT **tableP);

// Check if table is full so no more attacking can be made
int tableFull(tableT *tableP);

// Check if all attacking cards on the table are beaten
int tableBeaten(tableT *tableP);

// Put all cards from the table to the stack with discarded cards
// Reset beating map
void tableClean(tableT *tableP, stackT *discardP);

#endif // TABLE_H