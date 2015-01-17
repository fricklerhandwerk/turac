#ifndef RULES_H
#define RULES_H

/* GAME FUNCTIONS AND RULES */

#include "constants.h"
#include "party.h"
#include "table.h"


// Create playing deck using rank and suit lists
// NOTE: Automatically shuffles and finds a trump suit
// by uncovering the card at the bottom.
// WARNING: Must destroy newly created cards
// after pushing them onto the stack, otherwise memory leaks
stackT *deckInit(const char **listRank, const char **listSuit, int *trumpSuit);

// Hand cards to players in party Order until HAND_SIZE is reached for each player
// Reduce stack size on the way
void handCards(partyT *partyP, stackT *stackP, int sizeHand);

// Determine if a card has trump suit
int isTrump(cardT *cardP, int trumpSuit);

// Determine if card `a` beats card `b` using trump suit
int cardBeats(cardT *aP, cardT *bP, int trumpSuit);

// Determine if a chosen card can be added to the table for the defender to beat
int cardFits(cardT *cardP, tableT *tableP);

// Determine if current round is over
// check if one of the conditions is true:
// - table full && all cards beaten
// - table not full, but attacking player(s) done and all cards beaten
// - table not full, but defending player has taken cards
int roundOver(partyT *partyP, tableT *tableP);

// Determine if game has ended
// Check if deck is empty && 1 or no player has cards on his hands
int gameOver(partyT *partyP, stackT *deckP);


/* TODO: Add more functions for rule-checking */
#define RULES_H
