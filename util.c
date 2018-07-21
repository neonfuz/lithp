#include <stdio.h>
#include <stdlib.h>
#include "util.h"

char *read_file(char *path)
{
        FILE *f = fopen(path, "r");
        fseek(f, 0, SEEK_END);
        size_t size = ftell(f);
        char *file = malloc(size+1);
        rewind(f);
        for(size_t i=0; i<size; ++i)
                file[i] = fgetc(f);
        file[size] = '\0';
        fclose(f);
        return file;
}
