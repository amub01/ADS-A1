// in-out.h - I/O functions, chains to data.h
#include "data.h"

// I/O FUNCTION PROTOTYPES //
void print_results(node_ptr node);
void print_node(FILE *output, node_ptr node, dataset_t *titles);
node_ptr store_dataset(FILE *data, node_ptr node, int *ncells);
void readin_addresses(FILE *input, FILE *output, node_ptr node,
                      int *matches, dataset_t *titles, char *input_address);
void store_header(FILE *data, dataset_t *titles);