#include <stdio.h>
#include <stdlib.h>

#define size 10

void selectionSorting(int T[]) {
    int indexmin;
    for (int i = 0; i < size - 1; i++) {
        indexmin = i;
        for (int j = i + 1; j < size; j++) {
            if (T[j] < T[indexmin]) {
                indexmin = j;
            }
        }
        int temp = T[i];
        T[i] = T[indexmin];
        T[indexmin] = temp;
    }
}

void insertionSorting(int T[]) {
    for(int i=1; i<size; i++){
        int temp = T[i];
        int j = i-1;

        while(j>=0 && T[j] > temp){
            T[j+1] = T[j];
            j--;
        }

        T[j+1] = temp;
    }
}

void merge(int arr[], int left, int middle, int right) {
    int i, j, k;
    int n1 = middle - left + 1;    // size of left subarray
    int n2 = right - middle;       // size of right subarray
    
    // create temporary arrays
    int *L = (int*)malloc(n1 * sizeof(int));
    int *R = (int*)malloc(n2 * sizeof(int));
    
    // copy data to temporary arrays L[] and R[]
    for (i = 0; i < n1; i++){
        L[i] = arr[left + i];
    }

    for (j = 0; j < n2; j++){
        R[j] = arr[middle + 1 + j];
    }
    
    // merge the temporary arrays back into arr[left..right]
    i = 0;      // initial index of left subarray
    j = 0;      // initial index of right subarray
    k = left;   // initial index of merged subarray
    
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    
    // copy the remaining elements of L[], if any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    
    // copy the remaining elements of R[], if any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
    
    // free the temporary arrays
    free(L);
    free(R);
}

// main mergeSort function that sorts arr[left..right] using merge()
void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        // find the middle point to divide the array into two halves
        int middle = left + (right - left) / 2;
        
        // sort first and second halves recursively
        mergeSort(arr, left, middle);
        mergeSort(arr, middle + 1, right);
        
        // merge the sorted halves
        merge(arr, left, middle, right);
    }
}

int main() {
    int V[size] = {7, 5, 11, 6, 8, 4, 37, 43, 2, 9};

    printf("Unsorted array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", V[i]);
    }
    printf("\n");

    //*********************Procedures Call*****************************/

    // selectionSorting(V);
    // insertionSorting(V);
    mergeSort(V, 0, size - 1);

    //**************************************************/

    printf("Sorted array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", V[i]);
    }

    return 0;
}
