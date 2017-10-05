#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

char* fromFileToBuf(char *fileName);
int sortFile(char *fileName);
int compare(const void *str1, const void *str2);
int compareInv(const void *str1, const void *str2);
size_t getFileSize(FILE* inputFile);
int fromBuftoFile(char *fileName, size_t qtStr, char** pointerStr); 
size_t counterStr(char* buffer, size_t qtChar);
char* makeInvStr(const void *str, int *qtPunct); 

int main(int argc, char *argv[]) {
    if(argc == 2) {
        int result = sortFile(argv[1]);        
        if(result != 1) {
            exit(EXIT_FAILURE);
        }
    }
    else if(argc > 2) {
        printf("Too many arguments\n");
        exit(EXIT_FAILURE);
    }
    else {
        printf("Too few arguments\n");
        exit(EXIT_FAILURE);
    }
    return 0;
}

int sortFile(char *fileName) {
    char* buffer = fromFileToBuf(fileName);

    size_t qtChar = strlen(buffer);
    size_t qtStr = counterStr(buffer, qtChar);
    
    char** pointerStr = (char**)calloc(qtStr + 1, sizeof(*pointerStr)); 
    
    pointerStr[0] = buffer;
    int ip = 1;
    for(unsigned int i = 0; i < qtChar; i++) {
        if(buffer[i] == '\n') {
            buffer[i] = '\0';
            pointerStr[ip] = buffer + i + 1;
            ip++;
        }
    }

    qsort(pointerStr, qtStr, sizeof(*pointerStr), compare);
  
    char outputFile[] = "SortedFile";
    int result = fromBuftoFile(outputFile, qtStr, pointerStr);
    if(result != 1) {
        printf("Error in func fromBuftoFile\n");
        exit(EXIT_FAILURE);
    }
    
    qsort(pointerStr, qtStr, sizeof(*pointerStr), compareInv);

    char outputInvFile[] = "SortedFileInv";
    result = fromBuftoFile(outputInvFile, qtStr, pointerStr);
    if(result != 1) {
        printf("Error in func fromBuftoFile\n");
        exit(EXIT_FAILURE);
    }

    free(pointerStr);
    free(buffer);
    return 1;
}

char* fromFileToBuf(char *fileName) {
    FILE* inputFile = NULL;
    inputFile = fopen(fileName, "r");
    if(inputFile == NULL) {
        printf("Error with open %s file\n", fileName);
        exit(EXIT_FAILURE);
    }
    size_t fileSize = getFileSize(inputFile);
    char* buffer = (char*)calloc(fileSize, sizeof(char));
    if(buffer == NULL) {
        printf("Can't allocate memory\n");
        exit(EXIT_FAILURE);
    }
    size_t size = fread(buffer, sizeof(char), fileSize - 1, inputFile);
    if(size != fileSize - 1) {
        printf("Error with fread. Can't read all characters\n");
        exit(EXIT_FAILURE);
    }
    buffer[fileSize - 1] = '\0';
    fclose(inputFile);
    return buffer;
}

int fromBuftoFile(char *fileName, size_t qtStr, char** pointerStr) {
    FILE* outputFile = NULL;
    outputFile = fopen(fileName, "w+");
    if(outputFile == NULL) {
        printf("Error with open %s file\n", fileName);
        exit(EXIT_FAILURE);
    }

    for(size_t i = 0; i < qtStr; i++) {
        fprintf(outputFile, "%s\n", pointerStr[i]);
    }
    return 1;
}

size_t getFileSize(FILE* inputFile) {
	size_t fileSize = 0;
    fseek(inputFile, 0, SEEK_END);
	fileSize = (size_t)ftell(inputFile) + 1;
	if(fileSize <= 1) {
        printf("Empty file\n");
        exit(EXIT_FAILURE);
    }
    rewind(inputFile);
    return fileSize;
}

size_t counterStr(char* buffer, size_t qtChar) {
    size_t qtStr = 0;
    for(unsigned int i = 0; i < qtChar; i++) {
        if(buffer[i] == '\n') {
            qtStr++;
        }
    }
    return qtStr;
}

int compare(const void *str1, const void *str2) {
    return strcasecmp(*(const char**)str1, *(const char**)str2);
}

int compareInv(const void *str1, const void *str2) {
    /*
    size_t qtChar1 = strlen(*(const char **)str1);
    char *invStr1 = (char*)calloc(qtChar1, sizeof(char));
    char *tmpStr1 = (char*)calloc(qtChar1, sizeof(char));
    strncpy(tmpStr1, *(const char**)str1, qtChar1);
    for(unsigned int i = 0; i < qtChar1; i++) {
        invStr1[i] = tmpStr1[qtChar1 - i - 1];
    }
  //функция 
    size_t qtChar2 = strlen(*(const char**)str2);
    char *invStr2 = (char*)calloc(qtChar2, sizeof(char));
    char *tmpStr2 = (char*)calloc(qtChar2, sizeof(char));
    strncpy(tmpStr2, *(const char**)str2, qtChar2);   
    for(unsigned int i = 0; i < qtChar2; i++) {
        invStr2[i] = tmpStr2[qtChar2 - i - 1];
    }
    
    int result = strcasecmp(invStr1, invStr2);
    free(invStr1);
    free(invStr2);
    free(tmpStr1);
    free(tmpStr2);
    */
    int qtPunct1 = 0;
    char* invStr1 = makeInvStr(str1, &qtPunct1);

    int qtPunct2 = 0;
    char* invStr2 = makeInvStr(str2, &qtPunct2);
    
    int result = strcasecmp(invStr1, invStr2);
    free(invStr1 - qtPunct1);
    free(invStr2 - qtPunct2);
     
    return result;
}

char* makeInvStr(const void *str, int *qtPunct) {
    size_t qtChar = strlen(*(const char **)str);
    char *invStr = (char*)calloc(qtChar, sizeof(char));
    const char *tmpStr = *(const char**)str;
    for(unsigned int i = 0; i < qtChar; i++) {
        invStr[i] = tmpStr[qtChar - i - 1];
    }
    int i = 0;
    while(ispunct(invStr[0])) {
        invStr++;
        i++;
    }
    (*qtPunct) = i;
    return invStr;
}
