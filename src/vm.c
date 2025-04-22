#include "vm.h"
#include "print.h"

VM vm;

// void initVM();

// void freeVM();

uint8_t readByte() {
    return *vm.ip++;
}

VMStatus run(Chunk* chunk) {
    vm.chunk = chunk;
    vm.ip = chunk->code;
    return execute();
}

VMStatus execute() {
    uint8_t instruction;
    while (true) {
        switch (instruction = readByte()) {
            case OP_CLEAR: {
                clearScreen();
                break;
            }
            case OP_RETURN: {
                return VM_OK;
            }
            default:
                return VM_RUNTIME_ERROR;
        }
    }
}