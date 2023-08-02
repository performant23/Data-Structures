// Design Skiplist (https://leetcode.com/problems/design-skiplist/description/)

// Design a Skiplist without using any built-in libraries.
// A skiplist is a data structure that takes O(log(n)) time to add, erase and search. 
// Comparing with treap and red-black tree which has the same function and performance, 
// the code length of Skiplist can be comparatively short and the idea behind Skiplists is just simple linked lists.

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>

#define MAX_LEVEL 16

typedef struct Node {
    int val;
    struct Node *next[MAX_LEVEL];
} Node;

typedef struct {
    Node *head;
} Skiplist;

Skiplist* skiplistCreate() {
    Skiplist *skiplist = malloc(sizeof(Skiplist));
    skiplist->head = malloc(sizeof(Node));
    for (int i = 0; i < MAX_LEVEL; i++) {
        skiplist->head->next[i] = NULL;
    }
    srand(time(NULL));
    return skiplist;
}

bool skiplistSearch(Skiplist* obj, int target) {
    Node *p = obj->head;
    for (int i = MAX_LEVEL - 1; i >= 0; i--) {
        while (p->next[i] && p->next[i]->val < target) {
            p = p->next[i];
        }
    }
    return p->next[0] && p->next[0]->val == target;
}

void skiplistAdd(Skiplist* obj, int num) {
    Node *update[MAX_LEVEL];
    Node *p = obj->head;
    for (int i = MAX_LEVEL - 1; i >= 0; i--) {
        while (p->next[i] && p->next[i]->val < num) {
            p = p->next[i];
        }
        update[i] = p;
    }
    Node *new_node = malloc(sizeof(Node));
    new_node->val = num;
    int level = 1;
    while (level < MAX_LEVEL && rand() % 2 == 0) {
        level++;
    }
    for (int i = 0; i < level; i++) {
        new_node->next[i] = update[i]->next[i];
        update[i]->next[i] = new_node;
    }
}

bool skiplistErase(Skiplist* obj, int num) {
    Node *update[MAX_LEVEL];
    Node *p = obj->head;
    for (int i = MAX_LEVEL - 1; i >= 0; i--) {
        while (p->next[i] && p->next[i]->val < num) {
            p = p->next[i];
        }
        update[i] = p;
    }
    if (!p->next[0] || p->next[0]->val != num) {
        return false;
    }
    Node *del_node = p->next[0];
    for (int i = 0; i < MAX_LEVEL && update[i]->next[i] == del_node; i++) {
        update[i]->next[i] = del_node->next[i];
    }
    free(del_node);
    return true;
}

void skiplistFree(Skiplist* obj) {
    Node *p = obj->head;
    while (p) {
        Node *tmp = p->next[0];
        free(p);
        p = tmp;
    }
}


int main() {
    Skiplist* obj = skiplistCreate();

    skiplistAdd(obj, 1);
    skiplistAdd(obj, 2);
    skiplistAdd(obj, 3);
    
    bool search1 = skiplistSearch(obj, 2);
    printf("Search for 2: %s\n", search1 ? "Found" : "Not found");

    bool erase1 = skiplistErase(obj, 2);
    printf("Erase 2: %s\n", erase1 ? "Success" : "Not found");

    bool search2 = skiplistSearch(obj, 2);
    printf("Search for 2 after erase: %s\n", search2 ? "Found" : "Not found");

    skiplistFree(obj);
    
    return 0;
}