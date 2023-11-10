#include <stdio.h>
#include "list.h"
#include "systemdata.h"
#include <assert.h>
#include "list_values.h"
#include "func.h"

static const int START_SIZE = 8;
const int INCREASE = 2;

static int ResizeUp(List *lst);
static unsigned long ListVerify(List *lst);
static bool CorrectList(List *lst);
static int CheckPosition(List *lst, int position);
static int PrepareToInsert(List *lst, int *position);
static void DumpErrors(const unsigned long error);

int ListCtor(List *lst) {

    assert(lst);

    lst->size = START_SIZE;

    lst->data = (int *) calloc (START_SIZE, sizeof (int));
    lst->next = (int *) calloc (START_SIZE, sizeof (int));
    lst->prev = (int *) calloc (START_SIZE, sizeof (int));
    if (!lst->data || !lst->next || !lst->prev)
        return NO_MEMORY;

    for (size_t i = 0; i < (size_t) lst->size; i++) {
        if (i == 0) {
            lst->prev[i] = 0;
            lst->next[i] = 0;
        }
        else {
            if (i == (size_t) lst->size - 1)
                lst->next[i] = 0;
            else
                lst->next[i] = (int) i + 1;
            lst->prev[i] = -1;
        }
    }

    lst->data[0] = POISON;

    lst->head = 0;
    lst->tail = 0;
    lst->free = 1;
    lst->num_of_elements = 0;

    return SUCCESS;
}

int ListDtor(List *lst) {

    assert(lst);

    free(lst->data);
    free(lst->next);
    free(lst->prev);

    lst->head = -1;
    lst->tail = -1;
    lst->free = -1;
    lst->num_of_elements = -1;

    return SUCCESS;
}

int ListInsertAfter(List *lst, const List_t number, int position) {

    assert(lst);

    unsigned long error = ListVerify(lst);
    if (error) {
        ListDump(lst, error);
        return -1;
    }

    if (PrepareToInsert(lst, &position) != SUCCESS)
        return -1;

    int index = lst->free;
    if (lst->num_of_elements + 1 < lst->size - 1)
        lst->free = lst->next[lst->free];
    else
        lst->free = -1;

    lst->data[index] = number;
    lst->next[index] = lst->next[position];
    lst->prev[index] = position;

    lst->next[position] = index;
    lst->prev[lst->next[index]] = index;
    lst->num_of_elements++;

    if (position == lst->tail)
        lst->tail = index;
    if (lst->head == 0)
        lst->head = index;

    return index;
}

int ListInsertBefore(List *lst, const List_t number, int position) {

    assert(lst);

    unsigned long error = ListVerify(lst);
    if (error) {
        ListDump(lst, error);
        return -1;
    }

    if (PrepareToInsert(lst, &position) != SUCCESS)
        return -1;

    if (position < 1) {
        printf(RED "Incorrect index to insert" END_OF_COLOR ": %d\n", position);
        return -1;
    }

    int index = lst->free;
    if (lst->num_of_elements + 1 < lst->size - 1)
        lst->free = lst->next[lst->free];
    else
        lst->free = -1;

    lst->data[index] = number;
    lst->next[index] = position;
    lst->prev[index] = lst->prev[position];

    lst->next[lst->prev[position]] = index;
    lst->prev[position] = index;
    lst->num_of_elements++;

    if (position == lst->head)
        lst->head = index;

    return index;
}

List_t ListDelete(List *lst, const int position) {

    assert(lst);

    unsigned long error = ListVerify(lst);
    if (error) {
        ListDump(lst, error);
        return POISON;
    }

    if (position < 1 || lst->prev[position] == -1) {
        printf(RED "Incorrect index to delete" END_OF_COLOR ": %d\n", position);
        return POISON;
    }

    lst->next[lst->prev[position]] = lst->next[position];
    lst->prev[lst->next[position]] = lst->prev[position];
    if (lst->free >= 0)
        lst->next[position] = lst->free;
    lst->free = position;
    lst->prev[position] = -1;
    lst->num_of_elements--;

    lst->head = lst->next[0];
    lst->tail = lst->prev[0];

    return lst->data[position];
}

