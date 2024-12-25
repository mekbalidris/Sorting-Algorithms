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

Node* createNode(const char* word) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->word, word);
    newNode->next = NULL;
    return newNode;
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
        displayArray(arr, high - low + 1, iteration);
        stats.comparisons += leftStats.comparisons + rightStats.comparisons;
        stats.permutations += leftStats.permutations + rightStats.permutations;
    }

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

int getNextGap(int gap) {
    gap = (gap * 10) / 13;
    if(gap < 1)
        return 1;
    return gap;
}

SortStats combSort(int arr[], int size) {
    int gap = size;
    int swapped = 1;
    int iteration = 0;
    SortStats stats = {0, 0};

    while (gap != 1 || swapped) {
        gap = getNextGap(gap);
        swapped = 0;
        for(int i = 0; i < size - gap; i ++) {
            stats.comparisons ++;
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
        displayStringArray(matr, high - low + 1, iteration);

        SortStats leftStats = quickSortString(matr, low, pi - 1);
        SortStats rightStats = quickSortString(matr, pi + 1, high);

        stats.comparisons += leftStats.comparisons + rightStats.comparisons;
        stats.permutations += leftStats.permutations + rightStats.permutations;
    }

    return stats;
}

// *****************************************************
// Linked list Sorting >
SortStats insertionSortList(Node** head) {
    SortStats stats = {0, 0};
    Node* sorted = NULL;
    Node* current = *head;
    int iteration = 0;
    
    while (current != NULL) {
        Node* next = current->next;
        stats.comparisons++;
        
        if (sorted == NULL || strcmp(sorted->word, current->word) >= 0) {
            current->next = sorted;
            sorted = current;
            stats.permutations++;
        } else {
            Node* temp = sorted;
            while (temp->next != NULL && strcmp(temp->next->word, current->word) < 0) {
                stats.comparisons++;
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
            stats.permutations++;
        }
        
        current = next;
        iteration++;
        displayList(sorted, iteration);
    }
    
    *head = sorted;
    return stats;
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
    
    printf("\nVector Sort Menu\n");
    printf("Enter size of array (max %d): ", MAX_SIZE);
    scanf("%d", &size);
    
    printf("Enter %d integers:\n", size);
    for (int i = 0; i < size; i++) {
        scanf("%d", &arr[i]);
    }
    
    printf("\nChoose sorting method:\n");
    printf("1. Selection Sort\n");
    printf("2. Insertion Sort\n");
    printf("3. Bubble Sort\n");
    printf("4. Quick Sort\n");
    printf("5. Comb Sort\n");
    printf("Coming soon \n");
    int choice;
    scanf("%d", &choice);
    
    printf("\nOriginal array: ");
    displayArray(arr, size, 0);
    
    switch(choice) {
        case 1:
            stats = selectionSort(arr, size);
            break;
        case 2:
            stats = insertionSort(arr, size);
            break;
        case 3:
            stats = bubbleSort(arr, size);
            break;
        case 4:
            stats = quickSort(arr, 0, size - 1);
            break;    
        default:
            printf("Invalid choice!\n");
            return;
    }
    
    printf("\nFinal Results:\n");
    printf("Number of comparisons: %d\n", stats.comparisons);
    printf("Number of permutations: %d\n", stats.permutations);
} 

void matrixSortMenu() {
    char matrix[MAX_SIZE][MAX_STR_LEN];
    int size;
    SortStats stats;
    
    printf("\nMatrix Sort Menu\n");
    printf("Enter number of strings (max %d): ", MAX_SIZE);
    scanf("%d", &size);
    getchar();  // Consume newline
    
    printf("Enter %d strings:\n", size);
    for (int i = 0; i < size; i++) {
        fgets(matrix[i], MAX_STR_LEN, stdin);
        matrix[i][strcspn(matrix[i], "\n")] = 0;  // Remove newline
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