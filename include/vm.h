#ifndef VM_H
#define VH_H

#include "chunk.h"

typedef enum {
    VM_OK,
    VM_RUNTIME_ERROR
} VMStatus;

typedef struct {
    Chunk* chunk;
    uint8_t* ip;
} VM;

// void initVM();
// void freeVM();
uint8_t readByte();
VMStatus run(Chunk*);
VMStatus execute();

#endif