#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef double StackData_t;
enum { MAX_LENGTH = 256 };  

enum StackErrors {
    STACK_OK,
    STACK_NULL_PTR,
    STACK_NULL_DATA_PTR,
    STACK_WRONG_CAPACITY,
    STACK_WRONG_COUNT,
    STACK_UNDERFLOW
};

typedef struct Stack {
 	StackData_t *data_;
	size_t	    capacity_;
	size_t	    size_;
}Stack;

struct Stack*   StackCtor(size_t cap);
void            StackDtor(Stack *stack);
void            StackPush(Stack *stack, StackData_t value);
void            StackReallocMemory(Stack *stack);
StackData_t     StackPop(Stack *stack);
StackErrors     StackOk(const Stack *stack);
void            StackDump(const Stack *stack, FILE* stream, char Stack_name[MAX_LENGTH]);
size_t          IsStackEmpty(const Stack *stack);
size_t          GetStackSize(const Stack *stack);
size_t          GetStackCapacity(const Stack *stack);
void            StackClear(Stack *stack);

#endif
