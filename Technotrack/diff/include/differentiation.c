#include "diff.h"


Node* differentiation(Node* node, Node* parent) {
    if(node == NULL) return NULL;
    Node* diffNode = NULL;

    switch(node->type_) {
        case NUM:
            diffNode = NodeCtor(parent, NUM, 0);
            break;
        case VAR:
            diffNode = NodeCtor(parent, NUM, 1);
            break;
        case OPER:
            switch(node->data_) {
                case OPER_ADD:
                    diffNode = NodeCtor(parent, OPER, OPER_ADD);
                    diffNode->left_ = differentiation(node->left_, diffNode);
                    diffNode->right_ = differentiation(node->right_, diffNode);
                    break;
                case OPER_SUB:
                    diffNode = NodeCtor(parent, OPER, OPER_SUB);
                    diffNode->left_ = differentiation(node->left_, diffNode);
                    diffNode->right_ = differentiation(node->right_, diffNode);
                    break;
                case OPER_MUL: {
                    diffNode = NodeCtor(parent, OPER, OPER_ADD);
                   
                    Node* leftNode = NodeCtor(diffNode, OPER, OPER_MUL);
                    leftNode->left_ = differentiation(node->left_, leftNode);
                    leftNode->right_ = copyTree(node->right_, leftNode);

                    Node* rightNode = NodeCtor(diffNode, OPER, OPER_MUL);
                    rightNode->left_ = copyTree(node->left_, rightNode);
                    rightNode->right_ = differentiation(node->right_, rightNode);

                    diffNode->left_ = leftNode;
                    diffNode->right_ = rightNode;                                }
                    break;
                case OPER_DIV: {
                    diffNode = NodeCtor(parent, OPER, OPER_DIV);
                    diffNode->left_ = NodeCtor(parent, OPER, OPER_SUB);
                    
                    Node* leftNode = NodeCtor(diffNode->left_, OPER, OPER_MUL);
                    leftNode->left_ = differentiation(node->left_, leftNode);
                    leftNode->right_ = copyTree(node->right_, leftNode);

                    Node* rightNode = NodeCtor(diffNode->left_, OPER, OPER_MUL);
                    rightNode->left_ = copyTree(node->left_, rightNode);
                    rightNode->right_ = differentiation(node->right_, rightNode);

                    diffNode->left_->left_ = leftNode;
                    diffNode->left_->right_ = rightNode;

                    Node* underLine = NodeCtor(diffNode, OPER, OPER_POW); //denominator
                    underLine->left_ = copyTree(node->right_, underLine);
                    underLine->right_ = NodeCtor(underLine, NUM, 2);
                    
                    diffNode->right_ = underLine;                               }
                    break;
                case OPER_POW: {
                    diffNode = NodeCtor(parent, OPER, OPER_MUL);
                    diffNode->left_ = NodeCtor(diffNode, OPER, OPER_POW);

                    Node* mulNode = NodeCtor(diffNode->left_, OPER, OPER_MUL);
                    mulNode->left_ = copyTree(node->left_, mulNode);
                    mulNode->right_ = copyTree(node->right_, mulNode);

                    diffNode->left_->left_ = mulNode;

                    diffNode->left_->right_ = NodeCtor(diffNode->left_, NUM, node->right_->data_ - 1);
                    
                    diffNode->right_ = differentiation(node->left_, diffNode); }
                    break;
                default:
                    printf("Unknown open\n");
                    exit(EXIT_FAILURE);
            }
            break;
        case FUNC:
            switch(node->data_) {
                case FUNC_LN:
                    diffNode = NodeCtor(parent, OPER, OPER_MUL);
                    diffNode->left_ = NodeCtor(diffNode, OPER, OPER_DIV);
                    diffNode->left_->left_ = NodeCtor(diffNode->left_, NUM, 1);
                    diffNode->left_->right_ = copyTree(node->left_, diffNode->left_);

                    diffNode->right_ = differentiation(node->left_, diffNode);
                    break;
                default:
                    printf("Unlnown function\n");
                    exit(EXIT_FAILURE);
            }
            break;
        default:
            printf("Unknown type\n");
            exit(EXIT_FAILURE);
    }
    return diffNode;
}
