#include <stdlib.h>
#include <string.h>
#include "include/ms.h"
#include "lexer.c"
#include "parser.c"
#include "io.c"
#include "as_frontend.c"

static char* sh(char* cmd) { //Runs commands
    char* output = (char*) calloc(1, sizeof(char));
    output[0] = '\0';

    FILE* fp;
    char path[1035];

    fp = popen(cmd, "r");

    if (fp == NULL) {
        printf("Failed to run command\n");
        exit(1);
    }

    while (fgets(path, sizeof(path), fp) != NULL) {
        output = (char*) realloc(output, (strlen(output) + strlen(path) + 1) * sizeof(char));
        strcat(output, path);
    }

    pclose(fp);
    return output;
}

void ms_compile(char* src) {
    lexer_T* lexer = init_lexer(src);
    parser_T* parser = init_parser(lexer);
    AST_T* root = parser_parse(parser);

    char* s = as_f_root(root);

    ms_write_file("main.s", s);
    //ms_write_file("a.s.txt", s);
    sh("gcc main.s -o ms.exe");
}

void ms_compile_file(const char* filename) {
    char* src = ms_read_file(filename);
    ms_compile(src);
    free(src);
}