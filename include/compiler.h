#ifndef COMPILER_H
#define COMPILER_H

#include "query.h"
#include "chunk.h"

typedef enum {
    COMPILER_STATUS_OK,
    COMPILER_STATUS_ERROR
} CompilerStatus;

void emitByte(uint8_t, Chunk*);
void emitBytes(uint8_t, uint8_t, Chunk*);
void emitReturn(Chunk*);
CompilerStatus compile(Query, Chunk*);

#endif