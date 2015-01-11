/* Commandline view interface */

#ifndef CMD_VIEW_H
#define CMD_VIEW_H

/* VIEW FUNCTIONS FOR COMMAND LINE */

#include "card.h"
#include "stack.h"

// Print card without linebreak
// Takes card and rank/suit lists from rules file
void viewCard(cardT *cardP, const char **listRank, const char **listSuit);

// Print card with  linebreak
void viewCardLn(cardT *cardP, const char **listRank, const char **listSuit);

// Shows cards of a stack next to each other
void viewHand(stackT *handP, const char **listRank, const char **listSuit);


#endif // CMD_VIEW_H 