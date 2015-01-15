/* Implementation of player functions */

#include <stdlib.h>

#include "../inc/card.h"


// Allocate memory for player with empty hand
playerT *playerNew(char *name, *anfang){

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
  player->currentF = 0;
  player->stopF = 0;
  player->doneF = 0;
  player->next = NULL;

  return(player);
}

// Free member and player memory
void playerDestroy(playerT **playerP);

// Add player to party
void playerAdd(playerT *partyP, playerT *playerP);

// Set player state
void playerStart(playerT *playerP);
void playerStop(playerT *playerP);
void playerDone(playerT *playerP);

// Play a given cards from a players hand
// Where exactly it is put is decided by player status and table contents
void playCard(playerT *playerP, int numCard, tableT *tableP);

// Put given card in player's hand
void takeCard(playerT *playerP, cardT *cardP);

// Pick up all cards from the table
void pickUpCards(playerT *playerP, tableT *tableP);
