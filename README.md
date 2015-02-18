#turac

C implementation of the traditional russian card game Durak (Дурак) as an exercise project at TUHH.
http://en.wikipedia.org/wiki/Durak

Since it is just a simple demonstration, it runs in command line and you see both players' hands. The game also has a simple computer opponent.

#Compiling and running

Prerequisites: `git`,`make`,`gcc`

1. Clone the source into a `<directory>` of your choice. In a terminal, type or paste:
```
$ git clone https://github.com/frickler01/turac.git <directory>
```

2. Change into `<directory>` and run `make`:
```
$ cd <directory>
$ make turac
```

This will create a `bin` directory, where the executable is located. 

3. Start the game by providing the desired `<number>` of human players (0-2) and their `names` separated by blanks:

```
$ bin/turac <number> [<names>]
```

#Controls

##Player 1
	Cursor left: `A`
	Cursor right: `D`
	Play card: `W`
	End round: `E` (take cards or stop attacking)
	Sort hand: `Q` (sorts by rank, trumps sorted separately)

## Player 2
	Cursor left: `J`
	Cursor right: `L`
	Play card: `I`
	End round: `O`
	Sort hand: `U`

	Quit game: `.`

You can change the controls by editing the file `inc/cmd_input.h`.

#Playing

The attacking and defending players are indicated by a colored `(A)` or `(D)`.
Just move your cursor to select a card and put it on the table.  
The game does a lot of stuff for you automatically. It will deny illegal moves (nothing will happen), end your round if there is nothing else to do - like if you can't beat the given table or if you can't add anything - and proceed to the next round accordingly.  
If a player has ended its round, a `*` appears next to its name.
