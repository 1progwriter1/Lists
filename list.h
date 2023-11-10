#ifndef LIST_LISTS
#define LIST_LISTS

#include "list_values.h"

int ListCtor(List *lst);
int ListDtor(List *lst);
int ListInsertAfter(List *lst, const List_t number, int position);
int ListDump(List *lst, const unsigned long error);
int ListRandFill(List *lst, const int min, const int max);
int ListDelete(List *lst, const int position);
int ListInsertBefore(List *lst, const List_t number, int position);
int PrintList(List *lst);

#endif