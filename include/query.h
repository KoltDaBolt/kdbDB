#ifndef QUERY_H
#define QUERY_H

typedef enum {
    QUERY_TYPE_CLEAR,
    QUERY_TYPE_LIST_DATABASE,
    QUERY_TYPE_CREATE_DATABASE
} QueryType;

typedef struct {
    const char* dbname;
} CreateDatabase;

typedef struct {
    QueryType type;
    union {
        CreateDatabase createDbQuery;
    } data;
} Query;

#endif