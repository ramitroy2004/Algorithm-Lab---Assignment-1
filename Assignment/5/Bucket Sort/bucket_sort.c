#include <stdio.h>
#include <stdlib.h>

struct Node {
    float data;
    struct Node *next;
};

struct Node *newNode(float data) {
    struct Node *temp = (struct Node*) malloc(sizeof(struct Node));
    temp->data = data;
    temp->next = NULL;
    return temp;
}

void insertSorted(struct Node **head, float data) {
    struct Node *current;
    struct Node *temp = newNode(data);
    if (*head == NULL || (*head)->data >= temp->data) {
        temp->next = *head;
        *head = temp;
    } else {
        current = *head;
        while (current->next != NULL && current->next->data < temp->data) {
            current = current->next;
        }
        temp->next = current->next;
        current->next = temp;
    }
}

void bucketSort(float arr[], int n) {
    struct Node **buckets = (struct Node**) malloc(n * sizeof(struct Node*));
    for (int i = 0; i < n; i++) {
        buckets[i] = NULL;
    }

    // Put elements into buckets
    for (int i = 0; i < n; i++) {
        int index = n * arr[i];
        insertSorted(&buckets[index], arr[i]);
    }

    // Concatenate all the buckets
    int index = 0;
    for (int i = 0; i < n; i++) {
        struct Node *current = buckets[i];
        while (current != NULL) {
            arr[index++] = current->data;
            current = current->next;
        }
    }

    // Deallocate memory
    for (int i = 0; i < n; i++) {
        struct Node *current = buckets[i];
        while (current != NULL) {
            struct Node *temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(buckets);
}

int main() {

    float arr[6] = {0.22, 0.12, 0.82, 0.76, 0.65, 0.44};

    // Sort the data
    bucketSort(arr, 6);

    // Print the sorted data
    for (int i = 0; i < 6; i++) {
        printf("%f\n", arr[i]);
    }

    return 0;
}
