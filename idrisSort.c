#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 50
#define MAX_STR_LEN 20

typedef struct {
    int comparisons;
    int permutations;
} SortStats;

typedef struct Node {
    char word[MAX_STR_LEN];
    struct Node* next;
} Node;

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
            int temp = arr[i];
            arr[i] = arr[min_idx];
            arr[min_idx] = temp;
            stats.permutations++;
        }
        
        iteration++;
        displayArray(arr, size, iteration);
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

void merge(int arr[], int left, int middle, int right) {
    SortStats stats = {0, 0};
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
        stats.comparisons++;
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
        stats.permutations++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
        stats.permutations++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
        stats.permutations++;
    }

    free(L);
    free(R);
}

void mergeSort(int arr[], int left, int right, int size, int* iteration) {
    if (left < right) {
        int middle = left + (right - left) / 2;

        mergeSort(arr, left, middle, size, iteration);
        mergeSort(arr, middle + 1, right, size, iteration);

        merge(arr, left, middle, right);

        // Display intermediate state
        printf("After merging [%d..%d]: ", left, right);
        displayArray(arr, size, ++(*iteration));
    }
}

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

Node* createNode(const char* word) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->word, word);
    newNode->next = NULL;
    return newNode;
}

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

void vectorSortMenu() {
    int arr[MAX_SIZE];
    int size;
    SortStats stats;
    int iteration = 0;
    
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
            mergeSort(arr, 0, size - 1, size, &iteration);
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
    
    printf("\nOriginal matrix:\n");
    displayStringArray(matrix, size, 0);
    
    stats = insertionSortMatrix(matrix, size);
    
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
    
    printf("\nOriginal list:\n");
    displayList(head, 0);
    
    stats = insertionSortList(&head);
    
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