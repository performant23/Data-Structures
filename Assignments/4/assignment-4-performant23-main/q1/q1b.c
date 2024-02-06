#include <stdio.h>
#include <stdlib.h>
#include "q1.h"


// Here we create a new node with a given value and an array of pointers. 
//Array of pointers represents the connections to the next stations.

node* _1b_construct_node(int value, int max_level) {
	node* newNode = (node*)malloc(sizeof(node));
    newNode->value = value;
    newNode->connection_to_next_stations = (node**)malloc(sizeof(node*) * (max_level + 1));
    for(int i = 0; i <= max_level; i++) {
        newNode->connection_to_next_stations[i] = NULL;
    }
    return newNode;
	// return construct;
}


// Here we insert a new node (add a new station) by traversing the list to find the correct position and update the pointers for correct ordering.
node* _1b_insert_node(node* head, int value, int max_level, int index) {
    node* newNode = _1b_construct_node(value, max_level);
    
    if (head == NULL) {
        return newNode;
    }
    
    node* temp = head;
    while (temp->connection_to_next_stations[0] != NULL) {
        temp = temp->connection_to_next_stations[0];
    }
    
    temp->connection_to_next_stations[0] = newNode;
    
    for (int i = 1; i <= max_level; i++) {
        if (index % i == 0) {
            node* current = head;
            while (current->connection_to_next_stations[i] != NULL) {
                current = current->connection_to_next_stations[i];
            }
            current->connection_to_next_stations[i] = newNode;
        }
    }
    
    return head;
}


// Delete a node with a given value and reorganize the list
void _1b_delete_node(node* head, int value, int max_level) {
    node* temp = head;
    node* prev[max_level + 1];

    for (int i = 0; i <= max_level; i++) {
        prev[i] = NULL;
    }

    for (int i = max_level; i >= 0; i--) {
        while (temp->connection_to_next_stations[i] != NULL && temp->connection_to_next_stations[i]->value < value) {
            temp = temp->connection_to_next_stations[i];
        }
        prev[i] = temp;
    }

    temp = temp->connection_to_next_stations[0];

    if (temp != NULL && temp->value == value) {
        for (int i = 0; i <= max_level; i++) {
            if (prev[i] != NULL && prev[i]->connection_to_next_stations[i] == temp) {
                prev[i]->connection_to_next_stations[i] = temp->connection_to_next_stations[i];
            }
        }

        free(temp->connection_to_next_stations);
        free(temp);
    }
}

// Print the list with all its levels
void _1b_print_list(node* head, int max_level) {
    if (head == NULL) {
        printf("Empty list\n");
        return;
    }

    node* current = head;

    for (int m = 1; m <= max_level; m++) {
        current = head;

        while (current) {
            printf("%d -> ", current->value);
            current = current->connection_to_next_stations[m];
        }

        printf("\n");
    }
}
