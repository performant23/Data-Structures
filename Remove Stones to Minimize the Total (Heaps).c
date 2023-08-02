// Remove Stones to Minimize the Total (https://leetcode.com/problems/remove-stones-to-minimize-the-total/)

// You are given a 0-indexed integer array piles, where piles[i] represents the number of stones in the ith pile, and an integer k.
// You should apply the following operation exactly k times:

//     Choose any piles[i] and remove floor(piles[i] / 2) stones from it.

// Notice that you can apply the operation on the same pile more than once.

// Return the minimum possible total number of stones remaining after applying the k operations.

// floor(x) is the greatest integer that is smaller than or equal to x (i.e., rounds x down).

#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void maxHeapify(int* arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        maxHeapify(arr, n, largest);
    }
}

void buildMaxHeap(int* arr, int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        maxHeapify(arr, n, i);
}

int extractMax(int* arr, int* n) {
    if (*n == 0)
        return -1;

    int maxVal = arr[0];
    arr[0] = arr[*n - 1];
    (*n)--;
    maxHeapify(arr, *n, 0);

    return maxVal;
}

void insert(int* arr, int* n, int val) {
    (*n)++;
    arr[*n - 1] = val;

    for (int i = *n - 1; i != 0 && arr[(i - 1) / 2] < arr[i];) {
        swap(&arr[i], &arr[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

int minStoneSum(int* piles, int pilesSize, int k) {
    buildMaxHeap(piles, pilesSize);

    while (k--) {
        int maxVal = extractMax(piles, &pilesSize);
        maxVal -= maxVal / 2;
        insert(piles, &pilesSize, maxVal);
    }

    int sum = 0;
    for (int i = 0; i < pilesSize; i++)
        sum += piles[i];

    return sum;
}

int main() {
    int piles[] = {5,4,9};
    int pilesSize = sizeof(piles)/sizeof(piles[0]);
    int k = 2;

    printf("%d\n", minStoneSum(piles, pilesSize, k));

    return 0;
}