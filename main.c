#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_SIZE 50
#define MAX_STR_LEN 20

typedef struct {
    int comparisons;
    int permutations;
} SortStats;

typedef struct Node{
    char word[MAX_STR_LEN];
    struct Node* next;
}Node;

// Display functions >
// *****************************************************

void displayArray(int arr[], int size, int iteration) {
    printf("Iteration %d: ", iteration);
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void displayStringArray(char arr[][MAX_STR_LEN], int size, int iteration) {
    printf("Iteration %d: ", iteration);
    for (int i = 0; i < size; i++) {
        printf("%s ", arr[i]);
    }
    printf("\n");
}

void displayList(Node* head, int iteration) {
    printf("Iteration %d: ", iteration);
    Node* current = head;
    while (current != NULL) {
        printf("%s ", current->word);
        current = current->next;
    }
    printf("\n");
}

// *****************************************************
// Swap functions >

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void swapString(char arr[][20], int i, int j) {
    char temp[20];
    strcpy(temp, arr[i]);
    strcpy(arr[i], arr[j]);
    strcpy(arr[j], temp);

}
// *****************************************************
// Array Sorting Algorithms >

SortStats selectionSort(int arr[], int size) {
    SortStats stats = {0, 0};
    int iteration = 0;
    
    for (int i = 0; i < size - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < size; j++) {
            stats.comparisons++;
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        
        if (min_idx != i) {
            swap(&arr[i], &arr[min_idx]); 
            stats.permutations++;
        }
        
        iteration++;
        displayArray(arr, size, iteration);
    }
    
    return stats;
}


SortStats bubbleSort(int arr[], int size) {
    SortStats stats = {0, 0};
    int iteration = 0;
    
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            stats.comparisons++;
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
                stats.permutations++;
            }
        }
        
        iteration++;
        displayArray(arr, n, iteration);
    }
    
    return stats;
}

SortStats selectionSort(int arr[], int size) {
    SortStats stats = {0, 0};
    int iteration = 0;
    
    for (int i = 0; i < size - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < size; j++) {
            stats.comparisons++;
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        
        if (min_idx != i) {
            swap(&arr[i], &arr[min_idx]); 
            stats.permutations++;
        }
        
        iteration++;
        displayArray(arr, size, iteration);
    }
    
    return stats;
}

int partition(int arr[], int low, int high, SortStats *stats) {
    int pvt = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        stats->comparisons++;
        if (arr[j] < pvt) {
            i++;
            swap(&arr[i], &arr[j]);
            stats->permutations++;
        }
    }
    swap(&arr[i + 1], &arr[high]);
    stats->permutations++;
    return (i + 1);
}

SortStats quickSort(int arr[], int low, int high) {
    SortStats stats = {0, 0};
    int iteration = 0;

    if (low < high) {
        int pi = partition(arr, low, high, &stats);
        iteration++;
        

        SortStats leftStats = quickSort(arr, low, pi - 1);
        SortStats rightStats = quickSort(arr, pi + 1, high);

        stats.comparisons += leftStats.comparisons + rightStats.comparisons;
        stats.permutations += leftStats.permutations + rightStats.permutations;
    }
    displayArray(arr, high - low + 1, iteration);
    
    return stats;
}

SortStats insertionSort(int arr[], int size) {
    SortStats stats = {0, 0};
    int iteration = 0;
    
    for (int i = 1; i < size; i++) {
        int key = arr[i];
        int j = i - 1;
        
        while (j >= 0 && arr[j] > key) {
            stats.comparisons++;
            arr[j + 1] = arr[j];
            j--;
            stats.permutations++;
        }
        
        arr[j + 1] = key;
        iteration++;
        displayArray(arr, size, iteration);
    }
    
    return stats;
}

SortStats combSort(int arr[], int size) {
    int gap = size;
    int swapped = 1;
    SortStats stats = {0, 0};

    while (gap != 1 || swapped) {
        gap = getNextGap(gap);
        swapped = 0;
        for(int i = 0; i < size - gap; i ++) {
            stats.comparisons ++
            if(arr[i] > arr[i + gap]) {
                stats.comparisons ++
                swap(&arr[i], &arr[i + gap]);
                stats.permutations ++;
                swapped = 1;
            }
        }
        iteration ++;
        displayArray(arr, size, iteration);
    }

    return stats;
}
