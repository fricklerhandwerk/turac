/* Durak bot interface */

#ifndef BOT_H
#define BOT_H

#include <party.h>
#include <table.h>
#include <rules.h>

/* BOT FUNCTIONS
 *
 * The basic idea is that the stupid bot discerns two states,
 * which he reads from the party information:
 *
 * a) he is attacking (whenever he is not defending)
 * b) he is defending
 *
 *
 * Depending on his state, he will do the following:
 *
 * ATTACK
 * Take the lowest card in hand that fits on the table.
 * For this, sort hand such that it is ordered by rank
 + for all cards which are not trumps, and following
 + are all the trump cards, sorted by rank.
 * Then, check each card, starting with the lowest,
 + if it fits on the table.
 * Exit routine after putting the first matching card
 + on the table.
 * If there is no matching card on hand, set roundF = FALSE
 * (i.e. stop attacking for this round) and exit.
 *
 * DEFEND
 * For each unbeaten card on the table, take the lowest card
 + in hand that would beat this attacking card.
 * For this, sort hand as for attack, then check each card
 + in ascending rank order.
 * This is super inefficient, but simpler to implement.
 * When a beating card is found, put it on the table and work on the next one.
 * Once all attacking cards are beaten, exit routine.
 * If no beating card is found for any, set roundF = FALSE to take cards and exit.
 */

// sort bot's cards by actual game value, so he can work with it
void botSortHand(playerT *botP, int trumpSuit);

// attack, duh.
void botAttack(playerT *botP, tableT *tableP, int trumpSuit);

// defend
void botDefend(playerT *botP, tableT *tableP, int trumpSuit);

// decide what to do and do it
void botPlay(playerT *botP, partyT *partyP, tableT *tableP, int trumpSuit);

#endif // BOT_H