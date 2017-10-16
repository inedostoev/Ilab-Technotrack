#include"Stack.h"

#define ASSERT_OK(stack);                               \
    if(StackOk(stack)) {                                \
        FILE *stream = fopen("StackDump", "w+");        \
        if(stream == NULL) {                            \
            printf("Can't open file StackDump\n");      \
            assert(0);                                  \
        }                                               \
        StackDump(stack, stdout, "stack");              \
        StackDump(stack, stream, "stack");              \
        fclose(stream);                                 \
        assert(!"Это фиаско, братан"); /*assert(0);*/   \
    }                                                   

struct Stack *StackCtor(size_t cap) {
    Stack *stack = (Stack*)calloc(1, sizeof(Stack));
    stack->leftCanary_ = leftCanary;
    stack->capacity_ = cap;
    stack->size_ = 0;
    stack->data_ = (StackData_t*)calloc(cap, sizeof(StackData_t));
    stack->rightCanary_ = rightCanary;
    ASSERT_OK(stack);
    for(size_t i = 0; i < cap; i++) {
        stack->data_[i] = -666;
    }
    return stack;
}

int StackDtor(Stack *stack){
    ASSERT_OK(stack);
    for(size_t i = 0; i < stack->capacity_; i++) {
        stack->data_[i] = -666;
    }
    free(stack->data_);
    stack->data_ = NULL;
    stack->leftCanary_ = 666;
    stack->rightCanary_ = 666;
    stack->capacity_ = 666;
    stack->size_ = 666;
    free(stack);
    return 0;
}

int StackPush(Stack *stack, StackData_t value) {
    ASSERT_OK(stack);
    if(stack->size_ > (stack->capacity_ - 1)) {
            StackReallocMemory(stack);
    }
    stack->data_[(stack->size_)++] = value;
    ASSERT_OK(stack);
    return 0;
}

int StackReallocMemory(Stack *stack) {
    ASSERT_OK(stack);
    stack->capacity_ += 10;
    stack->data_ = 
        (StackData_t*)realloc(stack->data_, stack->capacity_ * sizeof(StackData_t));
    ASSERT_OK(stack);
    for(size_t i = stack->capacity_ - 10; i < stack->capacity_; i++) {
        stack->data_[i] = -666;
    }
    ASSERT_OK(stack);
    return 0;
}

StackData_t StackPop(Stack *stack){
    ASSERT_OK(stack);
    if(stack->size_ == 0) {
        printf("Error: stack underflow\n"); 
        exit(STACK_UNDERFLOW);
    }
    else {
        stack->size_--;
        StackData_t value = stack->data_[stack->size_];
        stack->data_[stack->size_] = -666;
        ASSERT_OK(stack);
        return value;
    }
}

StackErrors StackOk(const Stack *stack) {
    if(stack == NULL) {
        return STACK_NULL_PTR;
    }
    else if(stack->data_ == NULL) {
        return STACK_NULL_DATA_PTR;
    }
    else if(stack->capacity_ <= 0) {
        return STACK_WRONG_CAPACITY;
    }
    else if(stack->size_ < 0 || stack->size_ > stack->capacity_) {
        return STACK_WRONG_COUNT;
    }
    else if(stack->leftCanary_ != leftCanary || 
            stack->rightCanary_ != rightCanary) {
        return STACK_SPOILED;
    }
    else return STACK_OK;
}

StackErrors StackDump(const Stack *stack, FILE* stream, char* Stack_name) {
    StackErrors Error = StackOk(stack);
    if(Error == STACK_NULL_PTR) {
        fprintf(stream, "Stack pointer = NULL\n");
        return Error;
    }
    if(Error == STACK_SPOILED) {
        fprintf(stream, "Stack was spoiled\n");
        return Error;
    }
    fprintf(stream, "Stack '%s' ", Stack_name); 
    fprintf(stream, !StackOk(stack) ? "(Ok)\n" : "(NotOk)\n");
    fprintf(stream, "{\n");
    if(Error == STACK_WRONG_COUNT || Error == STACK_WRONG_CAPACITY) {
        fprintf(stream, "\tcapacity_ = %zu\n", stack->capacity_); 
        fprintf(stream, "\tsize_ = %zu\n", stack->size_);
        return Error;
    }
    fprintf(stream, "\tcapacity_ = %zu\n", stack->capacity_); 
    fprintf(stream, "\tsize_ = %zu\n", stack->size_);
    if(Error == STACK_NULL_DATA_PTR) {
        fprintf(stream, "\tdata_[%p]\n\t{\n", stack->data_);
    } 
    else {
        fprintf(stream, "\tdata_[%p]\n"
                        "\t{\n", stack->data_);
	    for (size_t i = 0; i < stack->size_; i++) {
		    fprintf(stream, "\t* [%zu] %lg\n", i, stack->data_[i]);
	    }
	    for (size_t i = stack->size_; i < stack->capacity_; i++) {
            fprintf(stream, "\t  [%zu] %lg  POISON!\n", i, stack->data_[i]);
	    }
    }
    fprintf(stream, "\t}\n" 
                    "}\n");
    return Error;
}

size_t IsStackEmpty(const Stack *stack) {
    ASSERT_OK(stack);
    if(stack->size_ == 0) {
        return 1;
    }
    else return 0;
}

size_t GetStackSize(const Stack *stack) {
    ASSERT_OK(stack);
    return stack->size_;
}

size_t GetStackCapacity(const Stack *stack) {
    ASSERT_OK(stack);
    return stack->capacity_;
}

int StackClear(Stack *stack) {
    ASSERT_OK(stack);
    for(size_t i = 0; i < stack->size_; i++) {
        stack->data_[i] = -666;
    }
    stack->size_ = 0;
    ASSERT_OK(stack);
    return 0;
}
