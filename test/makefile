CC = gcc
COMPILER_FLAGS = -std=c99 -Wall -Wextra -I$(INCLUDE_DIR) 

INCLUDE_DIR = ../inc
OBJECT_DIR  = ../obj

OBJS = cardTest.o


_DEPS = card.h
DEPS  = $(patsubst %,$(INCLUDE_DIR)/%,$(_DEPS))


# compile all dependencies separately
$(OBJECT_DIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

cardTest: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)

clean:
	rm -f $(OBJECT_DIR)/*.o *~ core $(INCLUDE_DIR)/*~ 