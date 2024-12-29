#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <time.h> 

#define MAX_SIZE 1000
#define MAX_STR_LEN 20

typedef struct {
    int comparisons;
    int permutations;
} SortStats;

typedef struct Node{
    char word[MAX_STR_LEN];
    struct Node* next;
}Node;

Node* createNode(const char* word) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->word, word);
    newNode->next = NULL;
    return newNode;
}

void measureSortingTime(void (*sortFunction)(int[], int), int arr[], int size, const char* algorithmName) {
    clock_t start, end;
    double cpu_time_used;
    
    // Create a copy of the array to keep original intact
    int* arr_copy = (int*)malloc(size * sizeof(int));
    memcpy(arr_copy, arr, size * sizeof(int));
    
    start = clock();
    sortFunction(arr_copy, size);
    end = clock();
    
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("\nTime taken by %s: %f seconds\n", algorithmName, cpu_time_used);
    
    free(arr_copy);
}
// Display functions >
// *****************************************************

void displayArray(int arr[], int size, int iteration) {
    printf("Iteration %d: ", iteration);
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void displayMergeSortProgress(int arr[], int iteration, int left, int right) {
    printf("Iteration %d: Merged range [%d..%d]: [", iteration, left, right);
    for (int i = left; i <= right; i++) {
        printf("%d", arr[i]);
        if (i < right) printf(", ");
    }
    printf("]\n");
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

void swapString(char arr[][MAX_STR_LEN], int i, int j) {
    char temp[MAX_STR_LEN];
    strcpy(temp, arr[i]);
    strcpy(arr[i], arr[j]);
    strcpy(arr[j], temp);

}
// *****************************************************
// Array Sorting Algorithms >

SortStats selectionSort(int arr[], int size) {     
    SortStats stats = {0, 0};     
    int iteration = 0;         
    
    // Iterate through the array
    for (int i = 0; i < size - 1; i++) {         
        int min_idx = i;         
        // Find minimum element in the unsorted portion
        for (int j = i + 1; j < size; j++) {             
            stats.comparisons++;             
            if (arr[j] < arr[min_idx]) {                 
                min_idx = j;             
            }         
        }         
        
        // Swap if minimum element is not at its correct position        
        if (min_idx != i) {             
            swap(&arr[i], &arr[min_idx]);             
            stats.permutations++;         
        }         
        
        // Display current state of array after each iteration        
        iteration++;         
        displayArray(arr, size, iteration);     
    }         
    return stats; 
} 


// Bubble Sort
SortStats bubbleSort(int arr[], int size) {
    // initialize the Sort state in {0, 0} and also the count of iterations
    SortStats stats = {0, 0};
    int iteration = 0;
    // iterrate through the array
    for (int i = 0; i < size - 1; i++) {
        // Compare adjacent elements
        for (int j = 0; j < size - i - 1; j++) {
            // Increament the number of comparisions
            stats.comparisons++;
            if (arr[j] > arr[j + 1]) {
                // if current element is greater than the next one than we swap
                swap(&arr[j], &arr[j + 1]);
                //  than we increment the number of permutation 
                stats.permutations++;
            }
        }
        
        // increment iterations
        iteration++;
        // display the atate of the array after eache iteration
        displayArray(arr, size, iteration);
    }
    
    return stats;
}

// Quick sort
// Partition function to rerrage elements aroud a pivot
int partition(int arr[], int low, int high, SortStats *stats) {
    int pvt = arr[high]; //pivot element chosen at the last element
    int i = low - 1; // index of the smaller element
    // loop throught the array to rearrange elements
    for (int j = low; j < high; j++) {
        stats->comparisons++;
        if (arr[j] < pvt) {
            //move the smaller element index to the next if curent element is smaller that the pivot
            i++; 
            swap(&arr[i], &arr[j]);
            stats->permutations++;
        }
    }
    // place the pivot in the corect position
    swap(&arr[i + 1], &arr[high]);
    stats->permutations++;
    return (i + 1); //return the index of the pevot element
}
// quick Sort recursive function
int iterationQuick = 0; // global variable with extern init to preserve the value
SortStats quickSort(int arr[], int low, int high) {
    SortStats stats = {0, 0};
    
    
    // Base case to exit is the range is invalid
    if (low < high) {
        // partition the array to get the pivot
        int pi = partition(arr, low, high, &stats);
        
        // recursively sort the left and the right partitions
        SortStats leftStats = quickSort(arr, low, pi - 1);
        SortStats rightStats = quickSort(arr, pi + 1, high);
        
        // accumulate statistics from the left and right recursive cal
        stats.comparisons += leftStats.comparisons + rightStats.comparisons;
        stats.permutations += leftStats.permutations + rightStats.permutations;
        iterationQuick++;
        displayMergeSortProgress(arr,iterationQuick, low, high);
    }
    
    return stats;
}



SortStats insertionSort(int arr[], int size) {     
    SortStats stats = {0, 0};     
    int iteration = 0;         
    
    // Start from second element
    for (int i = 1; i < size; i++) {         
        int key = arr[i];         // Element to be inserted
        int j = i - 1;         
        
        // Move elements greater than key one position ahead
        while (j >= 0 && arr[j] > key) {             
            stats.comparisons++;             
            arr[j + 1] = arr[j];             
            j--;             
            stats.permutations++;         
        }         
        
        // Place key in its correct position
        arr[j + 1] = key;         
        iteration++;         
        displayArray(arr, size, iteration);     
    }         
    return stats; 
}

int getNextGap(int gap) {
    gap = (gap * 10) / 13;
    if(gap < 1)
        return 1;
    return gap;
}

// Comb Soer
// function to calculate the next gap sizr in combsort
int getNextGap(int gap) {
    // reduce the gap size using the shrink factor (10/13)
    gap = (gap * 10) / 13;

    // Ensure the gap is at least 1 to continue comparisons
    if(gap < 1)
        return 1;
    return gap; // return the updated gap size
}
// CombSort function
SortStats combSort(int arr[], int size) {
    // init the gap
    int gap = size;
    int swapped = 1;
    int iteration = 0;
    SortStats stats = {0, 0};
    // continue sorting until the gap i 1 and no swap are performed
    while (gap != 1 || swapped) {
        // calculate the next gap size using the getNextgap function
        gap = getNextGap(gap);
        swapped = 0; // reset swap
        for(int i = 0; i < size - gap; i ++) {
            stats.comparisons ++;
            // if current element is greater than the one on the destince swap
            if(arr[i] > arr[i + gap]) {
                stats.comparisons ++;
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



// *****************************************************
// Strings Array Sorting >
SortStats insertionSortMatrix(char arr[][MAX_STR_LEN], int size) {
    SortStats stats = {0, 0};
    int iteration = 0;
    
    for (int i = 1; i < size; i++) {
        char key[MAX_STR_LEN];
        strcpy(key, arr[i]);
        int j = i - 1;
        
        while (j >= 0 && strcmp(arr[j], key) > 0) {
            stats.comparisons++;
            strcpy(arr[j + 1], arr[j]);
            j--;
            stats.permutations++;
        }
        
        strcpy(arr[j + 1], key);
        iteration++;
        displayStringArray(arr, size, iteration);
    }
    
    return stats;
}

int partitionString(char matr[][MAX_STR_LEN], int low, int high, SortStats *stats) {
    char pvt[MAX_STR_LEN];
    strcpy(pvt, matr[high]);
    int i = low - 1;

    for (int j = low; j < high; j++) {
        stats->comparisons++;
        if (strcmp(matr[j], pvt) < 0) {
            i++;
            swapString(matr, i, j);
            stats->permutations++;
        }
    }

    swapString(matr, i + 1, high);
    stats->permutations++;
    return (i + 1);
}

SortStats quickSortString(char matr[][MAX_STR_LEN], int low, int high) {
    SortStats stats = {0, 0};
    int iteration = 0;

    if (low < high) {
        int pi = partitionString(matr, low, high, &stats);
        iteration++;
        

        SortStats leftStats = quickSortString(matr, low, pi - 1);
        SortStats rightStats = quickSortString(matr, pi + 1, high);

        stats.comparisons += leftStats.comparisons + rightStats.comparisons;
        stats.permutations += leftStats.permutations + rightStats.permutations;
    }
    displayStringArray(matr, high - low + 1, iteration);

    return stats;
}

// *****************************************************
void merge(int arr[], int left, int middle, int right, SortStats *stats) {     
    int i, j, k;     
    int n1 = middle - left + 1;     // Size of left subarray
    int n2 = right - middle;        // Size of right subarray
    
    // Create temporary arrays
    int* L = (int*)malloc(n1 * sizeof(int));     
    int* R = (int*)malloc(n2 * sizeof(int));     
    
    // Copy data to temporary arrays
    for (i = 0; i < n1; i++) {         
        L[i] = arr[left + i];     
    }     
    for (j = 0; j < n2; j++) {         
        R[j] = arr[middle + 1 + j];     
    }     
    
    // Initial indexes of subarrays
    i = 0;       // Index for left subarray
    j = 0;       // Index for right subarray
    k = left;    // Index for merged array
    
    // Merge the temporary arrays back
    while (i < n1 && j < n2) {         
        stats->comparisons++;         
        if (L[i] <= R[j]) {             
            arr[k] = L[i];             
            i++;         
        } else {             
            arr[k] = R[j];             
            j++;         
        }         
        stats->permutations++;         
        k++;     
    }     
    
    // Copy remaining elements of L[]
    while (i < n1) {         
        arr[k] = L[i];         
        i++;         
        k++;         
        stats->permutations++;     
    }     
    
    // Copy remaining elements of R[]
    while (j < n2) {         
        arr[k] = R[j];         
        j++;         
        k++;         
        stats->permutations++;     
    }     
    
    // Free temporary arrays
    free(L);     
    free(R); 
}   


SortStats mergeSort(int arr[], int left, int right, int size) {     
    static int iteration = 0;     
    static SortStats totalStats = {0, 0};         
    
    if (left < right) {         
        // Find middle point
        int middle = left + (right - left) / 2;           
        
        // Sort first and second halves recursively
        mergeSort(arr, left, middle, size);         
        mergeSort(arr, middle + 1, right, size);           
        
        // Merge the sorted halves
        SortStats mergeStats = {0, 0};         
        merge(arr, left, middle, right, &mergeStats);           
        
        // Update total statistics
        totalStats.comparisons += mergeStats.comparisons;         
        totalStats.permutations += mergeStats.permutations;           
        
        // Display progress after each merge
        iteration++;         
        displayMergeSortProgress(arr, iteration, left, right);     
    }     
    return totalStats; 
}


// *****************************************************

// *****************************************************
// Linked list Sorting >
SortStats insertionSortList(Node** head) {
    SortStats stats = {0, 0};  // Structure to track comparisons and permutations
    Node* sorted = NULL;       // Pointer to the sorted portion of the list
    Node* current = *head;     // Pointer to traverse the unsorted portion
    int iteration = 0;         // Counter for visualization purposes
    
    // Traverse through the unsorted list
    while (current != NULL) {
        Node* next = current->next;  // Store next node before modifying current
        stats.comparisons++;         // Count comparison for the initial check
        
        // If sorted list is empty or current word should be at the beginning
        if (sorted == NULL || strcmp(sorted->word, current->word) >= 0) {
            current->next = sorted;  // Insert at beginning of sorted list
            sorted = current;
            stats.permutations++;    // Count the insertion
        } else {
            // Find the correct position in sorted list
            Node* temp = sorted;
            // Traverse until we find the right position (where next word is greater)
            while (temp->next != NULL && strcmp(temp->next->word, current->word) < 0) {
                stats.comparisons++; // Count each comparison during traversal
                temp = temp->next;
            }
            // Insert current node between temp and temp->next
            current->next = temp->next;
            temp->next = current;
            stats.permutations++; // Count the insertion
        }
        
        current = next; // Move to next node in unsorted portion
        iteration++;
        displayList(sorted, iteration); // Display current state of sorted list
    }
    
    *head = sorted;  // Update the head to point to sorted list
    return stats;    // Return statistics of the sorting process
}

SortStats bubbleSortingList(Node** l) {
    SortStats stats = {0, 0};
    int iteration = 0;

    if (l == NULL || *l == NULL || (*l)->next == NULL) {
        return stats;
    }

    int swapped;
    Node *p, *q, *next;

    do {
        swapped = 0;
        p = *l;
        q = NULL;

        while (p != NULL && p->next != NULL) {
            next = p->next;
            stats.comparisons++;

            if (strcmp(p->word, next->word) > 0) {
                if (q == NULL) {
                    *l = next;
                } else {
                    q->next = next;
                }

                p->next = next->next;
                next->next = p;
                swapped = 1;
                stats.permutations++;
            } else {
                q = p;
            }

            p = p->next;
        }

        iteration++;
        displayList(*l, iteration);

    } while (swapped);

    return stats;
}

// *****************************************************
// Menues >

void vectorSortMenu() {
    int arr[MAX_SIZE];
    int size;
    SortStats stats;
    srand(time(NULL));
    
    printf("\nVector Sort Menu\n");
    printf("Enter size of array (max %d): ", MAX_SIZE);
    scanf("%d", &size);
    
    if (size > MAX_SIZE) {
        printf("Size exceeds maximum limit of %d.\n", MAX_SIZE);
        return;
    }
    
    // Generate random array
    for (int i = 0; i < size; i++) {  
        arr[i] = rand() % 1000 + 1;
    }  
    
    printf("\nChoose sorting method:\n");
    printf("1. Selection Sort\n");
    printf("2. Insertion Sort\n");
    printf("3. Bubble Sort\n");
    printf("4. Quick Sort\n");
    printf("5. Comb Sort\n");
    printf("6. Merge Sort\n");
    int choice;
    scanf("%d", &choice);
    
    printf("\nOriginal array: ");
    displayArray(arr, size, 0);
    
    int* temp_arr = (int*)malloc(size * sizeof(int));
    memcpy(temp_arr, arr, size * sizeof(int));
    
    clock_t start, end;
    double cpu_time_used;
    
    switch(choice) {
        case 1:
            start = clock();
            stats = selectionSort(arr, size);
            end = clock();
            break;
        case 2:
            start = clock();
            stats = insertionSort(arr, size);
            end = clock();
            break;
        case 3:
            start = clock();
            stats = bubbleSort(arr, size);
            end = clock();
            break;
        case 4:
            start = clock();
            stats = quickSort(arr, 0, size - 1);
            end = clock();
            break;
        case 5:
            start = clock();
            stats = combSort(arr, size);
            end = clock();
            break;
        case 6:
            start = clock();
            stats = mergeSort(arr, 0, size - 1, size);
            end = clock();
            break;
        default:
            printf("Invalid choice.\n");
            free(temp_arr);
            return;
    }
    
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    
    printf("\nSorting completed.\n");
    printf("Total comparisons: %d\n", stats.comparisons);
    printf("Total permutations: %d\n", stats.permutations);
    printf("Time taken: %f seconds\n", cpu_time_used);
    
    free(temp_arr);
}

void matrixSortMenu() {
    char matrix[MAX_SIZE][MAX_STR_LEN];
    int size;
    SortStats stats;
    
    printf("\nMatrix Sort Menu\n");
    printf("Enter number of strings (max %d): ", MAX_SIZE);
    scanf("%d", &size);
    getchar();
    
    printf("Enter %d strings:\n", size);
    for (int i = 0; i < size; i++) {
        fgets(matrix[i], MAX_STR_LEN, stdin);
        matrix[i][strcspn(matrix[i], "\n")] = 0; 
    }
    
    printf("\nChoose sorting method:\n");
    printf("1. Insertion Sort \n");
    printf("2. Quick Sort\n");
    int choice;
    scanf("%d", &choice);

    printf("\nOriginal matrix:\n");
    displayStringArray(matrix, size, 0);

    switch(choice) {
        case 1:
            stats = insertionSortMatrix(matrix,  size);
            break;
        case 2:
            stats = quickSortString(matrix, 0, size - 1);
        break;

        default:
            printf("Invalide choice!\n");    
    }
    
    printf("\nFinal Results:\n");
    printf("Number of comparisons: %d\n", stats.comparisons);
    printf("Number of permutations: %d\n", stats.permutations);
}

void linkedListSortMenu() {
    Node* head = NULL;
    int size;
    SortStats stats;
    
    printf("\nLinked List Sort Menu\n");
    printf("Enter number of words (max %d): ", MAX_SIZE);
    scanf("%d", &size);
    getchar();  // Consume newline
    
    printf("Enter %d words:\n", size);
    for (int i = 0; i < size; i++) {
        char word[MAX_STR_LEN];
        fgets(word, MAX_STR_LEN, stdin);
        word[strcspn(word, "\n")] = 0;  // Remove newline
        
        Node* newNode = createNode(word);
        newNode->next = head;
        head = newNode;
    }

    printf("\nChoose sorting method:\n");
    printf("1. Bubbel Sort\n");
    printf("2. Insertion Sort\n");
    int choice;
    scanf("%d", &choice);
    
    printf("\nOriginal list:\n");
    displayList(head, 0);
    
    switch(choice) {
        case 1:
            stats = insertionSortList(&head);
            break;
        case 2:
            stats = bubbleSortingList(&head);
            break;
        default :
            printf("Invalide choice!\n");
    }
    
    printf("\nFinal Results:\n");
    printf("Number of comparisons: %d\n", stats.comparisons);
    printf("Number of permutations: %d\n", stats.permutations);
    
    while (head != NULL) {
        Node* temp = head;
        head = head->next;
        free(temp);
    }
}

void mainMenu() {
    while (1) {
        printf("\nMain Menu\n");
        printf("1. Vector Sort\n");
        printf("2. Matrix Sort\n");
        printf("3. Linked List Sort\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        
        int choice;
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                vectorSortMenu();
                break;
            case 2:
                matrixSortMenu();
                break;
            case 3:
                linkedListSortMenu();
                break;
            case 4:
                printf("Exiting program\n");
                return;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
}

int main() {
    mainMenu();
    return 0;
}