static unsigned long ListVerify(List *lst) {

    if (!lst)
        return NULL_POINTER;

    unsigned long error = 0;

    if (!lst->data || !lst->next || !lst->prev) {
        error |= NULL_DATA_PTR;
    }
    if (lst->head < 0) {
        error |= INCORRECT_HEAD;
    }
    if (lst->tail < 0) {
        error |= INCORRECT_TAIL;
    }
    if (lst->size < 0) {
        error |= INCORRECT_SIZE;
    }
    if (lst->free < -1) {
        error |= INCORRECT_FREE;
    }
    if (lst->num_of_elements < 0) {
        error |= INCORRECT_NUM_OF_ELEM;
    }

    if (!error) {
        if (!CorrectList(lst))
            error |= LIST_STRUCTURE_ERROR;
    }
    return error;
}

static void DumpErrors(const unsigned long error) {

    #define ERR_(code)  case code: {                          \
                            printf("%d (%s), ", code, #code); \
                            break;                            \
                            }                                 \

    unsigned long err_num = 1;
    printf("ERRORS CODES: ");
    for (size_t i = 0; i < sizeof (unsigned long); i++) {
        if ((error & err_num) != 0)
            switch (err_num) {
                ERR_(NULL_DATA_PTR)
                ERR_(INVALID_POSITION)
                ERR_(INCORRECT_SIZE)
                ERR_(INCORRECT_NUM_OF_ELEM)
                ERR_(INCORRECT_TAIL)
                ERR_(INCORRECT_HEAD)
                ERR_(INCORRECT_FREE)
                ERR_(LIST_STRUCTURE_ERROR)
            }
        err_num *= 2;
    }
    printf("\b\n");
    #undef ERR_
}

static bool CorrectList(List *lst)  {

    assert(lst);
    if (lst->tail == lst->head) {
        if (lst->num_of_elements <= 1)
            return 1;
        printf(RED "List structure is incorrect" END_OF_COLOR "\n");
        return 0;
    }

    int index = lst->head;
    int num_of_elem = 1;
    while (lst->next[index] != 0) {
        num_of_elem++;
        index = lst->next[index];
    }
    if (num_of_elem != lst->num_of_elements) {
        printf(RED "List structure is incorrect" END_OF_COLOR ". num_of_elem: %d, \n", num_of_elem);
        return 0;
    }

    return 1;
}

int ListDump(List *lst, const unsigned long error) {

    if (!lst) {
        printf("NULL POINTER. Unable to print list\n");
        return NULL_POINTER;
    }

    DumpErrors(error);

    if (lst->data && lst->next && lst->prev) {
        printf(BRIGHT_CYAN "data" END_OF_COLOR ": %p\n" BRIGHT_CYAN "next" END_OF_COLOR ": %p\n" BRIGHT_CYAN "prev" END_OF_COLOR ": %p\n" BRIGHT_GREEN "head" END_OF_COLOR ": %d, " BRIGHT_GREEN "tail" END_OF_COLOR ": %d, " BRIGHT_GREEN "free" END_OF_COLOR ": %d, " BRIGHT_GREEN "number of elements" END_OF_COLOR ": %d, " BRIGHT_GREEN "size" END_OF_COLOR ": %d\n\n", lst->data, lst->next, lst->prev, lst->head, lst->tail, lst->free, lst->num_of_elements, lst->size);

        printf(YELLOW "index" END_OF_COLOR ": |");
        for (size_t i = 0; i < (size_t) lst->size; i++)
            printf("%7lu|", i);

        printf("\n" BRIGHT_CYAN " data" END_OF_COLOR ": |");
        for (size_t i = 0; i < (size_t) lst->size; i++)
            printf("%7d|", lst->data[i]);

        printf("\n" BRIGHT_CYAN " next" END_OF_COLOR ": |");
        for (size_t i = 0; i < (size_t) lst->size; i++)
            printf("%7d|", lst->next[i]);

        printf("\n" BRIGHT_CYAN " prev" END_OF_COLOR ": |");
        for (size_t i = 0; i < (size_t) lst->size; i++)
            printf("%7d|", lst->prev[i]);

        printf("\n\n");
    }
    else {
        printf(RED "NULL POINTER. Unable to print list" END_OF_COLOR "\n");
        return NULL_POINTER;
    }

    return SUCCESS;
}

