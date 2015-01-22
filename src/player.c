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
  // get the needed card on top of the stack
  stackMoveTop(playerP->hand,numCard);
  // return top of stack
  return (stackPop(playerP->hand));
}

// Put given card in player's hand
int takeCard(playerT *playerP, cardT *cardP)
{
  return stackPush(playerP->hand,cardP);
}