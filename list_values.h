#ifndef LIST_VALUES_LISTS
#define LIST_VALUES_LISTS

#define graph_file "Graphviz/graph.dot"
#define graph_file_ptr "Graphviz/graph2.dot"
#define TAIL -5
#define HEAD -10

typedef int List_t;
#define list_output_id "%d"

const int POISON = -1e5;

struct List {
    List_t *data;
    int *next;
    int *prev;
    int head;
    int tail;
    int free;
    int num_of_elements;
    int size;
};

struct ListNode {
    List_t value;
    ListNode *next;
    ListNode *prev;
};

enum ListsErrors {
    NULL_DATA_PTR         = 1,
    INVALID_POSITION      = 1 << 1,
    INCORRECT_SIZE        = 1 << 2,
    INCORRECT_NUM_OF_ELEM = 1 << 3,
    INCORRECT_TAIL        = 1 << 4,
    INCORRECT_HEAD        = 1 << 5,
    INCORRECT_FREE        = 1 << 6,
    LIST_STRUCTURE_ERROR  = 1 << 7,
};

#endif
