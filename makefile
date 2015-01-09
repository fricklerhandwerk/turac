CC = gcc
COMPILER_FLAGS = -std=c99 -Wall -Wextra -I$(INCLUDE_DIR) 

OBJS = turac.c


INCLUDE_DIR = src

_DEPS = card.c
DEPS = $(patsubst %,$(INCLUDE_DIR)/%,$(_DEPS))

OBJ_NAME = turac

all : $(OBJS)
	$(CC) $(OBJS) $(DEPS) $(COMPILER_FLAGS) -o $(OBJ_NAME)

run : $(OBJS)
	$(CC) $(OBJS) $(DEPS) $(COMPILER_FLAGS) -o $(OBJ_NAME) && ./$(OBJ_NAME)
