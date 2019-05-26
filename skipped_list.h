#ifndef __SKIPPED_LIST_H__
#define __SKIPPED_LIST_H__

#include <stdio.h>

typedef struct _Skip_node {
    int elem;
    int level;
    struct _Skip_node** forward;
} Skip_node;

Skip_node* make_empty_skipped_list(int);
void delete_skipped_list(Skip_node*);
void insert(Skip_node*,int);
void delete(Skip_node*,int);
Skip_node* find(Skip_node*,int);

#endif