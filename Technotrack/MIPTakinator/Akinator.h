#ifndef AKINATOR_H_INCLUDED
#define AKINATOR_H_INCLUDED

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Node.h"

const int MAX_CMD_LENGTH = 4;
const int MAX_QN_LENGTH = 128;
const int YES = 1;
const int NO = 0;

int callMenu();
int scanfCmd();
Node* akinatorCtor();
Node* buildTree(char* buffer, size_t *counter, Node* Darth_Vader);
int findAnswer(Node* node, Node* root);
int scanfAnswer();
int addAnswer(Node* nodePointer, Node* root);
int writeFile(FILE* outputFile, Node* nodePointer);


#endif
