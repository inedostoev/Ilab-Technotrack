#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef double StackData_t;

const int leftCanary = 0x4D;
const int rightCanary = 0x309;

enum StackErrors {
    STACK_OK                = 0,
    STACK_NULL_PTR          = 1,
    STACK_NULL_DATA_PTR     = 2,
    STACK_WRONG_CAPACITY    = 3,
    STACK_WRONG_COUNT       = 4,
    STACK_UNDERFLOW         = 5,
    STACK_SPOILED           = 6
};

typedef struct Stack {
    int         leftCanary_;
    size_t      capacity_;
    size_t      size_;   
    StackData_t *data_;
    int         rightCanary_;
}Stack;

struct Stack*   StackCtor(size_t cap);
int             StackDtor(Stack *stack);
int             StackPush(Stack *stack, StackData_t value);
int             StackReallocMemory(Stack *stack);
StackData_t     StackPop(Stack *stack);
StackErrors     StackOk(const Stack *stack);
StackErrors     StackDump(const Stack *stack, FILE* stream, char* Stack_name);
size_t          IsStackEmpty(const Stack *stack);
size_t          GetStackSize(const Stack *stack);
size_t          GetStackCapacity(const Stack *stack);
int             StackClear(Stack *stack);

#endif
