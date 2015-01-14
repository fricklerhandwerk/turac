/* Commandline view interface */

#ifndef CMD_VIEW_H
#define CMD_VIEW_H

/* VIEW FUNCTIONS FOR COMMAND LINE */

#include "card.h"
#include "stack.h"
#include "table.h"


// Print card without linebreak
// Takes card and rank/suit lists from rules file
void viewCard(cardT *cardP, const char **listRank, const char **listSuit);

// Print card with linebreak
void viewCardLn(cardT *cardP, const char **listRank, const char **listSuit);

// Shows cards of a stack next to each other
void viewHandRow(stackT *handP, const char **listRank, const char **listSuit);
void viewHandCol(stackT *handP, const char **listRank, const char **listSuit);

// Shows deck of cards with total number of elements and the flipped ones next to it
// this is quite game specific, but in durak the flipped trump is part of the deck, not the table
void viewDeck(stackT *deckP, const char **listRank, const char **listSuit);

// Show table
void viewTableRow(tableT *tableP, const char **listRank, const char **listSuit);
void viewTableCol(tableT *tableP, const char **listRank, const char **listSuit);


#endif // CMD_VIEW_H