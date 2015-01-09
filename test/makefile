CC = gcc

INCLUDE_DIR = ../inc
SOURCE_DIR = ../src
BIN_DIR = ../bin

COMPILER_FLAGS = -I$(INCLUDE_DIR) -std=c99 -Wall -Wextra 

# local
LOC = cardTest.c

# dependencies
_SRC = card.c
SRC = $(addprefix $(SOURCE_DIR)/,$(_SRC))

cardTest: $(LOC) $(SRC)
	gcc -o $(BIN_DIR)/$@ $^ $(COMPILER_FLAGS)