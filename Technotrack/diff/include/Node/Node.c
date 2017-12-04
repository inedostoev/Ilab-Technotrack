#include "Node.h"


struct Node* NodeCtor(Node* parent, dataType type, int data) {
    Node* node = (Node*)calloc(1, sizeof(Node));
    if(node == NULL) {
        printf("Can't allocate memory for Node\n");
        exit(EXIT_FAILURE);
    }
    node->type_ = type;
    node->data_ = data;
    node->parent_ = parent;
    node->left_ = NULL;
    node->right_ = NULL;
    return node;
}

int TreeDtor(Node* root) {
    if(root == NULL) {
        return 0;
    }
    root->data_ = -666;
    root->parent_ = NULL;
    TreeDtor(root->left_);
    TreeDtor(root->right_);
    root->left_ = NULL;
    root->right_ = NULL;
    free(root);
    return 0;
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
    if(root->type_ == NUM) {
        fprintf(stream, "  type_ = NUM\\l");
        fprintf(stream, "  data_ = %d\\l", root->data_);
    }
    else if(root->type_ == VAR) {
        fprintf(stream, "  type_ = VAR\\l");
        fprintf(stream, "  data_ = x\\l");
    }
    else if(root->type_ == OPER) {
        fprintf(stream, "  type_ = OPER\\l");
        if(root->data_ == OPER_ADD) {
            fprintf(stream, "  data_ = +\\l");
        }
        else if(root->data_ == OPER_SUB) {
            fprintf(stream, "  data_ = -\\l");
        }
        else if(root->data_ == OPER_MUL) {
            fprintf(stream, "  data_ = *\\l");
        }
        else if(root->data_ == OPER_DIV) {
            fprintf(stream, "  data_ = /\\l");
        }
        else if(root->data_ == OPER_POW) {
            fprintf(stream, "  data_ = ^\\l");
        }
        else {
            printf("Error with OPER data\n");
            exit(EXIT_FAILURE);
        }
    }
    else if(root->type_ == FUNC) {
        fprintf(stream, "  type_ = FUNC\\l");
        if(root->data_ == FUNC_LN) {
            fprintf(stream, "  data_ = LN\\l");
        }
    }
    else {
        printf("Error with root->type\n");
        exit(EXIT_FAILURE);
    }
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
