#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED
#include "Node.h"
#include "Akinator.h"

Node*   buildTree(char* buffer, size_t *counter, Node* Darth_Vader);
int     writeFile(FILE *outputFile, Node *nodePointer);
Node*   copyTree(Node* node, Node* parent);

#endif
