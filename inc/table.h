/* Table interface */

#ifndef TABLE_H
#define TABLE_H

/* TABLE DATA TYPE
 *
 * Holds two equally sized stacks of cards,
 + one for the attacking cards which have to be beaten,
 + one for the defending cards, which beat the attacking ones.
 * The `beats[2]` array is a mapping of cards in def to cards in att
 + that tells us which card beats which. Ex: [[0,2][1,4]]
 */

typedef struct
{
	stackT *att;
	stackT *def;
	int *beats[2];
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

// Reset beating map
void tableEmpty(tableT *tableP);

#endif // TABLE_H