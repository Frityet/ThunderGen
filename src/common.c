//
// Created by Frityet on 2021-07-10.
//

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "common.h"

extern int errno;

int
throw_error(const char* msg, int exit_code)
{
    perror(msg);
    fprintf(stderr, "ERROR CODE: %d\n", errno);
    exit(exit_code);
    return 1;
}

char*
input_str(const char *msg)
{
    char *buffer = malloc(sizeof(char) * 256);
    printf("%s", msg);
    scanf("%s", buffer);
    return buffer;
}

char*
read_all_lines(const char *filepath)
{
    //I think the way I made this is sinking in memory leaks
    //but
    //I think it works???
    FILE *file = fopen(filepath, "w+");
    check_ptr(file);
    fseek(file, 0, SEEK_SET);
    size_t fsize = ftell(file);
    rewind(file);

    char *contents = malloc(sizeof(char) * fsize);
    fread(contents, 1, fsize, file);

    fclose(file);

    return contents;
}

char*
fread_all_lines(FILE *file)
{
    fseek(file, 0, SEEK_SET);
    size_t fsize = ftell(file);
    rewind(file);

    char *contents = malloc(sizeof(char) * fsize);
    fread(contents, 1, fsize, file);;

    return contents;
}

int
check_ptr(void *ptr)
{
    if (ptr == NULL) throw_error("Pointer is null", -1);
    else return 1;
    return 0;
}

int
free_ptr(void* ptr)
{
    free(ptr);
    ptr = NULL;
    return 0;
}
