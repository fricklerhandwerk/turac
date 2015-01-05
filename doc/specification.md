Game content
============

The human player has a simple computer opponent. The game is initialized by giving cards to both players and determining the trump suit and the player who starts attacking.  
Each round, the player has either to attack or to defend by dragging cards from his hand onto the table with the mouse. Only actions according to the game rules are carried out. The opponent attacks, defends or takes cards based on a set of simple decision rules.  
If the attacker is done, if there are six cards on the table and all of them are beaten or if the defender has taken the cards, all beaten cards are discarded and the next round starts. Then, after each round players with less than six cards on their hands are given cards from the deck until the deck is empty.  
The game ends when the deck is empty and one of the players has no more cards on his hands.

Key features
============
0. Strictly modular design and well-documented code
0. Card game engine/library with actions on cards and decks
0. Implementation of traditional game rules
0. Command line game control (though without fancy input validation)
0. Command line view
0. Two players at one computer
0. Simple computer opponent

Wishlist
==============
* Graphical view using SDL
* Drag&Drop game control using SDL
* Choice of input and view model at compile time
* Additional rule variants
* Multiple games in one session
* Additional game mode: two players on one computer
* More than two players
* Multiple computer opponent strengths to choose from
* Rule/player/AI choice as runtime arguments
* Rule/player/AI choice in game
* Network code
