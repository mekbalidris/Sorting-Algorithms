#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define size 10

// Counters for comparisons and permutations
int nbComp = 0;
int nbPerm = 0;

typedef struct Node {
    int data;
    struct Node* next;
} Node;

void displayArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void selectionSorting(int T[]) {
    nbComp = 0;
    nbPerm = 0;

    int indexmin;
    for (int i = 0; i < size - 1; i++) {
        indexmin = i;
        for (int j = i + 1; j < size; j++) {
            nbComp++;
            if (T[j] < T[indexmin]) {
                indexmin = j;
            }
        }
        int temp = T[i];
        T[i] = T[indexmin];
        T[indexmin] = temp;
        nbPerm++;

        // Display intermediate state
        printf("After iteration %d: ", i + 1);
        displayArray(T, size);
    }

    printf("Comparisons: %d, Permutations: %d\n", nbComp, nbPerm);
}

void insertionSorting(int T[]) {
    nbComp = 0;
    nbPerm = 0;

    for (int i = 1; i < size; i++) {
        int temp = T[i];
        int j = i - 1;

        while (j >= 0 && T[j] > temp) {
            nbComp++;
            T[j + 1] = T[j];
            j--;
            nbPerm++;
        }
        if (j >= 0) nbComp++;

        T[j + 1] = temp;

        // Display intermediate state
        printf("After iteration %d: ", i);
        displayArray(T, size);
    }

    printf("Comparisons: %d, Permutations: %d\n", nbComp, nbPerm);
}

void merge(int arr[], int left, int middle, int right) {
    int i, j, k;
    int n1 = middle - left + 1;
    int n2 = right - middle;

    int* L = (int*)malloc(n1 * sizeof(int));
    int* R = (int*)malloc(n2 * sizeof(int));

    for (i = 0; i < n1; i++) {
        L[i] = arr[left + i];
    }

    for (j = 0; j < n2; j++) {
        R[j] = arr[middle + 1 + j];
    }

    i = 0;
    j = 0;
    k = left;

    while (i < n1 && j < n2) {
        nbComp++;
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
        nbPerm++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
        nbPerm++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
        nbPerm++;
    }

    free(L);
    free(R);
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int middle = left + (right - left) / 2;

        mergeSort(arr, left, middle);
        mergeSort(arr, middle + 1, right);

        merge(arr, left, middle, right);

        // Display intermediate state
        printf("After merging [%d..%d]: ", left, right);
        displayArray(arr, size);
    }
}

void analyzeSortingTime(void (*sortingFunction)(int[]), int arr[], const char* sortName) {
    int tempArr[size];
    memcpy(tempArr, arr, size * sizeof(int));

    clock_t start = clock();
    sortingFunction(tempArr);
    clock_t end = clock();

    double timeSpent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("%s Time Taken: %.6f seconds\n", sortName, timeSpent);
}

int main() {
    int V[size] = {7, 5, 11, 6, 8, 4, 37, 43, 2, 9};

    printf("Original array: ");
    displayArray(V, size);

    printf("\nSelection Sort:\n");
    analyzeSortingTime(selectionSorting, V, "Selection Sort");

    printf("\nInsertion Sort:\n");
    analyzeSortingTime(insertionSorting, V, "Insertion Sort");

    printf("\nMerge Sort:\n");
    nbComp = 0;
    nbPerm = 0;
    analyzeSortingTime(mergeSort, V, "Merge Sort");
    printf("Comparisons: %d, Permutations: %d\n", nbComp, nbPerm);

    return 0;
}

/*
Time Complexity Analysis:
- Selection Sort: O(n^2) for all cases.
- Insertion Sort: Best O(n), Average/Worst O(n^2).
- Merge Sort: O(n log n) for all cases.
*/
