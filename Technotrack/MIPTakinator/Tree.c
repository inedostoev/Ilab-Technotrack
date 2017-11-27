#include"Tree.h"

Node* buildTree(char* buffer, size_t *counter, Node* Darth_Vader) {
    if(buffer[*counter + 1] == ')') {
        *counter += 2;
        return NULL;
    }
    (*counter)++;
    int len = -1;
    char* data = (char*)malloc(MAX_QN_LENGTH * sizeof(char));
    if (data == NULL) {
        printf("Can't allocate memory\n");
    }
    sscanf(buffer + (*counter), "%[^(]%n", data, &len);
    (*counter) += (size_t)len;
    Node* Luke = NodeCtor(Darth_Vader, data);
    Luke->left_ = buildTree(buffer, counter, Luke);
    Luke->right_ = buildTree(buffer, counter, Luke);
    (*counter)++;
    return Luke;
}

int writeFile(FILE *outputFile, Node *nodePointer) {
	if (nodePointer == NULL) {
		fprintf(outputFile, "()");
		return 1;
	}
	fprintf(outputFile, "(");
	fprintf(outputFile, "%s", nodePointer->data_);
	writeFile(outputFile, nodePointer->left_);
	writeFile(outputFile, nodePointer->right_);
	fprintf(outputFile, ")");
    return 0;
}

Node* copyTree(Node* node, Node* parent) {
    if(node == NULL) return NULL;
    Node* newNode = NULL;
    newNode = NodeCtor(parent, node->data_);
    newNode->left_ = copyTree(node->left_, newNode);
    newNode->right_ = copyTree(node->right_, newNode);
    return newNode;
}
