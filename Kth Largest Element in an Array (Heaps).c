// Kth Largest Element in an Array (https://leetcode.com/problems/kth-largest-element-in-an-array/description/)

// Given an integer array nums and an integer k, return the kth largest element in the array.
// Note that it is the kth largest element in the sorted order, not the kth distinct element.



#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void minHeapify(int* arr, int n, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] < arr[smallest])
        smallest = left;

    if (right < n && arr[right] < arr[smallest])
        smallest = right;

    if (smallest != i) {
        swap(&arr[i], &arr[smallest]);
        minHeapify(arr, n, smallest);
    }
}

void buildMinHeap(int* arr, int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        minHeapify(arr, n, i);
}

int extractMin(int* arr, int* n) {
    if (*n == 0)
        return -1;

    int minVal = arr[0];
    arr[0] = arr[*n - 1];
    (*n)--;
    minHeapify(arr, *n, 0);

    return minVal;
}

void insert(int* arr, int* n, int val) {
    (*n)++;
    arr[*n - 1] = val;

    for (int i = *n - 1; i != 0 && arr[(i - 1) / 2] > arr[i];) {
        swap(&arr[i], &arr[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

int findKthLargest(int* nums, int numsSize, int k) {
    int heap[k];
    int heapSize = 0;

    for (int i = 0; i < numsSize; i++) {
        if (heapSize < k)
            insert(heap, &heapSize, nums[i]);
        else if (nums[i] > heap[0]) {
            extractMin(heap, &heapSize);
            insert(heap, &heapSize, nums[i]);
        }
    }

    return heap[0];
}

int main() {
    int nums[] = {3,2,3,1,2,4,5,5,6};
    int numsSize = sizeof(nums)/sizeof(nums[0]);
    int k = 4;

    printf("%d\n", findKthLargest(nums, numsSize, k));

    return 0;
}