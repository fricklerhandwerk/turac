/*Durak player Input interface*/

#ifndef INPUT_H
#define INPUT_H

#include <party.h>
#include <table.h>
#include <rules.h>
#include <stdio.h>
#include <player.h>

void PlayerSortHand(playerT *playerP, int trumpSuit);

void input_player1(playerT *playerP,tableT *tableP, int *pos, int trumpSuit);

void input_twoplayers(playerT *playerPone, playerT *playerPtwo, tableT *tableP, int *pos_one, int *pos_two, int trumpSuit);


#endif
