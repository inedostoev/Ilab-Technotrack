#include"diff.h"
#include<math.h>


#define MUL                                                                 \
    (diffNode->type_ == OPER && diffNode->data_ == OPER_MUL)
#define LEFTEQ(number)                                                      \
    (diffNode->left_->type_ == NUM && diffNode->left_->data_ == number)
#define RIGHTEQ(number)                                                     \
    (diffNode->right_->type_ == NUM && diffNode->right_->data_ == number)
#define LEFTCOPY                                                            \
    copyTree(diffNode->left_, parent)
#define RIGHTCOPY                                                           \
    copyTree(diffNode->right_, parent)
#define ADD                                                                 \
    (diffNode->type_ == OPER && diffNode->data_ == OPER_ADD)
#define SUB                                                                 \
    (diffNode->type_ == OPER && diffNode->data_ == OPER_SUB)
#define POW                                                                 \
    (diffNode->type_ == OPER && diffNode->data_ == OPER_POW)

Node* simplicationTree(Node* diffNode, Node* parent, int *flag) {
    if(diffNode == NULL) return NULL;
    Node* node = NULL;
    if(MUL && (LEFTEQ(0) || RIGHTEQ(0))) {
        (*flag) = 1;
        TreeDtor(diffNode);
        node = NodeCtor(parent, NUM, 0);
        node->left_ = NULL;
        node->right_ = NULL;
        return node;
    }
    else if(MUL && LEFTEQ(1)) {
        (*flag) = 1;
        node = RIGHTCOPY;
        TreeDtor(diffNode);
        return node;
    }
    else if(MUL && RIGHTEQ(1)) {
        (*flag) = 1;
        node = LEFTCOPY;
        TreeDtor(diffNode);
        return node;
    }
    else if((ADD || SUB) && RIGHTEQ(0)) {
        (*flag) = 1;
        node = LEFTCOPY;
        TreeDtor(diffNode);       
        return node;
    }
    else if(ADD && LEFTEQ(0)) {
        (*flag) = 1;
        node = RIGHTCOPY;
        TreeDtor(diffNode);
        return node;
    }
    else if(SUB && LEFTEQ(0)) {
        (*flag) = 1;
        node = NodeCtor(parent, OPER, OPER_MUL);
        node->left_ = NodeCtor(node, NUM, -1);
        node->right_ = RIGHTCOPY; 
        TreeDtor(diffNode);
        return node;
    }
    else if(POW && RIGHTEQ(1)) {
        (*flag) = 1;
        node = LEFTCOPY;
        TreeDtor(diffNode);
        return node;
    }
    else {
        node = diffNode;
        node->left_ = simplicationTree(diffNode->left_, node, flag);
        node->right_ = simplicationTree(diffNode->right_, node, flag);
        return node;
    }
}
