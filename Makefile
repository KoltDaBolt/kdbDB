TARGET = bin/kdbDB
SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c, obj/%.o, $(SRC))
GCC = gcc -Wall -Werror
VALGRIND = valgrind --leak-check=full

run: clean default
	./$(TARGET)

valgrind: clean default
	$(VALGRIND) ./$(TARGET)

default: $(TARGET)

$(TARGET): $(OBJ)
	$(GCC) -o $@ $?

obj/%.o: src/%.c
	$(GCC) -c $< -o $@ -Iinclude

clean:
	rm -f obj/*.o bin/*
	touch obj/.gitkeep bin/.gitkeep

# $< = a single file given as a target
# $@ = the target of a rule
# $? = a list of all input files given as a target