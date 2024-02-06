#include <stdio.h>
#include <stdlib.h>
#include "q2.h"
#include <limits.h> 

// References - 
// https://www.programiz.com/dsa/avl-tree
// https://www.programiz.com/dsa/heap-data-structure

// Create a node in the tree with the given value
tNode* createTreeNode(int value) {
    tNode* newNode = (tNode*)malloc(sizeof(tNode));
    if (newNode == NULL) {
        printf("Memory Leak");
        return NULL;
    }
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 1;
    return newNode;
    // return newNode;
}

// Return the height of the node
int getHeight(tNode* root) {
	if (root == NULL) {
        return 0;
    }
    return root->height;
    // return root -> height;
}


// Refresh the height of the node
tNode* setHeight(tNode* root) {
    if (root == NULL) {
        return root;
    }
    int lH = getHeight(root->left);
    int rH = getHeight(root->right);
    if (lH > rH) {
        root->height = 1 + lH;
    } else {
        root->height = 1 + rH;
    }
    return root;
}



// Get the balance of the root's subtree
int getBalance(tNode* root)
{
    if (root == NULL) {
        return 0;
    }
    return getHeight(root->left) - getHeight(root->right);
	// return balance;
}

// Right Rotation
tNode* rightRotate(tNode* root) {
    
    printf("R\n");
	tNode* left_node = root->left;
    tNode* right_subtree = left_node->right;

    left_node->right = root;
    root->left = right_subtree;

    setHeight(root);
    setHeight(left_node);
    return left_node;
}

// Left Rotation
tNode* leftRotate(tNode* root) {
    
    printf("L\n");
    tNode* right_node = root->right;
    tNode* left_subtree = right_node->left;

    right_node->left = root;
    root->right = left_subtree;

    setHeight(root);
    setHeight(right_node);

    return right_node;
	
    // return right_node;
}

// Search the tree for the given value and return the node if found
tNode* searchTree(tNode* root, int value) {
    
    if (root == NULL) {
        return root;
    }
    if(root->value == value)
    {
        return root;
    }

    if (value < root->value) {
        return searchTree(root->left, value);
    }

    return searchTree(root->right, value);
}

// Insert a new node with the given value and rebalance the tree
tNode* insertTree(tNode* root, int value) {
    if (root == NULL) {
        return createTreeNode(value);
    }

    if (value < root->value) {
        root->left = insertTree(root->left, value);
    } else if (value > root->value) {
        root->right = insertTree(root->right, value);
    } else {
        return root;
    }

    setHeight(root);

    int balance = getBalance(root);

    if (balance > 1) {
        if (value < root->left->value) {
            return rightRotate(root);
        } else {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
    } else if (balance < -1) {
        if (value > root->right->value) {
            return leftRotate(root);
        } else {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
    }

    return root;
    
    // return root;
}

// Return the inorder predecessor of the given node
tNode* inOrderPre(tNode* root) {
    
    // return root;
    tNode* curr = root;
    while (curr->right != NULL) {
        curr = curr->right;
    }
    return curr;
}

// Delete the node with the given value and rebalance the tree
tNode* deleteTree(tNode* root, int val) {
    if (root == NULL) {
        return root;
    }

    if (val < root->value) {
        root->left = deleteTree(root->left, val);
    } else if (val > root->value) {
        root->right = deleteTree(root->right, val);
    } else {
        if (root->left == NULL) {
            tNode* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            tNode* temp = root->left;
            free(root);
            return temp;
        }

        tNode* temp = inOrderPre(root->right);

        root->value = temp->value;

        root->right = deleteTree(root->right, temp->value);
    }

    root = setHeight(root);

    int balance = getBalance(root);

    if (balance > 1) {
        if (getBalance(root->left) >= 0) {
            return rightRotate(root);
        } else {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
    }

    if (balance < -1) {
        if (getBalance(root->right) <= 0) {
            return leftRotate(root);
        } else {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
    }

    return root;
    // return root;
}

// Print out the tree in inorder
void inorderTree(tNode* root) {
    if (root != NULL) {
        inorderTree(root -> left); 
        printf("%d ",root->value);
        inorderTree(root->right);
    }
}

// Swap 2 elements in an array
void swap(int* num1, int* num2) {
    int temp = *num1;
    *num1 = *num2;
    *num2 = temp;
}

// Heapify max heap
void heapifyMax(int* arr, int len, int rootIndex) {
    
    int largest = rootIndex;
    int left = 2*rootIndex + 1;
    int right = 2*rootIndex + 2;

    if (left < len && arr[left] > arr[largest])
        largest = left;

    if (right < len && arr[right] > arr[largest])
        largest = right;

    if (largest != rootIndex)
    {
        swap(&arr[rootIndex], &arr[largest]);
        heapifyMax(arr, len, largest);
    }


}

// Build max heap
void buildMaxHeap(int* arr, int len) {
    int startval = (len / 2) - 1;

    for (int i = startval; i >= 0; i--)
        heapifyMax(arr, len, i);

}

// Insert element in max heap
int* insertMaxHeap(int* arr, int* len, int val) {
    if (*len == 0)
    {
        arr = (int*)malloc(sizeof(int));
        arr[0] = val;
        *len = 1;
    }
    else
    {
        arr = (int*)realloc(arr, (*len + 1)*sizeof(int));
        arr[*len] = val;
        *len = *len + 1;
        buildMaxHeap(arr, *len);
    }

    return arr;
    // return arr;

}

// Extract maximum element from max heap
int extractMax(int* arr, int* len) {
    if (*len == 0)
        return INT_MIN;

    int max = arr[0];
    arr[0] = arr[*len - 1];
    *len = *len - 1;
    arr = (int*)realloc(arr, *len*sizeof(int));
    heapifyMax(arr, *len, 0);
    return max;
    // return max;

}


// Find and return the Cth smallest element
int CthSmallest(tNode* root, unsigned int* arr, int n, int c) {
    int* Heap = NULL;
    int len = 0;

    for (int i = 0; i < n; i++) {
        if (i < c) {
            Heap = insertMaxHeap(Heap, &len, arr[i]);
        } else if (arr[i] < Heap[0]) {
            extractMax(Heap, &len);
            Heap = insertMaxHeap(Heap, &len, arr[i]);
        }
    }

    return Heap[0];
}

