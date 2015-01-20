/*Durak player Input interface*/

#ifndef INPUT_H
#define INPUT_H

#include <party.h>
#include <table.h>
#include <rules.h>
#include <stdio.h>
#include <player.h>

void PlayerSortHand(playerT *playerP, int trumpSuit);

void input_player1(playerT *playerP, int *position, int trumpSuit);

void input_twoplayers(playerT *playerPone, playerT *playerPtwo, int *position_one, int *position_two, int trumpSuit);


#endif
