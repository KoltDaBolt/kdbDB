#include "compiler.h"

void emitByte(uint8_t byte, Chunk* chunk) {
    writeChunk(chunk, byte);
}

void emitBytes(uint8_t byte1, uint8_t byte2, Chunk* chunk) {
    emitByte(byte1, chunk);
    emitByte(byte2, chunk);
}

void emitReturn(Chunk* chunk) {
    emitByte(OP_RETURN, chunk);
}

CompilerStatus compile(Query query, Chunk* chunk) {
    switch (query.type) {
        case QUERY_TYPE_CLEAR:
            emitByte(OP_CLEAR, chunk);
            emitReturn(chunk);
            break;
        default:
            return COMPILER_STATUS_ERROR;
    }

    return COMPILER_STATUS_OK;
}