#include <stdio.h>
#include "ms.c"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Please specify input file.\n");
        return 1;
    }

    ms_compile_file(argv[1]);

    return 0;
}