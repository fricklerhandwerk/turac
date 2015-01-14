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

// Put card on attack stack
int tablePutAtt(tableT *tableP, cardT *cardP);
// Put defending card "on top of" attacking card
// using the attacking card's position on the att stack
int tablePutDef(tableT *tableP, cardT *cardP, int beatPos);

// Check if table is full so no more attacking can be made
int tableFull(tableT *tableP);

// Check if all attacking cards on the table are beaten
int tableBeaten(tableT *tableP);

// Put all cards from the table to a destination stack (pick up or discard)
// Reset beating map
int tableClean(tableT *tableP, stackT *destP);

#endif // TABLE_H