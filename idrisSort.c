#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 50
#define MAX_STR_LEN 20

// Structure for statistics tracking
typedef struct {
    int comparisons;
    int permutations;
} SortStats;

typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Function to display array state after each iteration
void displayArray(int arr[], int size, int iteration) {
    printf("Iteration %d: ", iteration);
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Function to display string array state
void displayStringArray(char arr[][MAX_STR_LEN], int size, int iteration) {
    printf("Iteration %d: ", iteration);
    for (int i = 0; i < size; i++) {
        printf("%s ", arr[i]);
    }
    printf("\n");
}

// Function to display linked list state
void displayList(Node* head, int iteration) {
    printf("Iteration %d: ", iteration);
    Node* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// Enhanced Selection Sort with statistics
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

// Enhanced Insertion Sort with statistics
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

// Enhanced String Insertion Sort with statistics
SortStats insertionSortStrings(char arr[][MAX_STR_LEN], int size) {
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

// Enhanced Linked List Insertion Sort with statistics
SortStats insertionSortLinkedList(Node** head) {
    SortStats stats = {0, 0};
    Node* sorted = NULL;
    Node* current = *head;
    int iteration = 0;
    
    while (current != NULL) {
        Node* next = current->next;
        stats.comparisons++;
        
        if (sorted == NULL || sorted->data >= current->data) {
            current->next = sorted;
            sorted = current;
            stats.permutations++;
        } else {
            Node* temp = sorted;
            while (temp->next != NULL && temp->next->data < current->data) {
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

// Function to create a new node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Menu function for vector sorting
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
        default:
            printf("Invalid choice!\n");
            return;
    }
    
    printf("\nFinal Results:\n");
    printf("Number of comparisons: %d\n", stats.comparisons);
    printf("Number of permutations: %d\n", stats.permutations);
}

// Main menu function
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
                printf("Matrix Sort - To be implemented\n");
                break;
            case 3:
                printf("Linked List Sort - To be implemented\n");
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