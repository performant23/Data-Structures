// Sort an Array (https://leetcode.com/problems/sort-an-array/description/)

// Given an array of integers nums, sort the array in ascending order and return it.
// You must solve the problem without using any built-in functions in O(nlog(n)) time complexity and with 
//the smallest space complexity possible.

#include <stdio.h>
#include <stdlib.h>

void countingSort(int* nums, int numsSize) {
    // Finding the maximum and minimum values
    int maxVal = nums[0];
    int minVal = nums[0];
    for (int i = 1; i < numsSize; i++) {
        if (nums[i] > maxVal) {
            maxVal = nums[i];
        }
        if (nums[i] < minVal) {
            minVal = nums[i];
        }
    }
    
    // Getting the range of values in the input array
    int range = maxVal - minVal + 1;
    
    int* count = (int*)calloc(range, sizeof(int));
    
    // Counting occurrences of each value
    for (int i = 0; i < numsSize; i++) {
        count[nums[i] - minVal]++;
    }
    
    for (int i = 1; i < range; i++) {
        count[i] += count[i - 1];
    }
    
    int* temp = (int*)malloc(numsSize * sizeof(int));
    
    // Sorting the array
    for (int i = numsSize - 1; i >= 0; i--) {
        temp[count[nums[i] - minVal] - 1] = nums[i];
        count[nums[i] - minVal]--;
    }
    
    for (int i = 0; i < numsSize; i++) {
        nums[i] = temp[i];
    }
    
    free(count);
    free(temp);
}

int* sortArray(int* nums, int numsSize, int* returnSize) {
    countingSort(nums, numsSize);
    
    *returnSize = numsSize;
    return nums;
}

int main() {
    int nums[] = {10, 5, 2, 8, 3};
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
