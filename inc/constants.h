#ifndef CONST_H
#define CONST_H

/* GAME CONSTANTS */

#define HAND_SIZE 6

// Lists are terminated with NULL to have "portable" bound checking
// according to this post: http://stackoverflow.com/a/13583763

// Suits used
enum SUIT
{
	HEARTS,
	TILES,
	CLUBS,
	SPADES,
};

//const char *listSuit[] = {"Hearts","Tiles","Clubs","Spades",NULL};

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
const char *listSuit[] = {KRED"\u2665"KNRM,KRED"\u2666"KNRM,"\u2663","\u2660",NULL};

// Ranks used
enum RANK
{
	SIX,
	SEVEN,
	EIGHT,
	NINE,
	TEN,
	JACK,
	QUEEN,
	KING,
	ACE,
};

const char *listRank[] = {"6","7","8","9","10","J","Q","K","A",NULL};

// Card faces
enum FACE
{
	DOWN,
	UP
};

const char *listFace[] = {"down","up",NULL};

#endif // CONST_H
