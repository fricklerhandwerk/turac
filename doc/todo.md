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
	- [ ] Rules
		- [ ] deckCreate
		- [ ] handCards
		- [ ] isTrump
		- [ ] cardBeats
		- [ ] cardFits
		- [ ] roundOver // tells us when to switch player roles
		- [ ] gameOver
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
		- [x] table struct // two card stacks and a mapping array to know which card beats which
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
	- [ ] Party tests
	- [ ] Player tests
	- [x] Clumsy makefile (it's something)
	- [x] Commandline view
		- [x] Header file
		- [x] viewCard
		- [x] viewCardLn
		- [x] viewHandRow
		- [x] viewHandCol
		- [x] viewDeck
		- [x] viewTableRow
		- [x] viewTableCol



## Pile of stuff
- [ ] Makefile for handling modules (when set up, add your own compile option)
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
