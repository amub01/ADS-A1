
// WHAT IS LEFT TO DO?????? //
// - the b, n, and c comparison counting
// - freeing all the memory
// i think thats it :3

// Run command: ./ass1 1 dataset_22.csv output.txt <  test22.in

// INCLUDES //
#include <assert.h>  // Only for assert, not in the chain
#include "in-out.h"  // This chains to data.h, bringing in all definitions

// PROTOTYPES //

int main(int argc, char *argv[])
{
    // Make sure that there is at least an input & output file
    assert(argc > 3);

    // open the dataset & the output file and make sure they opened correctly
    FILE *data = fopen(argv[2], "r");
    FILE *output = fopen(argv[3], "w");
    assert(data != NULL); // && (output != NULL));

    // Create a dataset structure for the header titles
    dataset_t titles;

    // store the first row of the csv files, from W2.6 Workshops
    store_header(data, &titles);

    // setup the first node in the linked list
    node_ptr head = init_node();

    // store the data as a linked list
    int ncells = 0;
    store_dataset(data, head, &ncells);
    // need to use a temp variable for the recursive function
    head->ncells = ncells;

    char input_address[MAXSTR_LEN];
    int matches;
    readin_addresses(data, output, head, &matches,
                     &titles, input_address);

    // free & close stuff
    free_nodes(head);
    free_header(&titles);
    fclose(data);
    fclose(output);
    return 0;
}
