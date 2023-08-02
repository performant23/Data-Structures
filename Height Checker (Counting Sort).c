// Height Checker (https://leetcode.com/problems/height-checker/)

//A school is trying to take an annual photo of all the students. 
// The students are asked to stand in a single file line in non-decreasing order by height. 
// Let this ordering be represented by the integer array expected where expected[i] is the expected height of the ith student in line.

//You are given an integer array heights representing the current order that the students are standing in. 
//Each heights[i] is the height of the ith student in line (0-indexed).

//Return the number of indices where heights[i] != expected[i].


// Solution:
#include <stdio.h>
#include <stdlib.h>

int heightChecker(int* heights, int heightsSize) {
    // Find the expected order of heights
    int* expected = (int*)malloc(heightsSize * sizeof(int));
    for (int i = 0; i < heightsSize; i++) {
        expected[i] = heights[i];
    }
    for (int i = 1; i < heightsSize; i++) {
        for (int j = 0; j < heightsSize - i; j++) {
            if (expected[j] > expected[j + 1]) {
                int temp = expected[j];
                expected[j] = expected[j + 1];
                expected[j + 1] = temp;
            }
        }
    }

    // Use counting sort to count the number of indices for differences between expected and actual heights
    int count[101] = {0};
    for (int i = 0; i < heightsSize; i++) {
        count[heights[i]]++;
    }

    int index = 0;
    int mismatchCount = 0;
    for (int i = 1; i <= 100; i++) {
        while (count[i] > 0) {
            if (heights[index] != expected[index]) {
                mismatchCount++;
            }
            count[i]--;
            index++;
        }
    }

    free(expected);

    return mismatchCount;
}

int main() {
    int heights[] = {5, 1, 2, 3, 4};
    int heightsSize = sizeof(heights) / sizeof(heights[0]);

    int result = heightChecker(heights, heightsSize);

    printf("Number of mismatches: %d\n", result);

    return 0;
}