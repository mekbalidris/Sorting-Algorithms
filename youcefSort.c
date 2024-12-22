#include<stdio.h>

// ******************************Array implementation: **************************
// Swap function to use it in all functions

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
// Bubbule sorting >----------------------

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

// Quick Sortiong >----------------------
// Partition of the array by fixing eache time a pivot in the midel
// and have on the right value less than it and in the left values biger than it;

int partition(int arr[], int low, int high) {
    int pvt = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] < pvt) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// comb sort > ----------------------
// Function to find the next gap :
int getNextGap(int gap) {
    gap = (gap * 10) / 13;
    if(gap < 1)
        return 1;
    return gap;
}

void combSort(int arr[], int n) {
    int gap = n;
    int swapped = 1;

    while (gap != 1 || swapped) {
        gap = getNextGap(gap);
        swapped = 0;
        for(int i = 0; i < n - gap; i ++) {
            if(arr[i] > arr[i + gap]) {
                swap(&arr[i], &arr[i + gap]);
                swapped = 1;
            }
        }
    }
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++
// Display >
void displayArray(int arr[], int n) {
    for(int i = 0; i < n; i ++) {
        printf("%d ", arr[i]);
    }
}

int main() {

    int arr[] = {12, 56, 1, 102, 4,3, 8, -3};
    int n = sizeof(arr) / sizeof(int);
    printf("Befor : \n");
    displayArray(arr, n);
    printf("\nAfter :");
    // bubbleSort(arr,  n);
    // quickSort(arr, 0, n - 1);
    combSort(arr, n);
    displayArray(arr, n);

    return 0;
}
