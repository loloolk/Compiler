#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/io.h"

ssize_t getline(char **lineptr, size_t *n, FILE *stream) { //Needed for ms_read_file
    size_t pos;
    int c;

    if (lineptr == NULL || stream == NULL || n == NULL) {
        errno = 22;
        return -1;
    }

    c = getc(stream);
    if (c == EOF) {
        return -1;
    }

    if (*lineptr == NULL) {
        *lineptr = malloc(128);
        if (*lineptr == NULL) {
            return -1;
        }
        *n = 128;
    }

    pos = 0;
    while(c != EOF) {
        if (pos + 1 >= *n) {
            size_t new_size = *n + (*n >> 2);
            if (new_size < 128) {
                new_size = 128;
            }
            char *new_ptr = realloc(*lineptr, new_size);
            if (new_ptr == NULL) {
                return -1;
            }
            *n = new_size;
            *lineptr = new_ptr;
        }

        ((unsigned char *)(*lineptr))[pos ++] = c;
        if (c == '\n') {
            break;
        }
        c = getc(stream);
    }

    (*lineptr)[pos] = '\0';
    return pos;
}
char* ms_read_file(const char* filename) {
    FILE* fp;
    char* line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen(filename, "rb");
    if (fp == NULL) {
        printf("Could not open file `%s`\n", filename);
        exit(1);
    }

    char* buffer =(char*) calloc(1, sizeof(char));
    buffer[0] = '\0';

    while ((read = getline(&line, &len, fp)) != -1) { //supposed to be getline
        buffer = (char*) realloc(buffer, strlen(buffer) + strlen(line) + 1 * sizeof(char));
        strcat(buffer, line);
    }

    fclose(fp);
    if (line) {
        free(line);
    }

    return buffer;
}

void ms_write_file(const char* filename, char* outbuffer) {
    FILE* fp;

    fp = fopen(filename, "wb"); 
    if (fp == NULL) {
        printf("Could not open `%s` for writing\n", filename);
        exit(1);
    }

    fputs(outbuffer, fp);
    
    fclose(fp);
}
