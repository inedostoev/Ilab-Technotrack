#include "Node.h"


struct List* ListCtor(Node* firstNode) {
    List* list = (List*)calloc(1, sizeof(List));
    list->firstNode_ = firstNode;
    list->lastNode_ = firstNode;
    return list;
}

int DeleteList(List* list) {
    if(list == NULL) return -1;
    list->firstNode_ = NULL;
    list->lastNode_ = NULL;
    free(list);
    return 0;
}

struct Node* NodeCtor(Node* parent, Data_t data) {
    Node* node = (Node*)calloc(1, sizeof(Node));
    if(node == NULL) {
        printf("Can't allocate memory for Node\n");
        exit(NODE_NULL_PTR);
    }
    node->parent_ = parent;
    node->next_ = NULL;
    node->data_ = data;
    return node;
}

int ListDtor(Node* root) {
    if(root == NULL) {
        return 0;
    }
    root->data_ = -666;
    root->parent_ = NULL;
    ListDtor(root->next_);
    root->next_ = NULL;
    free(root);
    return 0;
}

int NodeDtor(Node* node) {
    assert(node != NULL);
    node->data_ = -666;
    node->parent_ = NULL;
    node->next_ = NULL;
    free(node);
    return 0;
}

Node* addFirstNode(List* list, Data_t data) {
    Node* newNode = NodeCtor(NULL, data);
    newNode->next_ = list->firstNode_;
    list->firstNode_->parent_ = newNode;
    list->firstNode_ = newNode;
    return newNode;
}

Node* addLastNode(List* list, Data_t data) {
    Node* newNode = NodeCtor(list->lastNode_, data);
    newNode->parent_->next_ = newNode;
    list->lastNode_ = newNode;
    return newNode;
}

Node* addNodeOnAdress(List* list, Node* adress, Data_t data) {
    if(adress == NULL) {
        printf("Error: null adress send to addNodeOnAdress\n");
        return NULL;
    }
    Node* root = list->firstNode_;
    while(root != adress) {
        if(root == NULL) {
            printf("Can't find this adress\n");
            return NULL;
        }
        root = root->next_;
    }
    Node *tmpPtr = root->next_;
    root->next_ = NodeCtor(root, data);
    root->next_->next_ = tmpPtr;
    tmpPtr->parent_ = root;
    return root->next_;
}

Node* DeleteNodeOnAdress(List* list, Node* node) {
    if(node == NULL) {
        printf("Error: node = NULL\n");
        return NULL;
    }
    else if(node->parent_ == NULL) 
        return DeleteFirstNode(list);
    else if(node->next_ == NULL) {
        list->lastNode_ = node->parent_;
        node->parent_->next_ = NULL;
        NodeDtor(node);
        return NULL;
    }
    else {
        node->next_->parent_ = node->parent_;
        node->parent_->next_ = node->next_;
        NodeDtor(node);
        return NULL;
    }
}

Node* DeleteFirstNode(List* list) {
    Node* root = list->firstNode_;
    root->next_->parent_ = NULL;
    Node* newRoot = root->next_;
    list->firstNode_ = newRoot;
    NodeDtor(root);
    return newRoot;
}

int NodeDump(Node* root) {
    FILE* ptrFile = fopen("dumpFile.gv", "w");
    if (ptrFile == NULL) {
        printf("Error with dumpFile.gv\n");
        exit(EXIT_FAILURE);
    }
    fprintf(ptrFile, "digraph graf {\n");
    
    dotNodeDump(root, ptrFile);
    
    fprintf(ptrFile, "}");
    fclose(ptrFile);
    system("dot dumpFile.gv -Tpng -o dumpFile.png");
    system("xdot dumpFile.gv");
    return 0;
}

int dotNodeDump(Node *root, FILE* stream) {
    fprintf(stream, "treeNode_%p [label=\""
                    "treeNode_[%p]\\l",
                    root, root);
    fprintf(stream, "{\\l");
    fprintf(stream, "  parent_ [%p]\\l", root->parent_);
    fprintf(stream, "  data_ = %lg\\l", root->data_);
    fprintf(stream, "  next_ [%p]\\l", root->next_);
    fprintf(stream, "}\\l");
    fprintf(stream, "\"]\n");
    if(root->next_ == NULL) return 0;
    fprintf(stream, "treeNode_%p->treeNode_%p\n", root, root->next_);
    dotNodeDump(root->next_, stream);
    return 0;
}
