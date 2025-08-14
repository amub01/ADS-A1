// data.h - Base header with all data structures and core functions
#include <stdio.h>

// DEFINES //
#define MAXCOLS 35     // number of columns in the input data
#define MAXSTR_LEN 128 // including the carriage return

// STRUCTS //
typedef struct dataset_s
{
    char *data[MAXCOLS];
    int str_len[MAXCOLS];
} dataset_t;

// looks messy because a typedef doesn't work for a self-referencing struct,
//               the struct layout is from W3 lecture slides.
typedef struct node_t node_t;
typedef node_t *node_ptr;
struct node_t
{
    dataset_t loctn;
    node_ptr next;
    int ncells;
};

typedef struct
{
    int num;
    char *street_suburb[MAXSTR_LEN];
    int postcode;
} address_t;

typedef struct addnode_t addnode_t;
typedef addnode_t *addnode_ptr;

struct addnode_t
{
    char *EZY_ADD[MAXSTR_LEN];
    addnode_ptr next;
};

// DATA MANIPULATION FUNCTIONS
void listSearch(node_ptr head, char *in_address, int *matches,
                FILE *output, dataset_t *titles);
void free_nodes(node_ptr node);
void free_header(dataset_t *title);
node_ptr init_node();

// I/O FUNCTION NEEDED BY DATA FUNCTIONS
void print_node(FILE *output, node_ptr node, dataset_t *titles);