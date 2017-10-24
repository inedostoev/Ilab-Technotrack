#ifndef CPU_H_INCLUDED
#define CPU_H_INCLUDED
#include "./Stack/Stack.h"

typedef double Data_t;

enum PROCESSOR_PROPERIES
{
	REGISTERS_QT = 4,
	MAX_CMD_SIZE = 6,
	MAX_ALLOW_FUNC_ARGS = 3,
};

enum CPU_CMDS{
#define CPUCMDS
#define CPUCMD(cmdname, args, code)									\
	CPU_##cmdname,
#include "./ASM/CPU_CMD"
#undef CPUCMD
#undef CPUCMDS
	CPU_DEFAULT
};

enum CPU_ERRORS {
    CPU_FOPEN_ERROR = -1
};

typedef struct CPU {
   Data_t *registers;
   Data_t *masArgs;
   int *masRegOrNum;
   Stack *stack;
   Stack *callStack;
} CPU;

int execute(FILE *inputFile);
char *fromFileToBuf(FILE *inputFile);
size_t getFileSize(FILE *inputFile);
int countCmd(char *buffer);
CPU_CMDS getCmdNum(char* scannedStr);
int getCmdArgQt(CPU_CMDS cmdCode);
int analysisArg(int numArg, char **buffer, CPU *cpu);
int executeCmd(CPU_CMDS cmdCode, CPU *cpu, char* slider,char **buffer, int *ip);
int moveIp(Data_t newAdress, char *slider, char **buffer, int *ip);
int cpuDump(FILE* stream, CPU *cpu, int ip);

#endif
