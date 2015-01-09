/* Implementation of basic card functions */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../inc/card.h"       

#define UP 1
#define DN 0

typedef struct cardT
{
  int rank;
  int suit;
  int face;
};


// Allocate memory for and create card with given rank and suit, face down
// Return memory size of card, 0 if error
int cardInit(cardT *cardP,char *rankString, char *suitString)
{
  int lenRank = strlen(rankString);
  int lenSuit = strlen(suitString);

  // allocate memory for rank and suit names
  cardP->rank = (char *) malloc(sizeof(char)*(lenRank+1));
  cardP->suit = (char *) malloc(sizeof(char)*(lenSuit+1));

  // handle allocation errors
  if (cardP->rank == NULL || cardP->suit == NULL)
  {
    return(0);
  }

  // write values
  strcpy(cardP->rank,rankString);
  strcpy(cardP->suit,suitString);
  cardP->face = DN;

  // compute memory size of card
  int memSize = lenRank + lenSuit + sizeof(int);

  return(memSize)
}

int cardDestroy(cardT *cardP);
{

  return(0);
}

// Set card facing
int cardFaceUp(cardT *card);
int cardFaceDown(cardT *card);

// Compare two cards by rank/suit
// Takes a list of ranks/suits from the rules file to determine rank/suit values
// Return values: a == b : 0; a > b : 1; a < b : -1;
int cardCompareRank(cardT *a, cardT *b, char **listRank);
int cardCompareSuit(cardT *a, cardT *b, char **listSuit);