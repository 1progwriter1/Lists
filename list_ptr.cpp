#include <stdio.h>
#include "list_ptr.h"
#include <assert.h>
#include "systemdata.h"
#include "list_values.h"
#include "func.h"

int ListCtorPtr(ListNode *lst, ListNode *next, ListNode *prev, const List_t number) {

    assert(lst);

    lst = (ListNode *) calloc (1, sizeof (ListNode));
    if (!lst)
        return NO_MEMORY;
    lst->value = number;
    lst->next = next;
    lst->prev = prev;

    return SUCCESS;
}

int ListDtorPtr(ListNode *lst) {

    assert(lst);

    ListNode *ptr = lst;
    ListNode *tmp = NULL;
    while (1)
        if (ptr->prev)
            ptr = ptr->prev;
        else
            break;

    while (ptr) {
        tmp = ptr;
        ptr = ptr->next;
        free(tmp);
    }

    return SUCCESS;
}

ListNode *ListInsertAfterPtr(ListNode *lst, const List_t number) {

    assert(lst);

    if (!lst->next) {
            lst->next = (ListNode *) calloc (1, sizeof (ListNode));
            if (!lst->next)
                return NULL;
        lst->next->prev = lst;
        lst->next->next = NULL;
        lst->next->value = number;
        return lst->next;
    }

    ListNode *ptr = (ListNode *) calloc (1, sizeof (ListNode));
    if (!ptr)
        return NULL;
    ptr->value = number;
    ptr->prev = lst;
    ptr->next = lst->next;
    lst->next->prev = ptr;
    lst->next = ptr;

    return lst->next;
}

List_t ListDeletePtr(ListNode *lst) {

    assert(lst);

    if (!lst->prev) {
        printf(RED "Incorrect address to delete" END_OF_COLOR "\n");
        return NULL;
    }

    List_t value = 0;
    if (lst->next) {
        lst->prev->next = lst->next;
        lst->next->prev = lst->prev;
        value = lst->value;
        free(lst);
    }
    else {
        lst->prev->next = NULL;
        value = lst->value;
        free(lst);
    }

    return value;
}

ListNode *ListInsertBeforePtr(ListNode *lst, const List_t number) {

    assert(lst);

    if (!lst->prev) {
        lst->prev = (ListNode *) calloc (1, sizeof (ListNode));
        if (!lst->prev)
            return NULL;
        lst->prev->next = lst;
        lst->prev->prev = NULL;
        lst->prev->value = number;

        return lst->prev;
    }

    ListNode *ptr = (ListNode *) calloc (1, sizeof (ListNode));
    if (!ptr)
        return NULL;
    ptr->prev = lst->prev;
    lst->prev->next = ptr;
    lst->prev = ptr;
    ptr->next = lst;
    ptr->value = number;

    return lst->prev;
}