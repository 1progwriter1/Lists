#include <stdio.h>
#include "graphviz_gen.h"
#include "func.h"
#include <assert.h>
#include "list_values.h"
#include "systemdata.h"

int GenGraph(List *lst, const char *filename) {

    assert(lst);
    assert(filename);

    FILE *fn = fopen(filename, WRITE);

    fprintf(fn, "digraph G {\n\trankdir = LR\n\t");

    for (size_t i = 0; i < (size_t) lst->size; i++) {
        fprintf(fn, "%lu [shape = \"Msquare\", label = \"index: %lu\\nvalue: %d\\nnext: %d\\nprev: %d\", style = \"filled\", color = \"#CCCCFF\"]\n\t", i, i, lst->data[i], lst->next[i], lst->prev[i]);
    }
    fprintf(fn, "tail [shape = \"octagon\", style = filled, color = \"#CCFFE5\"]\n\thead [shape = \"octagon\", style = filled, color = \"#CCFFE5\"]\n\t");

    fprintf(fn, "head->%d\n\ttail->%d\n\t", lst->head, lst->tail);

    for (size_t i = 0; i < (size_t) lst->size; i++) {
        fprintf(fn, "%lu", i);
        if (i != (size_t) lst->size - 1)
            fprintf(fn, "->");
        else
            fprintf(fn, " [weight = 10000, color = \"#FFFFFF\"]\n\t");
    }

    int index = 0;
    fprintf(fn, "%d", index);
    do {
        index = lst->next[index];
        fprintf(fn, "->%d", index);
    } while (index != 0);
    fprintf(fn, " [weight = 1, constraint = false, penwidth = \"2\" ,color = \"#68CC00\"]\n\t");

    index = 0;
    fprintf(fn, "%d", index);
    do {
        index = lst->prev[index];
        fprintf(fn, "->%d", index);
    } while (index != 0);
    fprintf(fn, " [weight = 1, constraint = true ,color = \"#CC0000\"]\n\t");

    if (lst->free > 0) {
        index = lst->free;
        while (lst->prev[lst->next[index]] == -1) {
            fprintf(fn, "%d->", index);
            index = lst->next[index];
        }
        fprintf(fn, "%d", index);
        if (index != lst->free)
            fprintf(fn, " [weight = 1, constraint = false, color = \"#666600\"]\n\t");
    }

    fprintf(fn, "%d [shape = \"Msquare\", label = \"num_of_elements: %d\\nsize: %d\\nfree: %d\\nPOISON: %d\", style = \"filled\", color = \"#FFFF99\"]\n\t", -10, lst->num_of_elements, lst->size, lst->free, lst->data[0]);
    fprintf(fn, "}");

    fileclose(fn);

    system("dot Graphviz/graph.dot -T png -o Graphviz/graph.png");

    return SUCCESS;
}

int GenGraphPtr(ListNode *lst, const char *filename) {

    assert(lst);
    assert(filename);

    FILE *fn = fopen(filename, WRITE);

    fprintf(fn, "digraph G {\n\trankdir = LR\n\t");


    ListNode *ptr = lst;
    while (1) {
        if (ptr->prev)
            ptr = ptr->prev;
        else
            break;
    }
    size_t index = 0;
    while (ptr) {
        fprintf(fn, "%lu [shape = \"Msquare\", label = \"address: %p\\nvalue: " list_output_id "\\nnext: %p\\nprev = %p\", style = \"filled\", color = \"#CCFFCC\"]\n\t", index++, ptr, ptr->value, ptr->next, ptr->prev);
        ptr = ptr->prev;
    }

    ptr = lst;
    index = 0;
    while (ptr) {
        fprintf(fn, "%lu", index++);
        if (ptr->next)
            fprintf(fn, "->");
        ptr = ptr->next;
    }

    fprintf(fn, "\n}");

    fileclose(fn);

    system("dot Graphviz/graph2.dot -T png -o Graphviz/graph2.png");

    return SUCCESS;
}