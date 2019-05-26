#include "skipped_list.h"

#include <stdio.h>

// Print information of the node that has given value.
// Call find function for find the proper node.
void print_found_node(FILE* output, Skip_node* header, int value)
{
    Skip_node* node_temp = find(header, value);
    if(!node_temp) {
        fprintf(output ,"There isn't %d.\n", value);
        return;
    }
    int i;
    fprintf(output, "elem : %d, address : %p\n", node_temp->elem, node_temp);
    for(i = 0; i <= node_temp->level; ++i) {
        fprintf(output, "next[%d] : %d\n", i, node_temp->forward[i]->elem);
    }
}

// print given skipped list's elements and levels
void print_skipped_list(FILE* output, Skip_node* header)
{
    fprintf(output, "header(%d)\n", header->level);
    header = header->forward[0];
    for(; header->forward; header = header->forward[0]) {
        fprintf(output, "%d(%d)\n", header->elem, header->level);
    }
    fprintf(output, "tail(%d)\n", header->level);
}

int main()
{
    Skip_node* header;
    int temp_num;
    Skip_node* node_temp;
    char mode[2];
    int i;

    FILE* input = fopen("./sample/input.txt", "r");
    FILE* output = fopen("./sample/output.txt", "w");
    
    fscanf(input, "%d", &temp_num);
    header = make_empty_skipped_list(temp_num);

    while(fscanf(input, "%s", mode) == 1) {
        switch(mode[0]) {
            case 'i':
            {
                fscanf(input, "%d", &temp_num);
                insert(header, temp_num);
                break;
            }
            case 'd':
            {
                fscanf(input, "%d", &temp_num);
                delete(header, temp_num);
                break;
            }
            case 'f':
            {
                fscanf(input, "%d", &temp_num);
                print_found_node(output, header, temp_num);
                break;
            }
            case 'p':
            {
                print_skipped_list(output, header);
                break;
            }
        }
    }
    delete_skipped_list(header);
    fclose(input);
    fclose(output);
    return 0;
}
