#ifndef SYSTEM_DATA
#define SYSTEM_DATA

#define READ "r"
#define WRITE "w"
#define APPEND "a"

#define RED "\033[31m"
#define BRIGHT_GREEN "\033[92m"
#define YELLOW "\033[33m"
#define BRIGHT_CYAN "\033[96m"
#define MAGENTA "\033[35m"
#define END_OF_COLOR "\033[0m"

#define UNDERLINED "4"

enum SystemErrors {
    SUCCESS,
    ERROR,
    NULL_POINTER,
    NO_MEMORY,
};

#endif