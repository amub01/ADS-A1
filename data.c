// data.c - Data manipulation functions
#include <stdlib.h>
#include <string.h>
#include "data.h"

void listSearch(node_ptr head, char *in_address, int *matches,
                FILE *output, dataset_t *titles)
{
    // Reset the comparison counter to 0
    *matches = 0;

    node_ptr curr_node = head;

    while (curr_node)
    {
        if (!strcmp(curr_node->loctn.data[1], in_address))
        {
            (*matches)++;
            print_node(output, curr_node, titles);

            // break;
        }
        curr_node = curr_node->next;
    }
    ////  NEED TO FIND A PROPER FIX FOR THIS ////
    printf(" --> %d records found -", *matches);
    printf("comparisons: b... n%d s%d\n", head->ncells, head->ncells);
}

// frees the nodes of the linked list
void free_nodes(node_ptr node)
{

    if (node->next == NULL)
    {
        for (int i = 0; i < MAXCOLS; i++)
        {
            free(node->loctn.data[i]);
        }
        free(node);
    }
    else
    {
        free_nodes(node->next);
    }
}

void free_header(dataset_t *titles)
{
    for (int i = 0; i < MAXCOLS; i++)
    {
        free(titles->data[i]);
    }
}

// initalises the nodes of the linked list;
node_ptr
init_node()
{
    return malloc(sizeof(node_t));
}