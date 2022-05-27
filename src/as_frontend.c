#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "include/as_frontend.h"

char* as_f_compound(AST_T* ast) {
    char* value = calloc(1, sizeof(char));
    for (int i = 0; i < ast->children->size; i++) {
        AST_T* child_ast = (AST_T*) ast->children->items[i];
        char* next_value = as_f(child_ast);
        value = realloc(value, (strlen(next_value) + 1) * sizeof(char));
        strcat(value, next_value);
    }
    return value;
}
char* as_f_assignment(AST_T* ast) {
    char* s = calloc(1, sizeof(char));
    if (ast->value->type == AST_FUNCTION) {
        const char* template = ".globl _%s\n"
                                "_%s:\n"
                                "pushq %%rbp\n"
                                "movq %%rsp, %%rbp\n";

        s = realloc(s, (strlen(template) + (strlen(ast->name) * 2) + 1) * sizeof(char));
        sprintf(s, template, ast->name, ast->name);

        AST_T* as_val = ast->value;
        char* as_val_val = as_f(as_val->value);

        s = realloc(s, (strlen(s) + strlen(as_val_val) + 1) * sizeof(char));
        strcat(s, as_val_val);
    }
    return s;
}
char* as_f_variable(AST_T* ast, int id) {
    char* s = calloc(1, sizeof(char));
    if (ast->type == AST_INT) {
        const char* template = "$%d";
        s = realloc(s, (strlen(template) + 256) * sizeof(char));
        sprintf(s, template, ast->int_value);
    }
    else {
        const char* template = "%d(%%rsp)";
        s = realloc(s, (strlen(template) + 8) * sizeof(char));
        sprintf(s, template, id);
    }
    return s;
}
char* as_f_call(AST_T* ast) {
    char* s = calloc(1, sizeof(char));
    if (strcmp(ast->name, "return") == 0) {
        AST_T* first_arg = (AST_T*) ast->value->children->size ? ast->value->children->items[0] : (void*) 0;
        char* var_s = calloc(3, sizeof(char));
        var_s[0] = '$';
        var_s[1] = '0';
        var_s[2] = '\0';

        if (first_arg && first_arg->type == AST_VARIABLE) {
            char* as_var_s = as_f_variable(first_arg, 0);
            var_s = realloc(var_s, (strlen(as_var_s) + 1) * sizeof(char));
            strcpy(var_s, as_var_s);
            free(as_var_s);
        }

        const char* template = "movl %s, %%eax\n"
                               "movq %%rbp, %%rsp\n"
                               "popq %%rbp\n"
                               "ret\n";
        char* ret_s = calloc(strlen(template) + 128, sizeof(char));
        sprintf(ret_s, template, var_s);
        s = realloc(s, (strlen(ret_s) + 1) * sizeof(char));
        strcat(s, ret_s);
    }
    return s;
}
char* as_f_int(AST_T* ast) {
    
}

char* as_f_root(AST_T* ast) {
    const char* section_text = ".section .text\n"
                                ".globl main\n"
                                "main:\n"
                                //"pushq \%rbp\n"
                                //"movq \%rsp, \%rbp"
                                "subq $32, \%rsp\n"
                                "movl \%ecx, 0(\%rbp)\n"
                                //"movq \%rdx, 16(\%rbp)"

                                "call _main\n"

                                "addq $32, %rsp\n"
                                //"popq %rbp\n"
                                "ret\n\n"; //idek at this point. it saves argc and v i think?
    char* value = (char*) calloc((strlen(section_text) + 128), sizeof(char));
    strcpy(value, section_text);

    char* next_value = as_f(ast);
    value = (char*) realloc(value, (strlen(value) + strlen(next_value) + 1) * sizeof(char));
    strcat(value, next_value);

    return value;
}

char* as_f(AST_T* ast) {
    char* value = calloc(1, sizeof(char));
    char* next_value = 0;

    switch (ast->type) {
        case AST_COMPOUND: next_value = as_f_compound(ast); break;
        case AST_ASSIGNMENT: next_value = as_f_assignment(ast); break;
        case AST_VARIABLE: next_value = as_f_variable(ast, 0); break;
        case AST_CALL: next_value = as_f_call(ast); break;
        case AST_INT: next_value = as_f_int(ast); break;
        default: {
            printf("[As_Frontend]:No frontend for AST of type `%d`\n", ast->type); exit(1);
        } break;
    }

    value = realloc(value, (strlen(next_value) + 1) * sizeof(char));
    strcat(value, next_value);
    
    return value;
}