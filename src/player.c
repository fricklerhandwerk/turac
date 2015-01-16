/* Implementation of player functions */

#include <stdlib.h>

#include "../inc/card.h"

playerT list = NULL;

// Allocate memory for player with empty hand
playerT *playerNew(char *name){

  // allocate memory for array of player
  playerT *player;
  player = malloc(sizeof(playerT));

  // handle allocation errors
  if (player == NULL)
  {
    return(NULL);
  }

  player->name = name;
  player->hand = NULL;
  //player->currentF = 0;
  player->stopF = 1;
  player->doneF = 0;
  player->next = list->next;
  list->next = player;

  return(player);
}

// Free member and player memory
void playerDestroy(playerT **playerP){
  playerT tmp = playerP->next;
  playerP->next = playerP->next->next;
  free(*playerP);
  *playerP = NULL;
}

// Add player to party
void playerAdd(playerT *partyP, playerT *playerP){
  for (int i = 0; i < partyP.numPlayers; i++){
    playerP = playerP.next;
    partyP.currentPlayer = partyP.currentPlayer.next;
  }
  while(playerP != NULL){
    if(partyP.currentPlayer == NULL){
      partyP.currentPlayer = playerP;
      partyP.currentPlayer = partyP.currentPlayer.next;
      partyP.numPlayers ++;
    }
    playerP = playerP.next;

  }
}

// Set player state
void playerStart(playerT *playerP){
  playerT.stopF = 0;
  playerT.doneF = 0;
}
void playerStop(playerT *playerP){
  playerT.stopF = 1;
}
void playerDone(playerT *playerP){
  playerT.stopF = 1;
  playerT.doneF = 1;
}

// Play a given cards from a players hand
// Where exactly it is put is decided by player status and table contents
void playCard(playerT *playerP, int numCard, tableT *tableP){
}

// Put given card in player's hand
void takeCard(playerT *playerP, cardT *cardP){
  stackPush(playerP.hand, cardP);
}

// Pick up all cards from the table
void pickUpCards(playerT *playerP, tableT *tableP){
  for (int i = 0; i < tableP.att.size; i++){
    takeCard(playerP, tableP.att.cards);
    tableP.att.cards = tableP.att.cards.next;
  }
  for (int i = 0; i < tableP.def.size; i++){
    takeCard(playerP, tableP.def.cards);
    tableP.def.cards = tableP.def.cards.next;
  }
  //destory table
  //stack sort
}
