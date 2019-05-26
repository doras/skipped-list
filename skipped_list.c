#include "skipped_list.h"
#include <stdlib.h>
#include <time.h>

static int is_initialized = 0;

// return 0 or 1, respectively, with 0.5 probability
int coin_flip()
{
    if (!is_initialized) {
        is_initialized = 1;
        srand(time(NULL));
    }

    return rand() % 2;
}

// dynamically allocate a Skip_node that has given value and level.
// forward of each node of search_result will replace to a new node.
Skip_node* make_empty_skip_node(int value, int level, Skip_node** search_result)
{
    Skip_node* new_node = malloc(sizeof(Skip_node));
    new_node->elem = value;
    new_node->level = level;
    new_node->forward = malloc(sizeof(Skip_node*) * (level + 1));

    return new_node;
}

// search the node that contains given value in given skipped list
// return the positions of the items that has the largest key less than given value in each level
// this function will return dynamically allocated array, therefore it needs deallocation.
Skip_node** search(Skip_node* header, int value)
{
    Skip_node** result = malloc(sizeof(Skip_node*) * (header->level + 1));
    int i;
    for(i = header->level; i >= 0; --i) {
        for(; header->forward[i]->forward && header->forward[i]->elem < value; header = header->forward[i]);
        result[i] = header;
    }
    return result;
}

// By calling coin_flip func, return an randomly generated integer that is from 0 to given max_level including both end.
int choose_level(int max_level)
{
    int count = 0;
    while(coin_flip()) ++count;

    if(count > max_level) return max_level;
    return count;
}


/*----------------------------------------------------------------------------------------------------------
  internal functions on the upper side                                  external functions on the lower side
  ----------------------------------------------------------------------------------------------------------*/


// dynamically allocate header node and tail node, return header node's address.
// max_level is 0-based value.
Skip_node* make_empty_skipped_list(int max_level)
{
    Skip_node* head = malloc(sizeof(Skip_node));
    Skip_node* tail = malloc(sizeof(Skip_node));

    head->level = max_level;
    head->forward = malloc(sizeof(Skip_node*) * (max_level + 1));

    tail->level = max_level;
    tail->forward = NULL;

    int i;
    for(i = 0; i <= max_level; ++i) {
        head->forward[i] = tail;
    }
    
    return head;
}

// deallocate the skipped list with given skipped list's header
void delete_skipped_list(Skip_node* node)
{
    Skip_node* temp;

    // while node is not tail
    while(node->forward) {
        temp = node;
        node = node->forward[0];
        free(temp->forward);
        free(temp);
    }
    free(node);
}

// insert a new node that contains given value to given Skipped_list
void insert(Skip_node* header, int value)
{
    Skip_node** search_result = search(header, value);
    int chosen_level = choose_level(header->level);
    Skip_node* new_node = make_empty_skip_node(value, chosen_level, search_result);

    int i;
    for(i = 0; i <= chosen_level; ++i) {
        new_node->forward[i] = search_result[i]->forward[i];
        search_result[i]->forward[i] = new_node;
    }

    free(search_result);
}

// delete node that has given value as element from given skipped list.
void delete(Skip_node* header, int value)
{
    Skip_node** search_result = search(header, value);
    Skip_node* target = search_result[0]->forward[0];

    if(target->elem != value) {
        free(search_result);
        return;
    }

    int i;
    for(i = 0; i <= target->level; ++i) {
        search_result[i]->forward[i] = target->forward[i];
    }

    free(target->forward);
    free(target);
    free(search_result);
}

// find the node that has given value as its element. And return its address.
Skip_node* find(Skip_node* header, int value)
{
    int i;
    Skip_node* temp = header;
    for(i = header->level; i >= 0; --i) {
        for(; temp->forward[i]->forward && temp->forward[i]->elem <= value; temp = temp->forward[i]);
        if(temp != header && temp->elem == value) return temp;
    }
    return NULL;
}
