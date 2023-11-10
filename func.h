#ifndef FUNC_LISTS
#define FUNC_LISTS

int randnum(const int min, const int max);
FILE *fileopen(const char *filename, const char mode[]);
void fileclose(FILE *fn);
void clean(const char *filename);

#endif