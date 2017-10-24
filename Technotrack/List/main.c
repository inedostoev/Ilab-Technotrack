#include<stdio.h>
#include<stdlib.h>
#include"Node.h"

int main() {
    Node* root = NodeCtor(NULL, 1);
    AddNode(root, 2);
    AddNode(root, 3);
    AddNode(root, 4);
    NodeDump(root);
    root = DeleteNode(root, 1);
    NodeDump(root);
    root = DeleteNode(root, 5);
    NodeDump(root);
    ListDtor(root);
    return 0;
}

