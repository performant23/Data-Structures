#ifndef Q1_H
#define Q1_H

//Tree node structure
struct treeNode {
    int value;
    struct treeNode* left;
    struct treeNode* right;
    int height;
};

//K-th smallest centre node structure
struct centreNode {
    int val;
    int* maxHeap;
    int* minHeap;
    int minHeapSize;
    int maxHeapSize;
};

//Make it easier to call the structs
typedef struct treeNode tNode;
typedef struct centreNode cNode;

tNode* createTreeNode(int val);
tNode* searchTree(tNode* root, int value);
tNode* insertTree(tNode* root, int value);
tNode* inOrderPre(tNode* root);
tNode* deleteTree(tNode* root, int value);
void inorderTree(tNode* root);
void swap(int* num1, int* num2);
void heapifyMax(int* arr, int len, int rootIndex);
void buildMaxHeap(int* arr, int len);
int* insertMaxHeap(int* arr, int* len, int value);
int extractMax(int* arr, int* len);
int CthSmallest(tNode* root, unsigned int* arr, int n, int c);

#endif