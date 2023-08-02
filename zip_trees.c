#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
};

int getHeight(struct TreeNode* root) {
    if (root == NULL) return 0;
    int leftHeight = getHeight(root->left);
    int rightHeight = getHeight(root->right);
    return (leftHeight > rightHeight) ? leftHeight + 1 : rightHeight + 1;
}

struct TreeNode* leftRotate(struct TreeNode* root) {
    struct TreeNode* newRoot = root->right;
    root->right = newRoot->left;
    newRoot->left = root;
    return newRoot;
}

struct TreeNode* rightRotate(struct TreeNode* root) {
    struct TreeNode* newRoot = root->left;
    root->left = newRoot->right;
    newRoot->right = root;
    return newRoot;
}

//balancing trees by performing rotations
struct TreeNode* balance(struct TreeNode* root) {
    int leftHeight = (root->left != NULL) ? root->left->val : 0;
    int rightHeight = (root->right != NULL) ? root->right->val : 0;

    if (leftHeight - rightHeight == 2) {
        if ((root->left->left != NULL ? root->left->left->val : 0) - (root->left->right != NULL ? root->left->right->val : 0) == 1)
            return rightRotate(root);
        else {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
    }

    if (rightHeight - leftHeight == 2) {
        if ((root->right->right != NULL ? root->right->right->val : 0) - (root->right->left != NULL ? root->right->left->val : 0) == 1)
            return leftRotate(root);
        else {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
    }

    return root;
}

// insertion of a node
struct TreeNode* insert(struct TreeNode* root, int val) {
    if (root == NULL) {
        struct TreeNode* node = malloc(sizeof(struct TreeNode));
        node->val = val;
        node->left = NULL;
        node->right = NULL;
        return node;
    }

    if (val < root->val)
        root->left = insert(root->left, val);
    else
        root->right = insert(root->right, val);

    return balance(root);
}

// inorder traversal of tree
void inorder(struct TreeNode* root, int* vals, int* size) {
    struct TreeNode* stack[10000];
    int top = -1;
    struct TreeNode* current = root;

    while (current != NULL || top != -1) {
        while (current != NULL) {
            stack[++top] = current;
            current = current->left;
        }

        current = stack[top--];
        vals[(*size)++] = current->val;
        current = current->right;
    }
}


// Merge 2 trees using ziptrees into 1 balanced tree
struct TreeNode* zipTrees(struct TreeNode* root1, struct TreeNode* root2) {
    int vals1[10000];
    int size1 = 0;
    int vals2[10000];
    int size2 = 0;

    inorder(root1, vals1, &size1);
    inorder(root2, vals2, &size2);

    struct TreeNode* newRoot = NULL;

    for (int i = 0; i < size1; i++)
        newRoot = insert(newRoot, vals1[i]);

    for (int i = 0; i < size2; i++)
        newRoot = insert(newRoot, vals2[i]);

    return newRoot;
}

void freeTree(struct TreeNode* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

void inorderTraversalPrint(struct TreeNode* root) {
    if (root != NULL) {
        inorderTraversalPrint(root->left);
        printf("%d ", root->val);
        inorderTraversalPrint(root->right);
    }
}

int main() {
    struct TreeNode* root1 = NULL;
    root1 = insert(root1, 5);
    root1 = insert(root1, 3);
    root1 = insert(root1, 7);

    struct TreeNode* root2 = NULL;
    root2 = insert(root2, 8);
    root2 = insert(root2, 4);
    root2 = insert(root2, 9);

    struct TreeNode* mergedRoot = zipTrees(root1, root2);
    printf("Inorder Traversal: \n");
    inorderTraversalPrint(mergedRoot);

    freeTree(mergedRoot);

    return 0;
}
