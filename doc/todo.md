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
- [ ] Implement more stuff (in any barely working way)
	- [ ] Players
	- [ ] Rules
	- [ ] Cmd view
	- [ ] Cmd control
	- [ ] Game loop
	- [ ] Bot
  

- Vincent
	- [x] Player
		- [x] playerInit
		- [x] playerDestroy
		- [x] playerStart
		- [x] playerStop
		- [x] playerDone
		- [x] playCard
		- [x] takeCard
- Tom
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
		- [ ] gameStart
		- [x] gameOver
	- [ ] Rules tests



## Pile of stuff
- [ ] Party
	- [ ] partyRemovePlayer // only necessary for multiplayer
- [ ] Commandline view
- [ ] Commandline control
	- [ ] Header file
	- [ ] moveCursor // cursor to choose card from hand
	- [ ] putCard // puts card on table
	- [ ] setDone // take cards or stop attacking
- [ ] Game loop
	- [ ] Header file
- [ ] Bot
	- [ ]
