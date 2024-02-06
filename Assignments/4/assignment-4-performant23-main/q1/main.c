#include <stdio.h>
#include <stdlib.h>
#include "../helpers/helpers.h"
#include "../prng/mt64.h"
#include "q1.h"

int fib_c(int n) {
    int a = 0, b = 1;
    for (int i = 0; i < n; ++i) {
        int temp = a;
        a = b;
        b += temp;
    }
    return a;
}

int main(int argc, char *argv[]) {

    //Make sure we have a seed
    if(argc != 3) {
        printf("Usage: %s <seed> <array_length>\n", argv[0]);
        exit(1);
    }

    init_genrand64(atoi(argv[1])); //Set the seed for the random number generator

    // Accept the length of the lists from the command line
    int l = atoi(argv[2]);

    // Set the number of levels (lines)
    int m = 2;

    // Generate the random array
    unsigned int *arr = generateRandomNumbers(l);
    printf("Random Array: ");
    printArray(arr, l);

    // Part A: Construct the list and print its levels
    printf("Part A:\n");
    node* head = construct_node(arr[0], m);
	for (int i = 1; i < l; i++) {
		head = insert_node(head, arr[i], m);
	}

    print_list(head, m);

    // Reset the number of levels. Let m=4
    m = 4;

    // Part B: Construct the list and print its levels
    printf("Part B:\n");
    head = _1b_construct_node(arr[0], m);
	for (int i = 1; i < l; i++) {
        head = _1b_insert_node(head, arr[i], m, i);
	}
    _1b_print_list(head, m);

    // Part C: Call delete, then use _1b_ functions
int size = l;
    printf("Part C:\n");

    for (int i = 0; i < size; i++) {
        if (isfasttrainStop(i)) {
            arr[i] = -1;
        }
    }

    int sizeAfterRemovingFib = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] != -1) {
            arr[sizeAfterRemovingFib] = arr[i];
            sizeAfterRemovingFib++;
        }
    }

    if (sizeAfterRemovingFib > 0) {
        int m = 4;

        node* head = _1b_construct_node(arr[0], m);
        for (int i = 1; i < sizeAfterRemovingFib; i++) {
            head = _1b_insert_node(head, arr[i], m, i);
        }

        _1b_print_list(head, m);

    } else {
        printf("Empty Array\n");
    }

    free(arr);

    return 0;

}

