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

typedef struct List {
    Node*       firstNode_;
    Node*       lastNode_;
} List;

struct List*    ListCtor(Node* firstNode);
int             DeleteList(List* list);

struct Node*    NodeCtor(Node* parent, Data_t data);
int             ListDtor(Node* root);
int             NodeDtor(Node* node);

Node* addFirstNode(List* list, Data_t data);
Node* addLastNode(List* list, Data_t data);
Node* addNodeOnAdress(List* list, Node* adress, Data_t data);

Node*           AddNode(Node* root, Data_t data);
Node*           DeleteNodeOnAdress(List* list, Node* node);
Node*           DeleteFirstNode(List* list);
int             NodeDump(Node* root);
int             dotNodeDump(Node *root, FILE* stream);

#endif
