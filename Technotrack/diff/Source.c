#include<stdio.h>
#include<stdlib.h>
#include"./include/diff.h"

int main() {
    Node* rootTree = diffCtor("./input/configFile");
    Node* root = copyTree(rootTree, NULL);
    NodeDump(root);

    Node* diffNode = differentiation(root, NULL);
    assert(diffNode != NULL);
    NodeDump(diffNode);

    int trnfFlag = 0;
    Node* newNode = simplicationTree(diffNode, NULL, &trnfFlag);
    while(trnfFlag == 1) {
        trnfFlag = 0;
        newNode = simplicationTree(newNode, NULL, &trnfFlag);
    }
    NodeDump(newNode);
    
    makeTex(newNode, rootTree);

    TreeDtor(newNode);   
    TreeDtor(rootTree);
    TreeDtor(root);
    //TreeDtor(diffNode);
    return 0;
}
