#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int pop() {
	return 0;
}

int push();


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

	return 0;

}

int sortRank(){
	return 0;
}

int sortSuit(){
	return 0;
}