int ListRandFill(List *lst, const int min, const int max) {

    assert(lst);
    unsigned long error = ListVerify(lst);
    if (error) {
        ListDump(lst, error);
        return ERROR;
    }

    for (size_t i = 0; i < (size_t) lst->size; i++) {
        if (i != 0)
            lst->data[i] = randnum(min, max);
        if ((int) i != lst->size - 1) {
            lst->next[i] = (int) i + 1;
        }
        else {
            lst->next[i] = 0;
        }
        if ((int) i > 0)
            lst->prev[i] = (int) i - 1;
    }
    lst->head = 1;
    lst->num_of_elements = 7;
    lst->tail = lst->size - 1;
    lst->free = -1;
    lst->prev[0] = lst->tail;

    return SUCCESS;
}

static int ResizeUp(List *lst) {

    assert(lst);

    unsigned long error = ListVerify(lst);
    if (error) {
        ListDump(lst, error);
        return ERROR;
    }

    lst->data = (int *) realloc (lst->data, (unsigned long) lst->size * INCREASE * sizeof (int));
    lst->next = (int *) realloc (lst->next, (unsigned long) lst->size * INCREASE * sizeof (int));
    lst->prev = (int *) realloc (lst->prev, (unsigned long) lst->size * INCREASE * sizeof (int));
    if (!lst->data | !lst->next || !lst->prev)
        return NO_MEMORY;
    for (size_t i = (size_t) lst->size; i < (size_t) lst->size * INCREASE; i++) {
        lst->data[i] = 0;
        lst->prev[i] = -1;
    }
    lst->next[lst->size * INCREASE - 1] = lst->free;
    lst->free = lst->size;
    for (size_t i = (size_t) lst->size; i < (size_t) lst->size * INCREASE - 1; i++)
        lst->next[i] = (int) i + 1;
    lst->size *= INCREASE;

    return SUCCESS;
}

static int CheckPosition(List *lst, int position) {

    assert(lst);

    if (position == TAIL) {
        position = lst->tail;
        return position;
    }
    if (position == HEAD) {
        position = lst->head;
        return position;
    }
    if (position >= lst->size || position < 1 || lst->prev[position] == -1) {
        printf(RED "Incorrect index to insert" END_OF_COLOR ": %d\n", position);
        return -1;
    }
    return position;

}

static int PrepareToInsert(List *lst, int *position) {

    assert(lst);
    assert(position);

    unsigned long error = ListVerify(lst);
    if (error) {
        ListDump(lst, error);
        return ERROR;
    }

    if ((*position = CheckPosition(lst, *position)) == -1)
        return ERROR;

    if (lst->num_of_elements + 1 >= lst->size)
        if (ResizeUp(lst) != SUCCESS)
            return ERROR;

    return SUCCESS;
}

int PrintList(List *lst) {

    assert(lst);

    unsigned long error = ListVerify(lst);
    if (error) {
        ListDump(lst, error);
        return ERROR;
    }

    int real_index = lst->head;
    int index = 0;
    do {
        printf("%d) " MAGENTA "%d " END_OF_COLOR, index++, lst->data[real_index]);
        real_index = lst->next[real_index];
    } while (real_index != 0);

    return SUCCESS;
}
