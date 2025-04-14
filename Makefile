# -=-=-=-=-= VARIABLES =-=-=-=-=-

RELEASE_TARGET = bin/kdbDB
DEBUG_TARGET = bin/kdbDB-debug
SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c, obj/%.o, $(SRC))

CC = gcc
CFLAGS_COMMON = -Wall -Werror -Iinclude
CFLAGS_DEBUG = $(CFLAGS_COMMON) -g -O0 -DDEBUG
CFLAGS_RELEASE = $(CFLAGS_COMMON) -O2

VALGRIND = valgrind --leak-check=full

# -=-=-=-=-= RUN TARGETS =-=-=-=-=-

default: clean RELEASE
	./$(RELEASE_TARGET)

debug: clean DEBUG
	./$(DEBUG_TARGET)

valgrind: clean RELEASE
	$(VALGRIND) ./$(RELEASE_TARGET)

debugvalgrind: clean DEBUG
	$(VALGRIND) ./$(DEBUG_TARGET)

clean:
	rm -f obj/*.o bin/*
	touch obj/.gitkeep bin/.gitkeep

# -=-=-=-=-= BUILD TARGETS =-=-=-=-=-

RELEASE: CFLAGS = $(CFLAGS_RELEASE)
RELEASE: $(RELEASE_TARGET)

DEBUG: CFLAGS = $(CFLAGS_DEBUG)
DEBUG: $(DEBUG_TARGET)

$(RELEASE_TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

$(DEBUG_TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

obj/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# $< = a single file given as a target
# $@ = the target of a rule
# $? = a list of all input files given as a target