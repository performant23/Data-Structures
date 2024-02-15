#include <stdio.h>
#include <stdlib.h>
#include "mt64.h"

// Add these declarations at the beginning of your main.c file
int* generateRandomNumbers(long long int n) {
    int* randomNumbers = (int*)malloc(sizeof(int) * n);
    for(long long int i = 0; i < n; i++) {
        randomNumbers[i] = (int)(genrand64_int64() % 1000);
    }
    return randomNumbers;
}

void printArray(int* arr, long long int n) {
    for(long long int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
}

struct treeNode {
    int val;
    struct treeNode* left;
    struct treeNode* right;
};

typedef struct treeNode TreeNode;

TreeNode* insertBST(TreeNode* root, int val) {
    if (root == NULL) {
        TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
        newNode->val = val;
        newNode->left = newNode->right = NULL;
        return newNode;
    }

    if (val < root->val) {
        root->left = insertBST(root->left, val);
    } else if (val > root->val) {
        root->right = insertBST(root->right, val);
    }

    return root;
}

void postOrderTraversal(TreeNode* root) {
    if (root != NULL) {
        postOrderTraversal(root->left);
        postOrderTraversal(root->right);
        printf("%d ", root->val);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <seed>\n", argv[0]);
        exit(1);
    }

    init_genrand64(atoi(argv[1]));

    long long int n = 10000000000LL;
    long long int targetIndex = 100000;  // 10^5th largest element

    // Use a fixed-size array
    int sequence[n];

    // Generate the sequence and store it in the array
    for (long long int i = 0; i < n; i++) {
        sequence[i] = (int)(genrand64_int64() % 1000);
    }

    // Print the 10^5th largest element
    printf("10^5th largest element: %d\n", sequence[n - targetIndex]);

    return 0;
}
