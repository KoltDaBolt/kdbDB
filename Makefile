TARGET = bin/kdbDB
SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c, obj/%.o, $(SRC))
VALGRIND = valgrind --leak-check=full

run: clean default
	./$(TARGET)

valgrind: clean default
	$(VALGRIND) ./$(TARGET)

default: $(TARGET)

$(TARGET): $(OBJ)
	gcc -o $@ $?

obj/%.o: src/%.c
	gcc -c $< -o $@ -Iinclude

clean:
	rm -f obj/*.o
	rm -f bin/*

# $< = a single file given as a target
# $@ = the target of a rule
# $? = a list of all input files given as a target