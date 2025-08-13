
// INCLUDES //
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// DEFINES //
#define MAXCOLS 35 // number of columns in the input data
#define MAXSTR_LEN 128 //including the carriage return

// STRUCTS //
typedef struct {
    char   *data[MAXCOLS];
    
} dataset_t;

//Hello

//looks messy because a typedef doesn't work for a self-referencing struct,
//              the struct layout is from W3 lecture slides.
typedef struct node_t node_t;
typedef node_t* node_ptr;
struct node_t {  
    dataset_t loctn;
    node_ptr   next;
    int      ncells;
  
};

typedef struct {
    int     num;
    char   *street_suburb[MAXSTR_LEN];
    int     postcode;

} address_t;

typedef struct addnode_t addnode_t;
typedef addnode_t* addnode_ptr;

struct addnode_t{
    char *EZY_ADD[MAXSTR_LEN];
    addnode_ptr next;
    
};

// PROTOTYPES //
void skip_header(FILE *data);
node_ptr init_node();
node_ptr store_dataset(FILE *data, node_ptr node);

addnode_ptr init_addnode();
void print_results(node_ptr node);
void read_address(addnode_ptr input);

int main(int argc, char *argv[]){
    // Make sure that there is at least an input & output file
    assert(argc > 3);
    

    //open the dataset & the output file and make sure they opened correctly
    FILE *data = fopen(argv[2], "r");
    FILE *output = fopen(argv[3], "w");
    assert(data != NULL); // && (output != NULL));

    //skip the first row of the csv files, from W2.6 Workshops
    skip_header(data);

    //setup the first node in the linked list
    node_ptr head = init_node();

    //store the data as a linked list
    store_dataset(data, head);

    //store the addresses from the command line
    addnode_ptr first = init_addnode();

    //print out the input ***DEBUGGING*****
    printf("the input is:\n");
    print_results(head);


    fclose(data);
    fclose(output);
    return 0;
}

//initalises the nodes of the linked list;
node_ptr
init_node(){
    return malloc(sizeof(node_t));
    
}

addnode_ptr
init_addnode(){
    return malloc(sizeof(addnode_t));
}
//writes the input data into a linked list of arrays that can be indexed to find details
node_ptr 
store_dataset(FILE *data, node_ptr node){

    //storing each row from input as its own node
    for(int counter = 0; counter < MAXCOLS; counter++){

        node->loctn.data[counter] = malloc(MAXSTR_LEN * sizeof(char));

        if(counter < MAXCOLS - 1){ 
            // Read until comma or empty field
            char c = fgetc(data);
            if(c == ',') {
                // Empty field case
                node->loctn.data[counter][0] = '\0';
            } else {
                // Start building the field with the first character
                int pos = 1;
                while(c != ',' && c != EOF) {
                    node->loctn.data[counter][pos] = c;
                    c = fgetc(data);
                    pos++;
                }
                // Null terminate the string
                node->loctn.data[counter][pos] = '\0';
            }
        } else {
            // for last column read until end of line
            char c = fgetc(data);
            int pos = 0;
            while(c != '\n' && c != EOF) {
                node->loctn.data[counter][pos++] = c;
                c = fgetc(data);
            }
            node->ncells++;
            node->loctn.data[counter][pos] = '\0';
        }

    }
    //check if there is a next line
    int nextchar = fgetc(data);
    if(nextchar != EOF){
        //put the character back so it can be stored
        ungetc(nextchar,data);
        node->next = store_dataset(data, init_node());
    } else {
        //if EOF return NULL
        node->next = NULL;
    }

    return node;
}

//stores the addresses from command line into a linked list
void read_address(addnode_ptr input){

    

}

//print out the relevant lines of the dataset
void
print_results(node_ptr node){

    for (int i = 0; i < MAXCOLS; i++){
        printf("%s|",node->loctn.data[i]);
    }
    printf("\n");
    if(node->next != NULL){
        print_results(node->next);
    }
}

//read the addresses in the command line

//skips the header line in the input csv files
void 
skip_header(FILE *data){
    while (fgetc(data) != '\n');
}

int
name_comp(node_ptr head, 


)

