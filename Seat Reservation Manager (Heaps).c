// Seat Reservation Manager (https://leetcode.com/problems/seat-reservation-manager/description/)
// Design a system that manages the reservation state of n seats that are numbered from 1 to n.

//Implement the SeatManager class:

//    SeatManager(int n) Initializes a SeatManager object that will manage n seats numbered from 1 to n. All seats are initially available.
  //  int reserve() Fetches the smallest-numbered unreserved seat, reserves it, and returns its number.
    //void unreserve(int seatNumber) Unreserves the seat with the given seatNumber.

// Solution:

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* seats;
    int size;
} SeatManager;

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void minHeapify(int* arr, int size, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < size && arr[left] < arr[smallest]) {
        smallest = left;
    }

    if (right < size && arr[right] < arr[smallest]) {
        smallest = right;
    }

    if (smallest != i) {
        swap(&arr[i], &arr[smallest]);
        minHeapify(arr, size, smallest);
    }
}

SeatManager* seatManagerCreate(int n) {
    SeatManager* obj = (SeatManager*)malloc(sizeof(SeatManager));
    obj->seats = (int*)malloc(n * sizeof(int));
    obj->size = n;

    for (int i = 0; i < n; i++) {
        obj->seats[i] = i + 1;
    }

    // Building a min-heap
    for (int i = n / 2 - 1; i >= 0; i--) {
        minHeapify(obj->seats, n, i);
    }

    return obj;
}

int seatManagerReserve(SeatManager* obj) {
    int seatNumber = obj->seats[0]; // Smallest-numbered unreserved seat
    obj->size--;
    obj->seats[0] = obj->seats[obj->size]; // Replacing the reserved seat with the last unreserved seat
    minHeapify(obj->seats, obj->size, 0); //We here Re-heapify the remaining seats
    return seatNumber;
}

void seatManagerUnreserve(SeatManager* obj, int seatNumber) {
    obj->seats[obj->size] = seatNumber; // Adding the unreserved seat back to the end of the array
    obj->size++;
    int i = obj->size - 1;
    int parent = (i - 1) / 2;

    while (i > 0 && obj->seats[parent] > obj->seats[i]) {
        swap(&obj->seats[i], &obj->seats[parent]);
        i = parent;
        parent = (i - 1) / 2;
    }
}

void seatManagerFree(SeatManager* obj) {
    free(obj->seats);
    free(obj);
}

int main() {
    SeatManager* obj = seatManagerCreate(5);
    printf("Reserved seat: %d\n", seatManagerReserve(obj));
    printf("Reserved seat: %d\n", seatManagerReserve(obj));
    seatManagerUnreserve(obj, 2);
    printf("Reserved seat: %d\n", seatManagerReserve(obj));
    printf("Reserved seat: %d\n", seatManagerReserve(obj));
    printf("Reserved seat: %d\n", seatManagerReserve(obj));
    printf("Reserved seat: %d\n", seatManagerReserve(obj));
    seatManagerFree(obj);
    return 0;
}
