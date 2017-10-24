#include "CPU.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

struct CPU *cpuCtor() {
    CPU *cpu = (CPU*)calloc(1, sizeof(CPU));
    assert(cpu != NULL);
    cpu->registers = (Data_t*)calloc(REGISTERS_QT, sizeof(Data_t));
    cpu->masArgs = (Data_t*)calloc(MAX_ALLOW_FUNC_ARGS, sizeof(Data_t));
    cpu->masRegOrNum = (int*)calloc(MAX_ALLOW_FUNC_ARGS, sizeof(int));
    assert(cpu->registers != NULL && 
           cpu->masArgs != NULL && 
           cpu->masRegOrNum != NULL);
    cpu->stack = StackCtor(10);
    cpu->callStack = StackCtor(10);
    return cpu;
}

int cpuDtor(CPU* cpu) {
    free(cpu->registers);
    free(cpu->masArgs);
    free(cpu->masRegOrNum);
    StackDtor(cpu->stack);
    StackDtor(cpu->callStack);
    free(cpu);
    return 0;
}

int execute(FILE *inputFile) {
    if(inputFile == NULL) {
        printf("FILE *inputFile == NULL\n");
        exit(CPU_FOPEN_ERROR);
    }
    char *buffer = fromFileToBuf(inputFile);
    char *slider = buffer;
    int qtCmd = countCmd(buffer);
    
    int cmdLength = 0;
    char* scannedStr = (char*)calloc(MAX_CMD_SIZE, sizeof(char));
    assert(scannedStr != NULL);
    
    CPU *cpu = cpuCtor();
    int ip = 0;
    while(ip <= qtCmd) {
        sscanf(buffer, "%5[0-9] %n", scannedStr, &cmdLength);
        buffer += cmdLength;
        CPU_CMDS cmdCode = getCmdNum(scannedStr);
        assert(cmdCode != CPU_DEFAULT);
        int argQt = getCmdArgQt(cmdCode);
        assert(argQt != -1 && argQt <= MAX_ALLOW_FUNC_ARGS);
        for(int i = 0; i < argQt; i++) {
            analysisArg(i, &buffer, cpu);
        }
        executeCmd(cmdCode, cpu, slider, &buffer, &ip);
        ip++;
    }
    cpuDump(stdout, cpu, ip);
    cpuDtor(cpu);
    free(scannedStr);
    free(slider);
    return 0;
}

char *fromFileToBuf(FILE *inputFile) {
    size_t fileSize = getFileSize(inputFile);
    char *buffer = (char *)calloc(fileSize, sizeof(char));
    assert(buffer != NULL);
    size_t size = fread(buffer, sizeof(char), fileSize, inputFile);
    assert(size <= fileSize);
    return buffer;
}

size_t getFileSize(FILE *inputFile) {
	fseek(inputFile, 0, SEEK_END);
	size_t fileSize = ftell(inputFile) + 1;
	assert(fileSize > 1);
    rewind(inputFile);
    return fileSize;
}

int countCmd(char* buffer) {
    int binNum = 0;
    for(int i = 0; i < strlen(buffer); i++) {
        if(buffer[i] == ' ') binNum++;
    }
    int qtCmd = 0;
    int cmdLength = 0;
    char* scannedStr = (char*)calloc(MAX_CMD_SIZE, sizeof(char));
    assert(scannedStr != NULL);
    for(int tmp = 0; tmp < binNum; tmp++) {
        sscanf(buffer, "%5[0-9] %n", scannedStr, &cmdLength);
        buffer += cmdLength;
        CPU_CMDS cmdCode = getCmdNum(scannedStr);
        assert(cmdCode != CPU_DEFAULT);
        qtCmd++; 
        int argQt = getCmdArgQt(cmdCode);
        assert(argQt != -1 && argQt <= MAX_ALLOW_FUNC_ARGS);
        for(int i = 0; i < argQt; i++) {
            sscanf(buffer, "%5[0-9$%-.] %n", scannedStr, &cmdLength);
            buffer += cmdLength;
            tmp++;
        }
    }   
    free(scannedStr);
    return qtCmd;
}

