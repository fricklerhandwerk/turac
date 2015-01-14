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
	- [ ] Player
	- [ ] playerInit
	- [ ] playerDestroy
	- [ ] playerStart
	- [ ] playerStop
	- [ ] playerDone
	- [ ] playCard
	- [ ] takeCard
	- [ ] pickUpCards
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
	- [ ] Table
		- [x] table struct // two card stacks and a mapping array to know which card beats which
		- [ ] tableInit
		- [ ] tableDestroy
		- [ ] tableFull
		- [ ] tableBeaten
		- [ ] tableEmpty
	- [x] Clumsy makefile (it's something)
	- [ ] Commandline view
		- [x] Header file
		- [x] viewCard
		- [x] viewCardLn
		- [x] viewHand


## Pile of stuff
- [ ] Makefile for handling modules (when set up, add your own compile option)
- [ ] Party
	- [ ] partyInit
	- [ ] partyDestroy
	- [ ] partyAddPlayer
	- [ ] partyRemovePlayer
	- [ ] partyNextPlayer
- [ ] Commandline view
	- [ ] viewDeck // maybe with number of cards inside
	- [ ] viewTable // use table info to get card alignment
- [ ] Commandline control
	- [ ] Header file
	- [ ] moveCursor // cursor to choose card from hand
	- [ ] putCard // puts card on table
	- [ ] setDone // take cards or stop attacking
- [ ] Game loop
	- [ ] Header file
- [ ] Bot
	- [ ]
