#include "Akinator.h"


int callMenu() {
    printf("Играть в игру [p]\n"
            "Dump [l]\n"
            "Выход [q]\n"
            "\nПоддержать автора: MasterCard 5469 3800 6135 6142\n");
    scanfCmd();
    return 0;
}

int scanfCmd() {
    Node* root = akinatorCtor();
    printf("\n");
    char scanfCmd[MAX_CMD_LENGTH];
    scanf("%3s", scanfCmd);
    if(!strcasecmp(scanfCmd, "p")) {
        printf("Я хочу поиграть с тобой в одну игру\n"
               "Загадай преподавателя из физтеха\n"
               "Сейчас я его отгадаю. на вопросы отвечай [да/нет] [yes/no] [y/n]\n");
        findAnswer(root, root);
    }
    else if(!strcasecmp(scanfCmd, "l")) {
        NodeDump(root);
    }
    else if(!strcasecmp(scanfCmd, "q")) {
        exit(1);
    }
    else {
        printf("Команда не распознана, попробуй еще\n");
    }
    ListDtor(root);
    return 0;
}

Node* akinatorCtor() {
    struct stat buf;
    lstat("configFile", &buf);
    off_t fileSize = buf.st_size;
    
    FILE* inputFile = fopen("configFile", "r");
    if(inputFile == NULL) {
        printf("Can't open configFile\n");
        exit(EXIT_FAILURE);
    }
    char *buffer = (char*)calloc(fileSize, sizeof(char));
    assert(buffer != NULL);
    fread(buffer, sizeof(char), fileSize, inputFile);  
    size_t counter = 0;
    Node* Tree = buildTree(buffer, &counter, NULL);
    free(buffer);
    fclose(inputFile);
    return Tree;
}

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

int findAnswer(Node* node, Node* root) {
    if(node == NULL) return 1;
    printf("%s\n", node->data_);
    int answer = scanfAnswer();
    if(node->left_ == NULL && node->right_ == NULL) {
        if(answer == YES) {
            printf("Ура, я угадал!\n");
        }
        else {
            addAnswer(node, root);
        }
    }
    else {
        if(answer == YES) {
            findAnswer(node->left_, root);
        }
        else {
            findAnswer(node->right_, root);
        }

    }
    return 0;
}

int scanfAnswer() {
    char answer[4];
    scanf("%3s", answer);
    if(!strcasecmp(answer, "yes") || !strcasecmp(answer, "да") || !strcasecmp(answer, "y")) {	
        return YES;
    }
    else if(!strcasecmp(answer, "no") || !strcasecmp(answer, "нет") || !strcasecmp(answer, "n")) {
        return NO;
    }
    else {
        printf("Вы не ввели ответ, попытайтесь еще\n");
        return scanfAnswer();
    }
}

int addAnswer(Node* nodePointer, Node* root) {						 
    printf("Упс, не знаю такого, давай внесем его в базу\n"
           "Введи преподавателя, которого загадали\n");
    char* answerStr_ = (char*)calloc(MAX_QN_LENGTH, sizeof(char));
    scanf("%s", answerStr_);
    printf("Введи отличительную черту от преподавателя по фамилии %s. В конце обязательно поставь вопрос\n", nodePointer->data_);
    char* questionStr_ = (char*)calloc(MAX_QN_LENGTH, sizeof(char));
    int count = -1;
    scanf("%[^?]%n", questionStr_, &count);
    questionStr_[count] = '?';
    questionStr_[count + 1] == ' ';
    nodePointer->left_ = NodeCtor(nodePointer, answerStr_);
    nodePointer->right_ = NodeCtor(nodePointer, nodePointer->data_);
    nodePointer->data_ = questionStr_;
    FILE* outputFile = fopen("configFile", "w");
	if (outputFile == NULL) {
		printf("Can't open configFile\n");
		exit(EXIT_FAILURE);
	}
    writeFile(outputFile, root);
    fclose(outputFile);
    return 0;
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

