#include <stdio.h>
#include "list.h"
#include "list_values.h"
#include "graphviz_gen.h"
#include "func.h"
#include "list_ptr.h"
#include <assert.h>

int main() {

    /* ListNode *lst = (ListNode *) calloc (1, sizeof (ListNode));
    //ListCtorPtr(lst, NULL, NULL, 10);
    lst->value = 10;
    ListNode *ptr = ListInsertAfterPtr(lst, 100);
    ptr = ListInsertAfterPtr(ptr, 250);
    // printf("%p %p ", lst->next, ptr->prev->next);
    ptr = ListInsertAfterPtr(ptr, 450);
    // printf("%p", ptr->prev->prev->next);
    ptr = ListInsertAfterPtr(ptr->prev->prev, 123);
    printf(list_output_id " ", ListDeletePtr(ptr->next));
    ListInsertBeforePtr(lst, 143);
    printf("%p", ptr);
    GenGraphPtr(lst, graph_file_ptr);

    ListDtorPtr(lst); */

    List lst = {};
    ListCtor(&lst);
    ListRandFill(&lst, 1, 100);
    ListDelete(&lst, 3);
    ListInsertAfter(&lst, 123, 7);
    GenGraph(&lst, graph_file);

    return 0;
}