/* Implementation of player functions */

#include <stdlib.h>

#include "../inc/player.h"

// Allocate memory for player with empty hand
playerT *playerNew(char *name, int sizeHand)
{
  // don't accept illegal values
  if (name == NULL || sizeHand < 0)
  {
    return(NULL);
  }

  // allocate memory for array of player
  playerT *playerP;
  playerP = malloc(sizeof(playerT));

  // allocate stack for player hand
  playerP->hand = stackInit(sizeHand);

  // handle allocation errors
  if (playerP == NULL || playerP->hand == NULL)
  {
    return(NULL);
  }

  // write values
  playerP->name = name;
  playerP->roundF = 0 ;
  playerP->gameF = 0;
  playerP->next = NULL;

  return(playerP);
}

// Free member and player memory
void playerDestroy(playerT **playerP)
{
  // destroy name string
  // NOTE: it's not intended to be used anywhere else
  free((*playerP)->name);
  (*playerP)->name = NULL;

  // destroy hand
  stackDestroy(&(*playerP)->hand);

  (*playerP)->next = NULL;

  free(*playerP);
  *playerP = NULL;
}

/* your intface was deprecated, this is a party.h function
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
*/

// Set player state
void playerStartRound(playerT *playerP)
{
  playerP->roundF = TRUE;
}

void playerEndRound(playerT *playerP)
{
  playerP->roundF = FALSE;
}

void playerStartGame(playerT *playerP)
{
  playerP->gameF = TRUE;
}

void playerEndGame(playerT *playerP)
{
  playerP->gameF = FALSE;
}

int playerInRound(playerT *playerP)
{
  return playerP->roundF;
}

int playerInGame(playerT *playerP)
{
  return playerP->gameF;
}

int playerHandSize(playerT *playerP)
{
  return stackSize(playerP->hand);
}

// Play a given cards from a players hand
// Where exactly it is put is decided by player status and table contents
cardT *playCard(playerT *playerP, int numCard)
{
  // refuse to operate on illegal values
  if (playerP == NULL || numCard < 0 || numCard > stackSize(playerP->hand)-1)
  {
    return(NULL);
  }
  // get the needed hand on top of the stack
  stackSwap(playerP->hand,numCard);
  // return top of stack
  return (stackPop(playerP->hand));
}

// Put given card in player's hand
int takeCard(playerT *playerP, cardT *cardP)
{
  return stackPush(playerP->hand,cardP);
}

/* this is now done by the table, which throws out its contents on some stack
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
*/
