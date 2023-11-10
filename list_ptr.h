#ifndef LIST_PTR_LISTS
#define LIST_PTR_LISTS

#include "list_values.h"

int ListCtorPtr(ListNode *lst, ListNode *next, ListNode *prev, const List_t number);
int ListDtorPtr(ListNode *lst);
ListNode *ListInsertAfterPtr(ListNode *lst, const List_t number);
List_t ListDeletePtr(ListNode *lst);
ListNode *ListInsertBeforePtr(ListNode *lst, const List_t number);

#endif
