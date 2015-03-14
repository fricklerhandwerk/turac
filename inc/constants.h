#ifndef CONST_H
#define CONST_H

/* GAME CONSTANTS */

#define HAND_SIZE 6

// Lists are terminated with NULL to have "portable" bound checking
// according to this post: http://stackoverflow.com/a/13583763

// Suits used
#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
const char *listSuit[] = {KRED"\u2665"KNRM,KRED"\u2666"KNRM,"\u2663","\u2660",0};

// Ranks used
const char *listRank[] = {"6","7","8","9","10","J","Q","K","A",0};

// Card faces
#define DOWN 0
#define UP 1

#endif // CONST_H
