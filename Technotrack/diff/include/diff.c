#include "diff.h"


Node* diffCtor(char* configName) {
    assert(configName != NULL);
    struct stat buf;
    lstat(configName, &buf);
    off_t fileSize = buf.st_size;
    
    FILE* inputFile = fopen(configName, "r");
    if(inputFile == NULL) {
        printf("Can't open configFile\n");
        exit(EXIT_FAILURE);
    }
    char* str = (char*)calloc(fileSize + 1, sizeof(char));
    size_t count = fread(str, sizeof(char), fileSize, inputFile);
    if(count != fileSize) printf("Error with fread\n");
    str[fileSize] = '\0'; 
    size_t ip = 0;
    Node* rootTree = makeTree(NULL, str, &ip);
    NodeDump(rootTree);
    free(str);
    fclose(inputFile);
    return rootTree;
}

Node* copyTree(Node* node, Node* parent) {
    if(node == NULL) return NULL;
    Node* newNode = NodeCtor(parent, node->type_, node->data_);
    newNode->left_ = copyTree(node->left_, newNode);
    newNode->right_ = copyTree(node->right_, newNode);
    return newNode;
}
