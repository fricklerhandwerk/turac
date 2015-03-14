#TODO

##Week 1
- [x] Write specification
- [x] Define ca. 8 key features
- [x] Define program structure
- [x] Define key functions and their signatures
- [x] Define most important data types
- [x] Define coding conventions
- [x] Agree on definitions

##Week 2
- [x] Split tasks
- [x] Implement some stuff

##Week 3
- [x] Implement more stuff (in any barely working way)
	- [x] Players
	- [x] Rules
	- [x] Cmd view
	- [x] Bot
	- [x] Botmatch

##Week 4
- [x] Make it work
	- [x] Cmd control
	- [x] Cmd view with control
	- [x] Game loop
	- [x] Bugfixes


##Wishlist
- [ ] There is currently no point where players leave the game (`gameF` flag unset). On the other hand, the player's game state is checked in the `nextPlayer` function. Players could be put out of game by checking after every handing cards whether the deck is empty and they have no cards on hand. Then `gameOver` could be reduced to counting the number of active players.
- [ ] Move playerSortHand() to an appropriate place (currently in cmd_input)
- [ ] Encapsule game start (game.c) // currently expanded before game loop
- [ ] Ask and start new game after finished (game.c)
- [ ] Set attacker and defender in next games according to who lost before (rules.h)
- [ ] Re-Implement stacks/lists using glib to have less maintenance (evil amout of work)

- Vincent
	- [x] Player
		- [x] playerInit
		- [x] playerDestroy
		- [x] playerStart
		- [x] playerStop
		- [x] playerDone
		- [x] playCard
		- [x] takeCard
	- [x] Commandline control
		- [x] Header file
		- [x] Move cursor
		- [x] Put card
		- [x] Set Done
		- [x] Quit
- Tom
 - [x] Cursor view
 - [x] Fix 
- Valentin
	- [x] Party interface
	- [x] Player interface
	- [x] Card
		- [x] cardNew
		- [x] cardFaceUp
		- [x] cardFaceDown
		- [x] cardCompareRank
		- [x] cardCompareSuit
	- [x] Card tests
	- [x] Makefile
	- [x] Commandline view
		- [x] Header file
		- [x] viewCard
		- [x] viewCardLn
		- [x] viewHandRow
		- [x] viewHandCol
		- [x] viewDeck
		- [x] viewTableRow
		- [x] viewTableCol
	- [x] Stack
		- [x] stackInit
		- [x] stackDestroy
		- [x] stackPush
		- [x] stackPop
		- [x] stackNumElem
		- [x] stackEmpty
		- [x] stackFull
		- [x] stackShuffle
		- [x] stackSortSuit
		- [x] stackSortRank
	- [x] Stack tests
	- [x] Table
		- [x] table struct
		- [x] tableInit
		- [x] tableDestroy
		- [x] tablePutAtt
		- [x] tablePutDef
		- [x] tableFull
		- [x] tableBeaten
		- [x] tableClean
	- [x] Table tests
	- [x] Party
		- [x] partyInit
		- [x] partyDestroy
		- [x] partyAddPlayer
		- [x] partyNextPlayer
	- [x] Player tests
	- [x] Party tests
	- [ ] Rules
		- [x] deckCreate
		- [x] handCards
		- [x] isTrump
		- [x] cardBeats
		- [x] cardFits
		- [x] attackStopped // all attackers stopped adding cards
		- [x] roundOver
		- [x] gameOver
	- [x] Rules tests
	- [x] Game loop
	 - [x] Cases for players/bots
	 - [x] Hand action to next player/bot
	- [x] Bot
		- [x] botSortHand
		- [x] botAttack
		- [x] botDefend
	- [x] Keep cards in order after playing
	- [x] Get number of human players and their names as program argument
	- [x] Set cursor to valid position after playing, not before
	- [x] Let cardBeats also check if an attacking card has already been beaten by some other card
	- [x] Remove card face member and all functions using it. It is actually useless. At least in this game we can manage the facing in view logic elegantly and save work in game mechanics, since at no point is facing game-state-dependently mixed in a given collection of cards or in any way influencing the game state internally.

