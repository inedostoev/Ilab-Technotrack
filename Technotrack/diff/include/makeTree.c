#include "diff.h"

Node* makeTree(Node* parent, char *str, size_t *ip) {
    Node* rootTree = getAddSub(parent, str, ip);
    //assert(str[*ip] == '\0');
    return rootTree;
}

#define MAKENODE(OPERTYPE);                                     \
    newNode = NodeCtor(parent, OPER, OPERTYPE);                 \
    leftNode->parent_ = newNode;                                \
    rightNode->parent_ = newNode;                               \
    newNode->left_ = leftNode;                                  \
    newNode->right_ = rightNode; 


Node* getAddSub(Node* parent, char *str, size_t *ip) {
    Node* newNode = getMulDiv(parent, str, ip);
    while(str[*ip] == '+' || str[*ip] == '-') {
        int op = str[*ip];
        (*ip)++;
        Node* rightNode = getMulDiv(parent, str, ip);
        Node* leftNode = newNode;
        if(op == '+') { MAKENODE(OPER_ADD); }
        else { MAKENODE(OPER_SUB); }
    }
    return newNode;
}

Node* getMulDiv(Node* parent, char *str, size_t *ip) {
    Node* newNode = getPower(parent, str, ip);
    while(str[*ip] == '*' || str[*ip] == '/') {
        int op = str[*ip];
        (*ip)++;
        Node* rightNode = getPower(parent, str, ip);
        Node* leftNode = newNode;
        if(op == '*') { MAKENODE(OPER_MUL); }
        else { MAKENODE(OPER_DIV); }
    }
    return newNode;
}

Node* getPower(Node* parent, char *str, size_t *ip) {
    Node* newNode = getBracketsFunc(parent, str, ip);
    while(str[*ip] == '^') {
        (*ip)++;
        Node* leftNode = newNode;
        Node* rightNode = getBracketsFunc(parent, str, ip);
        MAKENODE(OPER_POW);
    }
    return newNode;
}

Node* getBracketsFunc(Node* parent, char *str, size_t *ip) {
    if(str[*ip] == '(') {
        (*ip)++;
        Node* newNode = getAddSub(parent, str, ip);
        assert(str[*ip] == ')');
        (*ip)++;
        return newNode;
    }
    else if(!isdigit(str[*ip])) {
        return makeId(parent, str, ip);
    }
    else return getNumber(parent, str, ip);
}

Node* makeId(Node* parent, char *str, size_t *ip) {
    char id[3] = {};
    int idLength = 0;
    sscanf(str + (*ip), "%2[A-Za-z0-9] %n", id, &idLength);
    (*ip) += (size_t)idLength;
    Node* newNode = NULL;
    if(!strcmp(id, "x")) {
        newNode = NodeCtor(parent, VAR, 'x');
        newNode->left_ = NULL;
        newNode->right_ = NULL;
        return newNode;
    }
    else if(!strcmp(id, "ln")) {
        newNode = NodeCtor(parent, FUNC, FUNC_LN);
        newNode->left_ = getAddSub(newNode, str, ip);
        newNode->right_ = NULL;
        return newNode;
    }
    else {
        printf("Error: unknown id %s\n",id);
        exit(EXIT_FAILURE);
    }
}

Node* getNumber(Node* parent, char* str, size_t *ip) {
    int val = 0;
    while('0' <= str[*ip] && str[*ip] <= '9') {
        val = val * 10 + str[*ip] - '0';
        (*ip)++;
    }
    Node* newNode = NodeCtor(parent, NUM, val);
    newNode->left_ = NULL;
    newNode->right_ = NULL;
    return newNode;
}
