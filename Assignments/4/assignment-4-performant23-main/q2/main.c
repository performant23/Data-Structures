#include <stdio.h>
#include <stdlib.h>
#include "../helpers/helpers.h"
#include "../prng/mt64.h"
#include "q2.h"

int main(int argc, char *argv[])
{

    // Make sure we have a seed
    if (argc != 3)
    {
        printf("Usage: %s <seed> <array_length>\n", argv[0]);
        exit(1);
    }

    init_genrand64(atoi(argv[1])); // Set the seed for the random number generator

    // Accept the length of the lists from the command line
    int l = atoi(argv[2]);

    // Generate the random array
    unsigned int *arr = generateRandomNumbers(l);
    printf("Random Array: ");
    printArray(arr, l);

    // Part A: Construct the tree and print it inorder after every insertion
    tNode *root = NULL;

    for (int x = 0; x <= l - 1; x++)
    {
        root = insertTree(root, arr[x]);
        printf("Inorder: ");
        inorderTree(root);
        printf("\n");
    }

    // Part B: Delete the 4th, 5th and 6th smallest elements and print the tree inorder after each deletion
    int c = 4;
    for (int i = 0; i < 3; i++)
    {
        int cthSmallest = CthSmallest(root, arr, l, c+i);
        printf("%dth smallest element is: %d\n", c, cthSmallest);
        root = deleteTree(root, cthSmallest);
        printf("Inorder: ");
        inorderTree(root);
        printf("\n");
        c++;
    }

    return 0;
}
