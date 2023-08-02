// Maximum Gap (https://leetcode.com/problems/maximum-gap/description/)

// Given an integer array nums, return the maximum difference between two successive elements in its sorted form. 
//If the array contains less than two elements, return 0.
//You must write an algorithm that runs in linear time and uses linear extra space.


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int getMax(int* nums, int numsSize) {
    int max = nums[0];
    for (int i = 1; i < numsSize; i++) {
        if (nums[i] > max) {
            max = nums[i];
        }
    }
    return max;
}

// Counting Sort helper function
void countingSort(int* nums, int numsSize, int exp) {
    int output[numsSize];
    int count[10] = {0};

    for (int i = 0; i < numsSize; i++) {
        count[(nums[i] / exp) % 10]++;
    }

    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    for (int i = numsSize - 1; i >= 0; i--) {
        output[count[(nums[i] / exp) % 10] - 1] = nums[i];
        count[(nums[i] / exp) % 10]--;
    }

    for (int i = 0; i < numsSize; i++) {
        nums[i] = output[i];
    }
}

// Radix Sort
void radixSort(int* nums, int numsSize) {
    int max = getMax(nums, numsSize);

    for (int exp = 1; max / exp > 0; exp *= 10) {
        countingSort(nums, numsSize, exp);
    }
}

// Finding max difference
int maximumGap(int* nums, int numsSize) {
    if (numsSize < 2) {
        return 0;
    }

    radixSort(nums, numsSize);

    int maxDiff = 0;
    for (int i = 1; i < numsSize; i++) {
        int diff = nums[i] - nums[i - 1];
        if (diff > maxDiff) {
            maxDiff = diff;
        }
    }

    return maxDiff;
}

int main() {
    int nums[] = {3, 6, 9, 1};
    int numsSize = sizeof(nums) / sizeof(nums[0]);

    int maxGap = maximumGap(nums, numsSize);

    printf("Maximum Gap: %d\n", maxGap);

    return 0;
}