# kdbDB
A personal project making my own SQLite-like RDBMS from scratch.

## Necessary Installs
- GCC
- Make
- Valgrind (optional tool for development, linux only)

## Build & Run Instructions
| Command                | Description                                          |
|------------------------|------------------------------------------------------|
| `make`                 | Builds and runs the release version                  |
| `make debug`           | Builds and runs the debug version                    |
| `make valgrind`        | Builds and runs the release version under Valgrind   |
| `make debugvalgrind`   | Builds and runs the debug version under Valgrind     |


After building, the compiled binary will be located in the `bin/` directory.
