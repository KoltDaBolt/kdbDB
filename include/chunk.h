#ifndef CHUNK_H
#define CHUNK_H

#include <stdint.h>
#include "value.h"

typedef enum {
    OP_CLEAR,
    OP_CONSTANT,
    OP_RETURN
} OpCode;

typedef struct {
    int count;
    int capacity;
    uint8_t* code;
    ValueArray constants;
} Chunk;

void initChunk(Chunk*);
void freeChunk(Chunk*);
void writeChunk(Chunk*, uint8_t);
int addConstant(Chunk*, Value);

#ifdef DEBUG
void disassembleChunk(Chunk*, const char*);
int disassembleInstruction(Chunk*, int);
int simpleInstruction(const char*, int);
int constantInstruction(const char*, Chunk*, int);
#endif

#endif