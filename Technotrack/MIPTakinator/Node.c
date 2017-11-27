#include "Node.h"


struct Node* NodeCtor(Node* parent, char* data) {
    Node* node = (Node*)calloc(1, sizeof(Node));
    if(node == NULL) {
        printf("Can't allocate memory for Node\n");
        exit(NODE_NULL_PTR);
    }
    node->data_ = data;
    node->parent_ = parent;
    node->left_ = NULL;
    node->right_ = NULL;
    return node;
}

int ListDtor(Node* root) {
    if(root == NULL) {
        return 0;
    }
    free(root->data_);
    root->data_ = NULL;
    root->parent_ = NULL;
    ListDtor(root->left_);
    ListDtor(root->right_);
    root->left_ = NULL;
    root->right_ = NULL;
    free(root);
    return 0;
}

int NodeDump(Node* root, dumpMod mode) {
    FILE* ptrFile = fopen("dumpFile.gv", "w");
    if (ptrFile == NULL) {
        printf("Error with dumpFile.gv\n");
        exit(EXIT_FAILURE);
    }
    fprintf(ptrFile, "digraph graf {\n");
    
    if(mode == USER) dotUserDump(root, ptrFile);
    else dotNodeDump(root, ptrFile);
    
    fprintf(ptrFile, "}");
    fclose(ptrFile);
    system("dot dumpFile.gv -Tpng -o dumpFile.png");
    system("xdot dumpFile.gv");
    return 0;
}

int dotUserDump(Node *root, FILE* stream) {
    fprintf(stream, "treeNode_%p [label=\"", root);
    fprintf(stream, "%s\\l", root->data_);
    fprintf(stream, "\\l"
                    "\"]\n");
    if(root->left_) {
        fprintf(stream, "treeNode_%p->treeNode_%p\n", root, root->left_);
        dotUserDump(root->left_, stream);
    }
    if(root->right_) {
        fprintf(stream, "treeNode_%p->treeNode_%p\n", root, root->right_);
        dotUserDump(root->right_, stream);
    }
    return 0;
}

int dotNodeDump(Node *root, FILE* stream) {
    fprintf(stream, "treeNode_%p [label=\""
                    "treeNode_[%p]\\l",
                    root, root);
    fprintf(stream, "{\\l");
    fprintf(stream, "  parent_ [%p]\\l", root->parent_);
    fprintf(stream, "  data_ = %s\\l", root->data_);
    fprintf(stream, "  left_ [%p]\\l", root->left_);
    fprintf(stream, "  right_ [%p]\\l", root->right_);
    fprintf(stream, "}\\l"
                    "\"]\n");
    if(root->left_) {
        fprintf(stream, "treeNode_%p->treeNode_%p\n", root, root->left_);
        dotNodeDump(root->left_, stream);
    }
    if(root->right_) {
        fprintf(stream, "treeNode_%p->treeNode_%p\n", root, root->right_);
        dotNodeDump(root->right_, stream);
    }
    return 0;
}
