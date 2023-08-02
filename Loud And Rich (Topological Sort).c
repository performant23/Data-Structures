// Loud and Rich (https://leetcode.com/problems/loud-and-rich/description/)

// You are given an array richer where richer[i] = [ai, bi] indicates that ai has more money than bi and an integer array quiet 
// where quiet[i] is the quietness of the ith person. All the given data in richer are logically correct (i.e., the data will not lead you to a 
// situation where x is richer than y and y is richer than x at the same time).

// Return an integer array answer where answer[x] = y if y is the least quiet person (that is, the person y with the smallest 
// value of quiet[y]) among all people who definitely have equal to or more money than the person x.

// Solution:
#include <stdlib.h>

typedef struct {
    int val;
    struct ListNode* next;
} ListNode;

typedef struct {
    ListNode* head;
} LinkedList;

void addToList(LinkedList* list, int val) {
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
    newNode->val = val;
    newNode->next = list->head;
    list->head = newNode;
}
// Using DFS for topological sort
void dfs(int person, int* quiet, LinkedList* adjList, int* result, int* visited) {
    visited[person] = 1;
    ListNode* current = adjList[person].head;
    int minQuiet = quiet[person];
    int minPerson = person;
    
    while (current != NULL) {
        int neighbor = current->val;
        if (!visited[neighbor]) {
            dfs(neighbor, quiet, adjList, result, visited);
        }
        
        if (quiet[neighbor] < minQuiet) {
            minQuiet = quiet[neighbor];
            minPerson = result[neighbor];
        }
        
        current = current->next;
    }
    
    quiet[person] = minQuiet;
    result[person] = minPerson;
}


int* loudAndRich(int** richer, int richerSize, int* richerColSize, int* quiet, int quietSize, int* returnSize){
    int n = quietSize;
    int* result = (int*)malloc(n * sizeof(int));
    int* visited = (int*)calloc(n, sizeof(int));
    LinkedList* adjList = (LinkedList*)malloc(n * sizeof(LinkedList));
    
    for (int i = 0; i < n; i++) {
        adjList[i].head = NULL;
    }
    
    // Creating the DAG
    for (int i = 0; i < richerSize; i++) {
        int richerPerson = richer[i][0];
        int poorerPerson = richer[i][1];
        addToList(&adjList[poorerPerson], richerPerson);
    }
    
    // DFS for each person
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfs(i, quiet, adjList, result, visited);
        }
    }
    
    *returnSize = n;
    return result;
}

int main() {
    int richerSize = 3;
    int richerColSize[] = { 2, 2, 2 };
    int** richer = (int**)malloc(richerSize * sizeof(int*));
    richer[0] = (int*)malloc(2 * sizeof(int));
    richer[0][0] = 1;
    richer[0][1] = 0;
    richer[1] = (int*)malloc(2 * sizeof(int));
    richer[1][0] = 2;
    richer[1][1] = 1;
    richer[2] = (int*)malloc(2 * sizeof(int));
    richer[2][0] = 3;
    richer[2][1] = 1;

    int quietSize = 4;
    int quiet[] = { 3, 2, 5, 4 };

    int returnSize = 0;
    int* result = loudAndRich(richer, richerSize, richerColSize, quiet, quietSize, &returnSize);

    printf("Solution: ");
    for (int i = 0; i < returnSize; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    // Free memory
    for (int i = 0; i < richerSize; i++) {
        free(richer[i]);
    }
    free(richer);
    free(result);

    return 0;
}