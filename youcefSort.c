#include<stdio.h>
#include<string.h>

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
// ******************************Matrix implementation: **************************
// Swap function >
void swapString(char arr[][20], int i, int j) {
    char temp[20];
    strcpy(temp, arr[i]);
    strcpy(arr[i], arr[j]);
    strcpy(arr[j], temp);

}

// Quick sort function >
// Partitiont function :
int partitionString(char matr[][20], int low, int high) {
    char pvt[20];
    strcpy(pivot, matr[high]);
    int i = low -1;
    for(int j = low; j < high; j ++ ) {
        if(strcmp(matr[j], pvt) < 0) { // comaraison alphabitique
            i ++;
            swap(matr, i, j);
        }
        
    }
    swap(arr, i + 1, high);
    return i + 1;
}

void quickSortString(char matr[][20], int low, int high) {
    if(low < hight) {
        int pi = partitionString(matr, low, high);
        quickSort(matr, low, pi - 1);
        quickSort(matr, pi + 1, high);
    }
}



// +++++++++++++++++++++++++++++++++++++++++++++++++++++
// Display >

// display array :
void displayArray(int arr[], int n) {
    for(int i = 0; i < n; i ++) {
        printf("%d ", arr[i]);
    }
}

// display matrix that have strings:
void DisplayMatrix(char matr[][20], int size) {
    for(int i = 0; i< size; i ++) {
        printf("%s\n", matr[i]);
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
