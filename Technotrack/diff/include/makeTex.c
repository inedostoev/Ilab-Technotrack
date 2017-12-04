#include "diff.h"

int makeTex(Node* root, Node* firstNode) {
    FILE* stream = fopen("diff.tex", "w");
    if (stream == NULL) {
        printf("Error with diff.tex\n");
        exit(1);
    }
    fprintf(stream, "\\documentclass{article}\n");
    fprintf(stream, "\\usepackage[a4paper, margin=6mm]{geometry}\n");
    fprintf(stream, "\\usepackage{amsmath}\n");
    //fprintf(stream, "\\usepackage[utf8x]{inputenc}\n");
    //fprintf(stream, "\\usepackage[russian]{babel}\n");
    fprintf(stream, "\\usepackage{hyperref}\n");
    fprintf(stream, "\\title{Берем производную без смс и регистрации}\n");
    fprintf(stream, "\\begin{document}\n");
    fprintf(stream, "\\maketitle\n");
    fprintf(stream, "\\begin{eqnarray}\n");
    fprintf(stream, "\\left( ");
    makeTexNodeDump(firstNode, stream);
    fprintf(stream, "\\right) ' = \n");
    makeTexNodeDump(root, stream);
    printf("\n");
    fprintf(stream, "\\end{eqnarray}\n");
    fprintf(stream, "\\end{document}\n");
    fclose(stream);
    
    system("pdflatex diff.tex");
    system("evince diff.pdf");
    
    stream = NULL;
    return 0;
}

int makeTexNodeDump(Node* node, FILE* stream) {
    if(node == NULL) return 0;;
    if(node->type_ == FUNC) {
        if(node->data_ == FUNC_LN) {
            fprintf(stream, "Ln");
            fprintf(stream, "\\left(");
            makeTexNodeDump(node->left_, stream);
            makeTexNodeDump(node->right_, stream);
            fprintf(stream, "\\right)");
        }
    }
    if(node->type_ == OPER) {
        if(node->data_ == OPER_DIV) {
            fprintf(stream, "\\frac{");
            makeTexNodeDump(node->left_, stream);
            fprintf(stream, "}{");
            makeTexNodeDump(node->right_, stream);
            fprintf(stream, "}");
        } 
        else if(node->data_ == OPER_POW) {
            fprintf(stream, "{");
            makeTexNodeDump(node->left_, stream);
            fprintf(stream, "}^{");
            makeTexNodeDump(node->right_, stream);
            fprintf(stream, "}");
        }
        if(getPriority(node->parent_) > getPriority(node)) {
            if(node->data_ == OPER_SUB) {
                fprintf(stream, "\\left({");
                makeTexNodeDump(node->left_, stream);
                fprintf(stream, "-");
                makeTexNodeDump(node->right_, stream);
                fprintf(stream, "}\\right)"); 
            }
            else if(node->data_ == OPER_MUL) {
                fprintf(stream, "\\left({");
                makeTexNodeDump(node->left_, stream);
                fprintf(stream, "*");
                makeTexNodeDump(node->right_, stream);
                fprintf(stream, "}\\right)");        
            }
            else if(node->data_ == OPER_ADD) {
                fprintf(stream, "\\left({");
                makeTexNodeDump(node->left_, stream);
                fprintf(stream, "+");
                makeTexNodeDump(node->right_, stream);
                fprintf(stream, "}\\right)");
            }
        }
        else {
            if(node->data_ == OPER_SUB) {
                fprintf(stream, "{");
                makeTexNodeDump(node->left_, stream);
                fprintf(stream, "}-{");
                makeTexNodeDump(node->right_, stream);
                fprintf(stream, "}"); 
            }
            else if(node->data_ == OPER_MUL) {
                fprintf(stream, "{");
                makeTexNodeDump(node->left_, stream);
                fprintf(stream, "}*{");
                makeTexNodeDump(node->right_, stream);
                fprintf(stream, "}");        
            }
            else if(node->data_ == OPER_ADD) {
                fprintf(stream, "{");
                makeTexNodeDump(node->left_, stream);
                fprintf(stream, "}+{");
                makeTexNodeDump(node->right_, stream);
                fprintf(stream, "}");
            }
        }
    }
    if(node->type_ == VAR) {
        fprintf(stream, "{x}");
        makeTexNodeDump(node->left_, stream);
        makeTexNodeDump(node->right_, stream);
    }
    if(node->type_ == NUM) {
        fprintf(stream, "{%d}", node->data_);
        makeTexNodeDump(node->left_, stream);
        makeTexNodeDump(node->right_, stream);
    }
    return 0;
}

Priority getPriority(Node* node) {
    if(node == NULL) return LOW_PRIOR;
    if(node->type_ == OPER && (node->data_ == OPER_ADD || 
                               node->data_ == OPER_SUB )) 
        return ADDSUB_PRIOR;
    if(node->type_ == OPER && (node->data_ == OPER_MUL || 
                               node->data_ == OPER_DIV )) 
        return MULDIV_PRIOR;
    if(node->type_ == OPER && node->data_ == OPER_POW) return EXP_PRIOR;
    return LOW_PRIOR;
}
