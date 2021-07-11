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

void*
input(const char *format, const char *msg)
{
    void *buffer = malloc(sizeof(char) * 256);
    printf("%s", msg);
    scanf(format, buffer);
    return buffer;
}

char**
read_all_lines(const char *filepath, size_t max_lines, size_t line_len)
{
    //I think the way I made this is sinking in memory leaks
    //but
    //I think it works???
    FILE *file = fopen(filepath, "w+");

    if (file == NULL) throw_error("Could not read file", -1);

    fseek(file, 0, SEEK_SET);

    char **lines = malloc(sizeof(char**) * max_lines); //Generate a 2D array which will represent the lines of the file. We init the first dimension (the number of lines)
    if (lines == NULL) throw_error("Could not allocate memory", -1);

    lines[0] = malloc(sizeof(char*) * line_len);
    if (lines[0] == NULL) throw_error("Could not allocate memory", -1);
    int index = 0;
    while (fgets(lines[index], line_len, file))
    {


        ++index;
    }

    fclose(file);

    return lines;
}
