
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
void store_header(FILE *data, dataset_t *titles);
node_ptr init_node();
node_ptr store_dataset(FILE *data, node_ptr node, int *ncells);


void listSearch(node_ptr head, char *in_address, int *matches, FILE *output, dataset_t *titles);
void print_results(node_ptr node);
void print_node(FILE *output, node_ptr node, dataset_t *titles);

int main(int argc, char *argv[]){
    // Make sure that there is at least an input & output file
    assert(argc > 3);
    

    //open the dataset & the output file and make sure they opened correctly
    FILE *data = fopen(argv[2], "r");
    FILE *output = fopen(argv[3], "w");
    assert(data != NULL); // && (output != NULL));

    // Create a dataset structure for the header titles
    dataset_t titles;

    //store the first row of the csv files, from W2.6 Workshops
    store_header(data, &titles);

    //setup the first node in the linked list
    node_ptr head = init_node();
    int ncells = 0;

    //store the data as a linked list
    store_dataset(data, head, &ncells);

    //need to use a temp variable for the recursive function
     head->ncells = ncells;


    char input_address[MAXSTR_LEN];
    
    //read through & ignore the first line of command line
    int matches;
    while (fgets(input_address, MAXSTR_LEN, stdin)!=NULL) {

        input_address[strcspn(input_address, "\n")] = '\0';


        printf("%s", input_address);
        fprintf(output, "%s", input_address);
        listSearch(head, input_address, &matches, output, &titles);   
        }
    



    fclose(data);
    fclose(output);
    return 0;
}

//initalises the nodes of the linked list;
node_ptr
init_node(){
    return malloc(sizeof(node_t));
    
}

//writes the input data into a linked list of arrays that can be indexed to find details
node_ptr 
store_dataset(FILE *data, node_ptr node, int *ncells){

    (*ncells)++;
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
                int pos = 0;
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
                node->loctn.data[counter][pos] = c;
                pos++;
                c = fgetc(data);
            }
            node->loctn.data[counter][pos] = '\0';
        }

    }
    //check if there is a next line
    int nextchar = fgetc(data);
    if(nextchar != EOF){
        //put the character back so it can be stored
        ungetc(nextchar,data);
        node->next = store_dataset(data, init_node(), ncells);
    } else {
        //if EOF return NULL
        node->next = NULL;
    }

    return node;
}



//skips the header line in the input csv files
void 
store_header(FILE *data, dataset_t *titles) {

    for(int counter = 0; counter < MAXCOLS; counter++) {
        titles->data[counter] = malloc(MAXSTR_LEN * sizeof(char));

        char c = fgetc(data);
        int pos = 0;

        while (c != ',' && c != '\n' && c != EOF && pos < MAXSTR_LEN-1) {
            titles->data[counter][pos] = c;
            c = fgetc(data);
            pos++;
        }

        titles->data[counter][pos] = '\0';

        if (c == '\n' || c == EOF) {
            break;
        }
    }

    return;
}



void 
listSearch(node_ptr head, char *in_address, int *matches, FILE *output, dataset_t *titles) {
	// Reset the comparison counter to 0
	*matches = 0;
	
	node_ptr curr_node = head;
	
	while (curr_node) {
		if (!strcmp(curr_node->loctn.data[1], in_address)) {
            (*matches)++; 
    		print_node(output, curr_node, titles);
            
    		break;
		}
		curr_node = curr_node->next;
	}
    printf(" --> %d records found -",*matches);
    printf("comparisons: b... n%d s%d\n", head->ncells,head->ncells);

}

void 
print_node(FILE *output, node_ptr node, dataset_t *titles) {
    fprintf(output,"\n--> ");


    for (int i=0;i<MAXCOLS;i++) {
        fprintf(output," %s: %s ||", titles->data[i],node->loctn.data[i]);
    }

    fprintf(output,"\n");
}



