#include <stdio.h>
#include <stdlib.h>
#include "CPU.h"
#include "./Stack/Stack.h"

int main() {
	FILE* binFile = fopen("./ASM/binFile", "rb");
    int i = execute(binFile);
    fclose(binFile);
	return 0;
}
