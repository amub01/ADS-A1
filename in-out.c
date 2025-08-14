#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "in-out.h"  // This includes data.h automatically

// prints each cell of the node into the output file
void print_node(FILE *output, node_ptr node, dataset_t *titles)
{
    fprintf(output, "--> ");

    for (int i = 0; i < MAXCOLS; i++)
    {
        fprintf(output, " %s: %s ||", titles->data[i], node->loctn.data[i]);
    }

    fprintf(output, "\n");
}

void readin_addresses(FILE *input, FILE *output, node_ptr node, int *matches,
                      dataset_t *titles, char input_address[])
{
    while (fgets(input_address, MAXSTR_LEN, stdin) != NULL)
    {

        input_address[strcspn(input_address, "\n")] = '\0';

        printf("%s", input_address);
        fprintf(output, "%s", input_address);

        listSearch(node, input_address, matches, output, titles);
    }
}

void store_header(FILE *data, dataset_t *titles)
{

    for (int counter = 0; counter < MAXCOLS; counter++)
    {
        titles->data[counter] = malloc(MAXSTR_LEN * sizeof(char));

        char c = fgetc(data);
        int pos = 0;

        while (c != ',' && c != '\n' && c != EOF && pos < MAXSTR_LEN - 1)
        {
            titles->data[counter][pos] = c;
            c = fgetc(data);
            pos++;
        }

        titles->data[counter][pos] = '\0';

        // reused from store_dataset :P
        char *trimmed = realloc(titles->data[counter], (pos + 1) * sizeof(char));
        if (trimmed != NULL)
        {
            titles->data[counter] = trimmed;
        }

        if (c == '\n' || c == EOF)
        {
            break;
        }
    }

    return;
}

node_ptr
store_dataset(FILE *data, node_ptr node, int *ncells)
{

    (*ncells)++;
    // storing each row from input as its own node
    for (int counter = 0; counter < MAXCOLS; counter++)
    {

        node->loctn.data[counter] = malloc(MAXSTR_LEN * sizeof(char));

        if (counter < MAXCOLS - 1)
        {
            // Read until comma or empty field
            char c = fgetc(data);
            if (c == ',')
            {
                // Empty field case
                node->loctn.data[counter][0] = '\0';
            }
            else
            {
                // Start building the field with the first character
                int pos = 0;
                while (c != ',' && c != EOF)
                {
                    node->loctn.data[counter][pos] = c;
                    c = fgetc(data);
                    pos++;
                }
                // Null terminate the string
                node->loctn.data[counter][pos] = '\0';
                // realloc to trim node size
                node->loctn.str_len[counter] = strlen(node->loctn.data[counter]);
                char *trimmed = realloc(node->loctn.data[counter], (pos + 1) * sizeof(char));
                if (trimmed != NULL)
                {
                    node->loctn.data[counter] = trimmed;
                }
            }
        }
        else
        {
            // for last column read until end of line
            char c = fgetc(data);
            int pos = 0;
            while (c != '\n' && c != EOF)
            {
                node->loctn.data[counter][pos] = c;
                pos++;
                c = fgetc(data);
            }
            node->loctn.data[counter][pos] = '\0';
        }
    }
    // check if there is a next line
    int nextchar = fgetc(data);
    if (nextchar != EOF)
    {
        // put the character back so it can be stored
        ungetc(nextchar, data);
        node->next = store_dataset(data, init_node(), ncells);
    }
    else
    {
        // if EOF return NULL
        node->next = NULL;
    }

    return node;
}