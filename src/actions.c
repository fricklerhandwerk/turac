#include <stdio.h>
#include <time.h>
#include <stdlib.h>

struct cards
{
	int value;  // 0 = no card
	char color; //hearts = h, diamonds = d, clubs = s, spades = s, n = none
};

struct cards deck[36];

char trumpcolor = 'n';

int print_cards(struct cards *printcard) 
{
	int counter_i;
	printf("\n");

	for (counter_i = 0; counter_i < 36; ++counter_i)
	{
		printf("%d%c ", printcard[counter_i].value, printcard[counter_i].color);
	}
	return 0;
}


//function to draw cards in any case - it still exists in old verion at the gamestart.c

int draw(struct cards *player_hand, struct cards *deck_struct, int startnumber, int amount)
{
	int counter;
	for (counter = startnumber; counter < (counter + amount); ++counter)
	{
		if (counter < 36)
		{
			for (int i = 0; i < 36; ++i)
			{
				if (player_hand[i].value == 0)
				{
					player_hand[i] = deck_struct[counter];
					break; // if card is taken do not to insert it again
				}
			}
		}
	}
	return startnumber + amount;

}

int pop() {
	return 0;
}

int push(){
	return 0;
}


//shuffels the deck at the beginning of a game
//we take a 36 card deck for granted because it's the most used verion
//	http://en.wikipedia.org/wiki/Durak
//The represent all cards of six and higher (includeing aces) (colors: hearts, diamonds, clubs and Spades)
//	http://en.wikipedia.org/wiki/Suit_%28cards%29


int shuffle(){
	int deck_order[36], counter_i = 0, random_num = 0;
	for (int counter_i = 0; counter_i < 36; ++counter_i)
	{
		deck_order[counter_i] = -1;
	}
	counter_i = 0;
	while (counter_i < 36) {
		random_num = rand () % 36;
		if (deck_order[random_num] == -1){
			deck_order[random_num] = counter_i;
			counter_i ++;
		}
	}
	for (counter_i = 0; counter_i < 36; ++counter_i)
	{
		printf("%d ", deck_order[counter_i]);
	}
	for (counter_i = 0; counter_i < 36; ++counter_i)
	{
		if (deck_order[counter_i] == -1)
		{
			deck[counter_i].color = 'n';
			deck[counter_i].value = 0;
		}else if (deck_order[counter_i] > -1 && deck_order[counter_i] < 9)
		{
			deck[counter_i].color = 'h';
			deck[counter_i].value = (deck_order[counter_i] + 6);
		}else if (deck_order[counter_i] > 8 && deck_order[counter_i] < 18)
		{
			deck[counter_i].color = 'd';
			deck[counter_i].value = (deck_order[counter_i] - 3);
		}else if (deck_order[counter_i] > 17 && deck_order[counter_i] < 27)
		{
			deck[counter_i].color = 'c';
			deck[counter_i].value = (deck_order[counter_i] - 12);
		}else if (deck_order[counter_i] > 26 && deck_order[counter_i] < 36)
		{
			deck[counter_i].color = 's';
			deck[counter_i].value = (deck_order[counter_i] - 21);
		}else
		{
			return -1;
		}
	} 

/*	printf("\n");

	for (counter_i = 0; counter_i < 36; ++counter_i)
	{
		printf("%d%c ", deck[counter_i].value, deck[counter_i].color);
	}*/

	trumpcolor = deck[35].color;

	if (trumpcolor == 'h')
		printf("\nThe trumpcolor is hearts\n");
	else if (trumpcolor == 'd')
		printf("\nThe trumpcolor is diamonds\n");
	else if (trumpcolor == 'c')
		printf("\nThe trumpcolor is clubs\n");
	else if (trumpcolor == 's')
		printf("\nThe trumpcolor is spades\n");
	else
		printf("something somewhere went terribly wrong\n");



	return 0;

}

int sortRank(){
	return 0;
}

int sortSuit(struct cards *player_hand){
	struct cards temp;
	int outer_counter, inner_counter;
	for (outer_counter = 0; outer_counter < 36 - 1; ++outer_counter)
	{
		for (inner_counter = 0; inner_counter < 36 - 1 - outer_counter; ++inner_counter)
		{
			if (player_hand[inner_counter].color > player_hand[inner_counter + 1].color)
			{
				temp = player_hand[inner_counter];
				player_hand[inner_counter] = player_hand[inner_counter + 1];
				player_hand[inner_counter + 1] = temp;
			}
		}
	}

	return 0;
}


int main (){
	srand(time(NULL)); 
	shuffle();
	print_cards(deck);
	sortSuit(deck);
	print_cards(deck);
	return 0;
}