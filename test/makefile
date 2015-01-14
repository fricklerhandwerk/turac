CC = gcc

INCLUDE_DIR = ../inc
SOURCE_DIR = ../src
BIN_DIR = ../bin

COMPILER_FLAGS = -I$(INCLUDE_DIR) -std=c99 -Wall -Wextra 

# dependencies
_SRC = card.c stack.c table.c cmd_view.c
SRC = $(addprefix $(SOURCE_DIR)/,$(_SRC))

cardTest: $(SRC) cardTest.c
	gcc -o $(BIN_DIR)/$@ $^ $(COMPILER_FLAGS)

printTest: $(SRC) printTest.c
	gcc -o $(BIN_DIR)/$@ $^ $(COMPILER_FLAGS)
	
stackTest: $(SRC) stackTest.c
	gcc -o $(BIN_DIR)/$@ $^ $(COMPILER_FLAGS)

tableTest: $(SRC) tableTest.c
	gcc -o $(BIN_DIR)/$@ $^ $(COMPILER_FLAGS)