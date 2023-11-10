#include <stdio.h>
#include <math.h>
#include "func.h"
#include <assert.h>
#include "systemdata.h"

int randnum(const int min, const int max) {
    return rand() % (max - min + 1) + min;
}

FILE *fileopen(const char *filename, const char mode[]) {

    assert(filename);

    FILE *fn = fopen(filename, mode);

    if (fn == nullptr)
        perror("");

    return fn;
}

void fileclose(FILE *fn) {

    assert(fn);

    if (fn != stdout)
        if (fclose(fn) != 0)
            fprintf(stderr, "File not closed\n");
}

void clean(const char *filename) {

    assert(filename);

    fileclose(fileopen(filename, WRITE));
}