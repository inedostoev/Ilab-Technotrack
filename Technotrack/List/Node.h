#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

enum NodeErrors {
    NODE_NULL_PTR = -1
};

typedef double Data_t;

typedef struct Node {
    Data_t      data_;
    Node*       parent_;
    Node*       next_;
} Node;

struct Node*    NodeCtor(Node* parent, Data_t data);
int             ListDtor(Node* root);
int             NodeDtor(Node* node);
Node*           AddNode(Node* root, Data_t data);
Node*           DeleteNodeOnAdress(Node* node);
Node*           DeleteNode(Node* root, Data_t data);
Node*           DeleteFirstNode(Node* root);
int             NodeDump(Node* root);
int             dotNodeDump(Node *root, FILE* stream);

#endif
