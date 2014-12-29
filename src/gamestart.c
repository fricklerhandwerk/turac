#include <stdio.h>


//function to draw cards in any case - might move it to acitons 'cause it's not only needed at the game begin
int draw(int *player_hand, int *deck_int, int startnumber, int amount){
	int counter;
	for (counter = startnumber; counter < (counter + amount); ++counter)
	{
		if (counter < 36)
		{
			for (int i = 0; i < 36; ++i)
			{
				if (player_hand[i] == -1)
				{
					player_hand[i] == deck_int[counter]
					break; // if card is taken do not to insert it again
				}
			}
		}
	}

}


int first_draw(int *deck_int, int player_number, int *player_hand_1, int *player_hand_2, int *player_hand_3, int *player_hand_4) {
	
	int counter_player;
	int counter_card = 0;
	
	for (counter_card = 0; counter_card < 36; ++counter_card)
	{
		player_hand_1[counter_card] = -1
		player_hand_2[counter_card] = -1
		player_hand_3[counter_card] = -1
		player_hand_4[counter_card] = -1
	}


	//drawing
	for (counter_player = 0; counter_player < player_number; ++counter_player){
		if (counter_player == 0)
			draw(player_hand_1, deck_int, 0, 6);
		if (counter_player == 1)
			draw(player_hand_2, deck_int, 6, 6);
		if (counter_player == 2)
			draw(player_hand_3, deck_int, 12, 6);
		if (counter_player == 3)
			draw(player_hand_4, deck_int, 18, 6);

	}

	//returns currunt card number
	return counter_player * 6;
}