#ifndef Q1_H
#define Q1_H

struct node_type {     
    // Your definition here 
    int value;
    struct node_type** connection_to_next_stations;
};  
    
typedef struct node_type node; 
int isfasttrainStop(int n);
node* construct_node(int value, int max_level);
node* insert_node(node* head, int value, int max_level);
void delete_node(node* head, int value, int max_level);
void print_list(node* head, int max_level);


node* _1b_construct_node(int value, int max_level);
node* _1b_insert_node(node* head, int value, int max_level, int line);
void _1b_delete_node(node* head, int value, int max_level);
void _1b_print_list(node* head, int max_level);

#endif