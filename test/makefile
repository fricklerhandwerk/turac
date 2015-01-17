CC = gcc

INCLUDE_DIR = ../inc
SOURCE_DIR = ../src
BIN_DIR = ../bin

COMPILER_FLAGS = -I$(INCLUDE_DIR) -std=c99 -Wall -Wextra 

# dependencies
_SRC = card.c stack.c player.c party.c table.c cmd_view.c
SRC = $(addprefix $(SOURCE_DIR)/,$(_SRC))

cardTest: $(SRC) cardTest.c
	gcc -o $(BIN_DIR)/$@ $^ $(COMPILER_FLAGS) && $(BIN_DIR)/$@

printTest: $(SRC) printTest.c
	gcc -o $(BIN_DIR)/$@ $^ $(COMPILER_FLAGS) && $(BIN_DIR)/$@
	
stackTest: $(SRC) stackTest.c
	gcc -o $(BIN_DIR)/$@ $^ $(COMPILER_FLAGS) && $(BIN_DIR)/$@

tableTest: $(SRC) tableTest.c
	gcc -o $(BIN_DIR)/$@ $^ $(COMPILER_FLAGS) && $(BIN_DIR)/$@

playerTest: $(SRC) playerTest.c
	gcc -o $(BIN_DIR)/$@ $^ $(COMPILER_FLAGS) && $(BIN_DIR)/$@

partyTest: $(SRC) partyTest.c
	gcc -o $(BIN_DIR)/$@ $^ $(COMPILER_FLAGS) && $(BIN_DIR)/$@