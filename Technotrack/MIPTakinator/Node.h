#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

const int NODE_NULL_PTR = -1;

enum dumpMod {
    USER,
    PROGER,
};

typedef struct Node {
    char*       data_;
    Node*       parent_;
    Node*       left_;
    Node*       right_;
} Node;

struct Node*    NodeCtor(Node* parent, char* data);
int             ListDtor(Node* root);
Node*           AddNode(Node* root, char* data);
int             NodeDump(Node* root, dumpMod mode);
int             dotUserDump(Node *root, FILE* stream);
int             dotNodeDump(Node *root, FILE* stream);

#endif
