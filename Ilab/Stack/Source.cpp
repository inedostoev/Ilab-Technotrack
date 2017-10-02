#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "Stack.h"

#define DUMP(file,Stack_name);							\
{														\
	assert(strlen(#Stack_name) < MAX_LENGTH);			\
	Stack_name.dump(file,#Stack_name);				    \
}

int main()
{
	Stack ms(3);
	if (!ms.Ok()) {
		abort();
	}
	for (int i = 0; i < 7; i++) {
		ms.push(i + 10);
	}
	if (ms.empty()) {
		printf("The stack is empty.\n");
	}
	else {
		printf("The stack is not empty.\n");
	}
	ms.pop();

	DUMP(stdout, ms);
	FILE*  stream = fopen("dump.txt", "a");
	DUMP(stream, ms);
	fclose(stream);

	for (int i = 1; i < 7; i++) {
		ms.pop();
	}
	ms.~Stack();
	system("PAUSE");
	return 0;
}
#undef DUMP