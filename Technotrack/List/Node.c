#include "Node.h"


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
    NodeDtor(root->next_);
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

int AddNode(Node* root, Data_t data) {
    if(root->next_ != NULL) AddNode(root->next_, data);
    else root->next_ = NodeCtor(root, data);
    return 0;
}

Node* DeleteNode(Node* root, Data_t data) {
    if(root->data_ == data) {
        if(root->parent_ == NULL) {
            root->next_->parent_ = NULL;
            Node* newRoot = root->next_;
            NodeDtor(root);
            return newRoot;
        }
        else if(root->next_ == NULL) {
            root->parent_->next_ = NULL;
        }
        else {
            root->next_->parent_ = root->parent_;
            root->parent_->next_ = root->next_;
        }
        NodeDtor(root);
    }
    else if(root->next_ == NULL) {
        printf("Can't find Node with data_ = %lg\n", data);
        return root;
    }
    else {
        DeleteNode(root->next_, data);
    }
    return root;
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


