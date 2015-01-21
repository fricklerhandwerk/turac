void input()//maybe but active players in here?
{
	char input_c;
	//setting input to raw input
	system ("/bin/stty raw");

	while((input_c=getchar())!= '.') {
		/* type a period to break out of the loop, since CTRL-D won't work raw */

		if(input_c == 'w'){
			//player 1 selcet up
		} else if (input_c == 's'){
			//player 1 select down
		} else if (input_c == 'o'){
			//player 2 select up
		} else if (input_c == 'l'){
			//player 2 select down
		} else if (input_c == 'e'){
			//player 1 play selected card
		} else if (input_c == 'd'){
			//player 1 stop
		} else if (input_c == 'i'){
			//player 2 play selected card
		} else if (input_c == 'k'){
			//player 2 stop
		} else {
			printf("\n--------------------\nBitte gebe etwas anderes ein!\n------------------\n");
		}

	}


	//setting input to cooked input
	system ("/bin/stty cooked");
}
