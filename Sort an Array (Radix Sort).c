// Sort an Array (https://leetcode.com/problems/sort-an-array/description/) (The problem was solved above with counting sort)

//Given an array of integers nums, sort the array in ascending order and return it.
// You must solve the problem without using any built-in functions in O(nlog(n)) time complexity and with 
//the smallest space complexity possible.


#include <stdio.h>
#include <stdlib.h>

void countingSort(int* nums, int numsSize, int exp) {
    int output[numsSize];
    int count[21] = {0};

    // Count occurrences of each digit at the current exponent
    for (int i = 0; i < numsSize; i++) {
        int index = (nums[i] / exp) % 10 + 10; 
        count[index]++;
    }

    for (int i = 1; i < 21; i++) {
        count[i] += count[i - 1];
    }

    // Build the output array using the sorted digits
    for (int i = numsSize - 1; i >= 0; i--) {
        int index = (nums[i] / exp) % 10 + 10;
        output[count[index] - 1] = nums[i];
        count[index]--;
    }

    for (int i = 0; i < numsSize; i++) {
        nums[i] = output[i];
    }
}

int getMax(int* nums, int numsSize) {
    int max = nums[0];
    for (int i = 1; i < numsSize; i++) {
        if (nums[i] > max) {
            max = nums[i];
        }
    }
    return max;
}

void radixSort(int* nums, int numsSize) {
    int max = getMax(nums, numsSize);

    for (int exp = 1; max / exp > 0; exp *= 10) {
        countingSort(nums, numsSize, exp);
    }
}

int* sortArray(int* nums, int numsSize, int* returnSize) {
    radixSort(nums, numsSize);

    *returnSize = numsSize;
    return nums;
}

int main() {
    int nums[] = {170, 45, 75, 90, 802, 24, 2, 66};
    int numsSize = sizeof(nums) / sizeof(nums[0]);

    int* sortedArray = sortArray(nums, numsSize, &numsSize);

    printf("Sorted Array: ");
    for (int i = 0; i < numsSize; i++) {
        printf("%d ", sortedArray[i]);
    }
    printf("\n");

    free(sortedArray);

    return 0;
}