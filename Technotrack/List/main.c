#include<stdio.h>
#include<stdlib.h>
#include"Node.h"

int main() {
    Node* root = NodeCtor(NULL, 1);
    List* list = ListCtor(root);
    
    Node* tmp = addLastNode(list, 2);
    Node* t = addLastNode(list, 3);
    addFirstNode(list, 0);
    addNodeOnAdress(list, tmp, 2.5);
    
    NodeDump(list->firstNode_);
    
    DeleteNodeOnAdress(list, t);
    NodeDump(list->firstNode_);
    
    ListDtor(list->firstNode_);
    DeleteList(list);
    return 0;
}

