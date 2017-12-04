#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

enum dataType {
    NUM,
    VAR,
    OPER,
    FUNC,
    ERROR
};

enum operType {
    OPER_ADD,
    OPER_SUB,
    OPER_MUL,
    OPER_DIV,
    OPER_POW
};

enum funcType {
    FUNC_LN
};

enum Priority {
    LOW_PRIOR,
    ADDSUB_PRIOR,
    MULDIV_PRIOR,
    EXP_PRIOR,
};

typedef struct Node {
    int         data_;
    dataType    type_;
    Node*       parent_;
    Node*       left_;
    Node*       right_;
} Node;

struct Node*    NodeCtor(Node* parent, dataType type, int data);
int             TreeDtor(Node* root);
int             NodeDump(Node* root);
int             dotNodeDump(Node *root, FILE* stream);


#endif
