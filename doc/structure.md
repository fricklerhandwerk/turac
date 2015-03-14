* Engine/Library
	* cards.h
		* card data type with numeric information on a single card
			* rank, suit, facing
		* very basic card functions
			* create, destroy, set facing, compare by rank/suit
	* stack.h
		* datatype for stack of cards, implemented as array
		* usual stack functions
			* create, destroy, pop, push, full, empty
		* card game specific functions
			* shuffle, sort by rank/suit
* Game rules
	* constants.h	
		* game invariants like hand size
		* lists of ranks and suits and their ordering
	* rules.h
		* game-specific functions
			* create deck, hand cards
			* check if specific card actions are allowed
			* check round/game status
	* player.h
		* player data type
			* hand, player status
		* player functions
			* create, destroy
			* changes of player status
			* info on player status
			* simple player actions
	* party.h
		* party data type
			* linked list for players
			* number of players
			* current attacking and defending player
		* party functions
			* create, destroy
			* add player
			* next player
	* table.h
		* table data type
			* attack and defend stack
			* mapping of defending cards to attacking cards
		* table functions
			* put cards on attack/defend stack
			* tell if table is full/beaten
			* clean table (put all cards somewhere)
* Command line view
	* cmd_view.h
		* view game objects
			* card
			* hand
			* deck
			* waste stack
			* table
			* player
			* whole game
* Computer opponent
	* bot.h
		* decide which role to take (attack or defend)
		* attack playing lowest possible card or stop
		* defend playing lowest possible card or take cards
* Game control (main function)
	* game.c
		*	initialize all game objects
		*	start game and control the game loop
		*	output game result
* Command line control


Not implemented:
* SDL view
	* Table
	* Hand
* SDL mouse control
	* [Ideas for SDL view/control module] (https://github.com/ricoz/drac)

[General hints for implementation] (http://www.bandgap.cs.rice.edu/workshops/oopd/sigcse2006/WebDocs/CardGame/assignment.html)  
[Suggestions for library functions] (http://www.brainjar.com/js/cards/)  
[Durak German Wikipedia article] (http://de.wikipedia.org/wiki/Durak_%28Kartenspiel%29)