CPU_CMDS getCmdNum(char* scannedStr) {
int binNum= atoi(scannedStr);
#define CPUCMDS
#define CPUCMD(cmdname, args, code)									            \
    if (CPU_##cmdname == binNum)   \
		return CPU_##cmdname;
#include "./ASM/CPU_CMD"
#undef CPUCMD
#undef CPUCMDS
	else return CPU_DEFAULT;
}

int getCmdArgQt(CPU_CMDS cmdCode) {
#define CPUCMDS
#define CPUCMD(cmdname, args, code)									            \
    if (cmdCode == CPU_##cmdname)									            \
        return args;
#include "./ASM/CPU_CMD"
#undef CPUCMD
#undef CPUCMDS
	else return -1;
}

int analysisArg(int numArg, char **buffer, CPU *cpu) {
    int cmdLength = 0;
    char* scannedStr = (char*)calloc(MAX_CMD_SIZE, sizeof(char));
    sscanf(*buffer, "%5[0-9$%-.] %n", scannedStr, &cmdLength);
    *buffer += cmdLength;
    
    if (scannedStr[0] == '$') {
	    cpu->masRegOrNum[numArg] = 0;
		scannedStr[0] = ' ';
	}
	if (scannedStr[0] == '%') {
		cpu->masRegOrNum[numArg] = 1;
		scannedStr[0] = ' ';
	}
	else {										
		cpu->masRegOrNum[numArg] = 0;
	}
	cpu->masArgs[numArg] = atof(scannedStr);
    free(scannedStr);
    return 0;
}

int executeCmd(CPU_CMDS cmdCode, CPU *cpu, char* slider, char **buffer, int *ip) {
	Data_t firstArg = 0;
    Data_t secondArg = 0;
	switch (cmdCode)
	{
#define CPUCMDS
#define CPUCMD(cmdname, args, code)						\
	case CPU_##cmdname:									\
		code											\
		break;											
#include "./ASM/CPU_CMD"
#undef CPUCMD
#undef CPUCMDS
	default:
		printf("Error, unknown cmd\n");
		break;
	}
    return 0;
}

int moveIp(Data_t newAdress, char *slider, char **buffer, int *ip) {
    int cmdLength = 0;
    char* scannedStr = (char*)calloc(MAX_CMD_SIZE, sizeof(char));
    assert(scannedStr != NULL);
    (*buffer) = slider;
    int counter = 0;
    for(counter = 0; counter < newAdress; counter++) {
        sscanf(*buffer, "%5[0-9] %n", scannedStr, &cmdLength);
        *buffer += cmdLength;
        CPU_CMDS cmdCode = getCmdNum(scannedStr);
        assert(cmdCode != CPU_DEFAULT);
        int argQt = getCmdArgQt(cmdCode);
        assert(argQt != -1 && argQt <= MAX_ALLOW_FUNC_ARGS);
        for(int i = 0; i < argQt; i++) {
            sscanf(*buffer, "%5[0-9$%-.] %n", scannedStr, &cmdLength);
            *buffer += cmdLength;
        }
    }   
    (*ip) = counter;
    free(scannedStr);
    return 0; 
}

int cpuDump(FILE* stream, CPU *cpu, int ip) {
	fprintf(stream, "\n/***********DUMP***********/\nCPU\n\t{\n\tip = %i\n", ip);
	for (int i = 0; i < REGISTERS_QT; i++) {
		fprintf(stream, "\tr[%i] = %lg\n", i, cpu->registers[i]);
	}
    
    char *stackName = "cpuStack";
    StackDump(cpu->stack, stream, stackName);

    char *callStackName = "callStack";
    StackDump(cpu->callStack, stream, callStackName);
	fprintf(stream, "}\n");
    return 0;
}
