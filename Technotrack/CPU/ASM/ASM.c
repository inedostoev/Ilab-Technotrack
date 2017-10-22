#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h> 

enum ASM_CMDS {
#define CPUCMDS
#define CPUCMD(cmdname, arg, code)			\
	ASM_##cmdname,									
#include "CPU_CMD"
#undef CPUCMD
#undef CPUCMDS
	ASM_DEFAULT
};

enum CONFIG {
	MAX_CMD_SIZE	= 6,
	MAX_ARG_SIZE    = 6,
	LABELS_QT       = 8
};

enum ASM_ERRORS {
    ASM_FOPEN_ERROR     = -1,
    ASM_PRE_ASM_ERROR   = -2
};

int assembling(FILE *asmFile, FILE *binFile);
int checkFiles(const FILE *asmFile, const FILE *binFile);
size_t getFileSize(FILE *asmFile);
int preAssembling(char *asmBuffer, int *labelAddress, size_t *qtCmd);
char* fromFileToBuf(FILE *asmFile);
ASM_CMDS getCmdNum(char *asmBuffer);
int gerArgs(ASM_CMDS cmdCode, char **asmBuffer, FILE *binFile, int *labelAddress);
int getCmdArgQt(ASM_CMDS CmdCode);

int assembling(FILE *asmFile, FILE *binFile) {
    if(checkFiles(asmFile, binFile)) {
        exit(ASM_FOPEN_ERROR);
    }
    char *asmBuffer = fromFileToBuf(asmFile);
    char *slider = asmBuffer;
    int *labelAddress = (int*)calloc(LABELS_QT, sizeof(int));
    for(int i = 0; i < LABELS_QT; i++) {
        labelAddress[i] = -1;
    }
    size_t qtCmd = 0;
    if(preAssembling(slider, labelAddress, &qtCmd)) {
        printf("Error with preAssembling\n");
        exit(ASM_PRE_ASM_ERROR);
    }
    int cmdLength = 0;
    char* scannedStr = (char*)calloc(MAX_CMD_SIZE, sizeof(char));
    assert(scannedStr != NULL);
    for(size_t i = 0; i < qtCmd; i++) {
        assert(MAX_CMD_SIZE == 6);
        sscanf(slider, "%5[A-Z0-9] %n", scannedStr, &cmdLength);
        slider += cmdLength;
        ASM_CMDS cmdCode = getCmdNum(scannedStr);
        assert(cmdCode != ASM_DEFAULT);
        fprintf(binFile, "%d ", cmdCode);
        int result = gerArgs(cmdCode, &slider, binFile, labelAddress);
    }
    free(scannedStr);
    free(asmBuffer);
    free(labelAddress);
    return 0;
}

int checkFiles(const FILE *asmFile, const FILE *binFile) {
	if (!asmFile) {
        printf("asmFile no open\n");
        return ASM_FOPEN_ERROR;
    }
	else printf("asmFile open\n");
	if (!binFile) {
        printf("binFile no open\n");
	    return ASM_FOPEN_ERROR;
    }
    else printf("binFile open\n");
    return 0;
}

char* fromFileToBuf(FILE* asmFile) {
    size_t fileSize = getFileSize(asmFile);
    char *asmBuffer = (char*)calloc(fileSize, sizeof(char));
    assert(asmBuffer != NULL);
    size_t count = fread(asmBuffer, sizeof(char), fileSize, asmFile);
    assert(count = fileSize);
    return asmBuffer; 
}


size_t getFileSize(FILE* asmFile) {
    fseek(asmFile, 0, SEEK_END);
    size_t fileSize = (size_t)ftell(asmFile) + 1;
    assert(fileSize > 1);
    rewind(asmFile);
    return fileSize;
}

int preAssembling(char *asmBuffer, int *labelAddress, size_t *qtCmd) {
    int label = 0;
    char* tmpPtr = NULL;
    size_t fileSize = strlen(asmBuffer);
    for(size_t i = 0; i < fileSize; i++) {
        if(asmBuffer[i] == '\n') {
            (*qtCmd)++;
        }
        if(asmBuffer[i] == ':') {
            label = asmBuffer[i + 1] - '0';
            assert(LABELS_QT < 10 && label < LABELS_QT && labelAddress[label] == -1);
            labelAddress[label] = *qtCmd;
            for(tmpPtr = asmBuffer + i; tmpPtr < strchr(tmpPtr, '\n'); tmpPtr++) {
                *tmpPtr = ' ';
            }
            *tmpPtr = ' ';
        }

        //комменты и пропуск пробелов
    }
    return 0;
}

ASM_CMDS getCmdNum(char *scannedStr) {
#define CPUCMDS
#define CPUCMD(cmdname, arg, code)						\
	if (!strcasecmp(#cmdname, scannedStr))       	    \
		return ASM_##cmdname;
#include "CPU_CMD"
#undef CPUCMD
#undef CPUCMDS
	else return ASM_DEFAULT;
}


int gerArgs(ASM_CMDS cmdCode, char **asmBuffer, FILE *binFile, int *labelAddress) {
    int argQt = getCmdArgQt(cmdCode);
    assert(argQt != -1);
    char* argValue = (char*)calloc(MAX_ARG_SIZE, sizeof(char));
    assert(argValue != NULL);
    int cmdLength = 0;
    for(int i = 0; i < argQt; i++) {
        assert(MAX_ARG_SIZE == 6);
        sscanf(*asmBuffer, "%5[0-9%$.-] %n", argValue, &cmdLength);
        *asmBuffer += cmdLength;
        if(argValue[0] == '$' || argValue[0] == '%') {
            fprintf(binFile, "%s ", argValue);
        }
        else {
            assert(labelAddress[argValue[0] - '0'] != -1);
            fprintf(binFile, "%d ", labelAddress[argValue[0] - '0']);
        }
    }
    free(argValue);
    return 0;
}

int getCmdArgQt(ASM_CMDS CmdCode) {
#define CPUCMDS
#define CPUCMD(cmdname, arg, code)				        \
    if (CmdCode == ASM_##cmdname)   			        \
        return arg;
#include "CPU_CMD"
#undef CPUCMD
#undef CPUCMDS
	else return -1;
}


int main() {
	FILE* asmFile = fopen("asmFile", "rb");
	FILE* binFile = fopen("binFile", "wb");
	assembling(asmFile, binFile);
    return 0;
}
