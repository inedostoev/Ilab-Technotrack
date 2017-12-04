#ifndef DIFF_H_INCLUDED
#define DIFF_H_INCLUDED

#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<unistd.h>
#include"./Node/Node.h"
#include<ctype.h>
#include<string.h>

Node* diffCtor(char* configFile);
Node* copyTree(Node* node, Node* parent);

Node* makeTree(Node* parent, char* str, size_t *ip);
Node* getAddSub(Node* parent, char *str, size_t *ip);
Node* getMulDiv(Node* parent, char *str, size_t *ip);
Node* getPower(Node* parent, char *str, size_t *ip);
Node* getBracketsFunc(Node* parent, char* str, size_t *ip);
Node* makeId(Node* parent, char* str, size_t *ip);
Node* getNumber(Node* parent, char* str, size_t *ip);

Node* differentiation(Node* node, Node* parent); 
Node* simplicationTree(Node* diffNode, Node* parent, int *flag); 

int makeTex(Node* root, Node* firstNode);
int makeTexNodeDump(Node* node, FILE* stream);
Priority getPriority(Node* node);

#endif
