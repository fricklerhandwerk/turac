* Engine/Library
	* cards.h
		* card data type with numeric information on a single card
			* rank, suit, facing
		* very basic card functions
			* create, set facing, compare by rank/suit
	* stack.h
		* datatype for stack of cards, implemented as array
		* usual stack functions
			* create, destroy, pop, push, full, empty
		* card game specific functions
			* shuffle, sort by rank/suit
* Game rules
	* rules.h
		* game constants
			* lists of ranks and suits and their ordering
			* hand size
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
			* player actions
* Game control
	* Game
	* Round
	* Move
* Command line view
* Command line control
* SDL view
	* Table
	* Hand
* SDL mouse control
	* [Ideas for SDL view/control module] (https://github.com/ricoz/drac)
* Computer opponent


[General hints for implementation] (http://www.bandgap.cs.rice.edu/workshops/oopd/sigcse2006/WebDocs/CardGame/assignment.html)
[Suggestions for library functions] (http://www.brainjar.com/js/cards/)
[Durak German Wikipedia article] (http://de.wikipedia.org/wiki/Durak_%28Kartenspiel%29)

