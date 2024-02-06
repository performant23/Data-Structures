#include <stdio.h>
#include <stdlib.h>
#include "q1.h"
#include <stdbool.h>


// To solve this problem, we can create a skip list where each node has a value and an array of pointers
// Each station is represented as a node in a skip list, where each node contains a value and an array of pointers to the next stations.
//The skip list allows for efficient traversal of the stations, with the ‘fast’ trains skipping over nodes (stations) 
// in the list according to the Fibonacci sequence.
//Each pointer in the array corresponds to a different level in the skip list, which represents the ‘fast’ and ‘slow’ tracks.
// The ‘fast’ trains can quickly skip over stations by following the pointers at higher levels in the skip list.

node* construct_node(int value, int max_value) {
    node* newNode = (node*)malloc(sizeof(node));
    newNode->value = value;
    newNode->connection_to_next_stations = (node**)malloc(max_value * sizeof(node*));

    return newNode;
}

// A/c to fibonacci sequence
int isfasttrainStop(int n) {
    int fb = 0, fb_ = 1, temp;
    while (fb <= n) {
        if (fb == n) {
            return 1;
        }

        temp = fb;
        fb = fb_;
        fb_ = temp + fb_;
    }

    return 0;
}

node* insert_node(node* head, int value, int max_level) {
    node* newNode = construct_node(value, max_level);
    node* curr = head;
    node* temp = head;
    int position = 0;
    while (curr->connection_to_next_stations[0] != NULL) {
        curr = curr->connection_to_next_stations[0];
        position++;
        if (isfasttrainStop(position)) {
            temp = curr;
        }
    }
    curr->connection_to_next_stations[0] = newNode;
    position++;
    if (isfasttrainStop(position)) {
        temp->connection_to_next_stations[1] = newNode;
    }
    return head;
}

// Print the list with both its levels
void print_list(node* head, int max_level) {
    node* curr = head;
    while (curr) {
        printf("%d -> ", curr->value);
        curr = curr->connection_to_next_stations[0];
    }
    printf("\n");
    curr = head;
    while (curr) {
        printf("%d -> ", curr->value);
        curr = curr->connection_to_next_stations[1];
    }
    printf("\n");
}