#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "Stack.h"

#define DUMP(file,Stack_name);							\
{														\
	assert(strlen(#Stack_name) < MAX_LENGTH);			\
	StackDump(Stack_name, file, #Stack_name);    \
}

int main() {
    Stack *s = StackCtor(3);
    for (int i = 0; i < 7; i++) {
		StackPush(s, i + 10);
	}
	if (IsStackEmpty(s)) {
		printf("The stack is empty.\n");
	}
	else {
		printf("The stack is not empty.\n");
	}

    DUMP(stdout, s);
	FILE* stream = fopen("StackDump", "w+");
	DUMP(stream, s);

    double c = StackPop(s);

    DUMP(stdout, s);
	DUMP(stream, s);

	for (int i = 1; i < 7; i++) {
		StackPop(s);
	}

    DUMP(stdout, s);
	DUMP(stream, s);

    StackDtor(s);
	return 0;

}

#undef DUMP
