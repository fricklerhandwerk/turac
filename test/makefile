CC = gcc

INCLUDE_DIR = ../inc
SOURCE_DIR = ../src
BIN_DIR = ../bin

COMPILER_FLAGS = -I$(INCLUDE_DIR) -std=c99 -Wall -Wextra 

# dependencies
_SRC = card.c stack.c cmd_view.c
SRC = $(addprefix $(SOURCE_DIR)/,$(_SRC))

cardTest: $(SRC) cardTestc
	gcc -o $(BIN_DIR)/$@ $^ $(COMPILER_FLAGS)

printTest: $(SRC) printTest.c
	gcc -o $(BIN_DIR)/$@ $^ $(COMPILER_FLAGS)