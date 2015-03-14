/*Durak player Input interface*/

#ifndef INPUT_H
#define INPUT_H

#include <stdio.h>
#include <stdlib.h>
#include "player.h"
#include "party.h"
#include "table.h"
#include "rules.h"

// player keys
#define P1_LT 'a'
#define P1_RT 'd'
#define P1_AC 'w'
#define P1_EN 'e'
#define P1_ST 'q'

#define P2_LT 'j'
#define P2_RT 'l'
#define P2_AC 'i'
#define P2_EN 'o'
#define P2_ST 'u'

#define QUIT '.'


void input_player1(partyT *partyP, playerT *playerP,tableT *tableP, int *pos, int *quit, int trumpSuit);

void input_twoplayers(partyT *partyP, playerT *playerPone, playerT *playerPtwo, tableT *tableP, int *pos_one, int *pos_two, int *quit, int trumpSuit);

#endif // INPUT
