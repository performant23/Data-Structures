// Course Schedule - II (https://leetcode.com/problems/course-schedule-ii/description/)

//There are a total of numCourses courses you have to take, labeled from 0 to numCourses - 1. 
// You are given an array prerequisites where prerequisites[i] = [a_i, b_i] indicates that you must take course b_i first if you want to 
// take course a_i.
// For example, the pair [0, 1], indicates that to take course 0 you have to first take course 1.
//Return the ordering of courses you should take to finish all courses. 
//If there are many valid answers, return any of them. If it is impossible to finish all courses, return an empty array.


// Solution:
#include <stdlib.h>

typedef struct {
    int val;
    struct ListNode* next;
} ListNode;

typedef struct {
    ListNode* head;
} LinkedList;

typedef struct {
    int numCourses;
    int* inDegrees;
    LinkedList* adjacencyList;
    int* result;
    int index;
} Graph;

ListNode* createListNode(int val) {
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
    newNode->val = val;
    newNode->next = NULL;
    return newNode;
}

void addToList(LinkedList* list, int val) {
    ListNode* newNode = createListNode(val);
    if (list->head == NULL) {
        list->head = newNode;
    } else {
        newNode->next = list->head;
        list->head = newNode;
    }
}

int* findOrder(int numCourses, int** prerequisites, int prerequisitesSize, int* prerequisitesColSize, int* returnSize) {
    int* result = (int*)malloc(numCourses * sizeof(int));
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    
    // Initializing graph data
    graph->numCourses = numCourses;
    graph->inDegrees = (int*)calloc(numCourses, sizeof(int));
    graph->adjacencyList = (LinkedList*)malloc(numCourses * sizeof(LinkedList));
    graph->result = result;
    graph->index = 0;
    
    for (int i = 0; i < numCourses; i++) {
        graph->adjacencyList[i].head = NULL;
    }
    
    for (int i = 0; i < prerequisitesSize; i++) {
        int course = prerequisites[i][0];
        int prerequisite = prerequisites[i][1];
        addToList(&graph->adjacencyList[prerequisite], course);
        graph->inDegrees[course]++;
    }
    
    // Using BFS for topological sort
    int* queue = (int*)malloc(numCourses * sizeof(int));
    int front = 0, rear = 0;
    
    for (int i = 0; i < numCourses; i++) {
        if (graph->inDegrees[i] == 0) {
            queue[rear++] = i;
        }
    }
    
    while (front < rear) {
        int course = queue[front++];
        result[graph->index++] = course;
        
        ListNode* current = graph->adjacencyList[course].head;
        while (current != NULL) {
            int neighbor = current->val;
            graph->inDegrees[neighbor]--;
            
            if (graph->inDegrees[neighbor] == 0) {
                queue[rear++] = neighbor;
            }
            
            current = current->next;
        }
    }
    
    // Checking validity condition
    if (graph->index == numCourses) {
        *returnSize = numCourses;
    } else {
        *returnSize = 0;
    }
    
    free(queue);
    free(graph->inDegrees);
    free(graph->adjacencyList);
    free(graph);
    
    return result;
}

// Sample Testcase
int main() {
    int numCourses = 4;
    int prerequisitesSize = 2;
    int prerequisitesColSize[] = { 2, 2 };
    int** prerequisites = (int**)malloc(prerequisitesSize * sizeof(int*));
    prerequisites[0] = (int*)malloc(2 * sizeof(int));
    prerequisites[0][0] = 1;
    prerequisites[0][1] = 0;
    prerequisites[1] = (int*)malloc(2 * sizeof(int));
    prerequisites[1][0] = 2;
    prerequisites[1][1] = 1;

    int returnSize = 0;
    int* result = findOrder(numCourses, prerequisites, prerequisitesSize, prerequisitesColSize, &returnSize);

    printf("Solution: ");
    for (int i = 0; i < returnSize; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    // Free memory
    for (int i = 0; i < prerequisitesSize; i++) {
        free(prerequisites[i]);
    }
    free(prerequisites);
    free(result);

    return 0;
}